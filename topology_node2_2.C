// topology_node2_2_with_progress.C
// - 진행률: (g,l,i) 삼중 루프 기준 % 표시
// - tried: attachments까지 적용된 "그래프 1건 시도" 카운트
// - I(instantons)는 의도대로 s(v)로 추가 (파라미터로 구분)
// - S는 항상 (S, host) 순서로 connect → "왼쪽 포트" 규칙 유지
// - multiset+exact 규칙 유지, n_attaches 불일치 수정(필요 스펙에서 반영)

#include "Theory.h"
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <cmath>
#include <atomic>

#ifdef _OPENMP
  #include <omp.h>
  #define MASTER_THREAD (omp_get_thread_num()==0)
#else
  #define MASTER_THREAD (true)
#endif

// --- 로컬 kind (Theory.h의 Kind와 이름 충돌 방지용) ---
enum class LKind : unsigned char { G=0, L=1, S=2, I=3 };

// ---- 기본 자료구조 ----
struct ParamBank { const int* vals; int N; };
struct BaseNode  { LKind kind; };
struct BaseEdge  { int u, v; };

struct AttachRule {
  int   host_idx;    // 어느 노드에 붙이는지 (노드 인덱스)
  LKind kind;        // 붙일 타입(S/L/I)
  int   max_count;   // 몇 개 붙일지 (multiset일 때는 정확히 max_count)
  bool  multiset;    // 중복 조합 허용
  bool  exact;       // 정확히 max_count개(=true) / 0..max_count개(=false)
};

struct UnorderedPair { int a, b; }; // 대칭쌍 (예: 좌/우 g 교환)

// ---- 토폴로지 스펙 ----
struct TopoSpec {
  // 파라미터 뱅크
  ParamBank gbank, lbank, sbank, ibank; // G, L(interior), S, I(instanton)

  // 베이스 그래프
  const BaseNode* nodes; int n_nodes;
  const BaseEdge* edges; int n_edges;

  // 부착(옵션)
  const AttachRule* attaches; int n_attaches;

  // 대칭(옵션)
  const UnorderedPair* unordered_pairs; int n_unordered;

  // 출력
  const char* out_path;
};

// ----------------------- 유틸리티 -----------------------
static inline bool connect_safe(TheoryGraph& G, NodeRef a, NodeRef b){
  try { G.connect(a, b); return true; }
  catch (const std::invalid_argument&) { return false; }
}

// 정확히 k개 multiset 조합 (idx 비내림)
static void gen_multiset_combos(const int* vals, int N, int k,
                                std::vector<std::vector<int>>& out){
  if (k==0){ out.push_back({}); return; }
  std::vector<int> idx(k,0);
  while (true){
    std::vector<int> take; take.reserve(k);
    for (int t=0;t<k;t++) take.push_back(vals[idx[t]]);
    out.push_back(std::move(take));
    int pos=k-1;
    while (pos>=0 && idx[pos]==N-1) --pos;
    if (pos<0) break;
    int v = ++idx[pos];
    for (int t=pos+1;t<k;t++) idx[t]=v;
  }
}

static inline void append_matrix(const Eigen::MatrixXi& M, std::string& buf){
  for (int r=0;r<M.rows();++r){
    for (int c=0;c<M.cols();++c){
      if (c) buf.push_back(' ');
      buf += std::to_string(M(r,c));
    }
    buf.push_back('\n');
  }
  buf.push_back('\n'); // 블록 사이 빈 줄
}

// NOTE: 요구사항대로 I는 is(v)가 아니라 s(v)로 추가한다.
static inline NodeRef addNode(TheoryGraph& G, LKind k, int v){
  switch(k){
    case LKind::G: return G.add(n_(v));  // gauge
    case LKind::L: return G.add(i(v));   // interior link (표기는 L, 구현은 i(v))
    case LKind::S: return G.add(s(v));   // side
    case LKind::I: return G.add(s(v));   // instanton(파라미터로 구분)
  }
  return NodeRef{-1};
}

// ----------------------- SCFT 필터 -----------------------
static inline bool pass_filter_pre_and_post_zero_zero(const Eigen::MatrixXi& pre){
  Tensor T;
  T.SetIF(pre);
  T.Setb0Q();
  if (T.TimeDirection()!=0 || T.NullDirection()!=0) return false;
  T.ForcedBlowdown();
  return (T.TimeDirection()==0 && T.NullDirection()==0);
}

// ----------------------- 진행 카운터(전역) -----------------------
static std::atomic<long long> triple_done{0};  // (g,l,i) 완료 건수
static std::atomic<long long> tried{0};        // 실제 그래프 1건 시도 건수

// ----------------------- 공용 러너 -----------------------
void run_topology(const TopoSpec& S){
  // 노드 위치 파악
  std::vector<int> g_pos, l_pos, i_pos; // instanton은 i_pos에 수집
  g_pos.reserve(S.n_nodes); l_pos.reserve(S.n_nodes); i_pos.reserve(S.n_nodes);
  for (int ni=0; ni<S.n_nodes; ++ni){
    if (S.nodes[ni].kind==LKind::G) g_pos.push_back(ni);
    else if (S.nodes[ni].kind==LKind::L) l_pos.push_back(ni);
    else if (S.nodes[ni].kind==LKind::I) i_pos.push_back(ni);
  }
  const int NG = (int)g_pos.size();
  const int NL = (int)l_pos.size();
  const int NI = (int)i_pos.size(); // instanton count

  // 삼중 루프 분모(없으면 1로 보정)
  const long long GG = (long long)std::pow((double)S.gbank.N, NG);
  const long long LL = (long long)std::pow((double)S.lbank.N, NL);
  const long long II = (long long)std::pow((double)S.ibank.N, NI);
  const long long TRIPLE_TOTAL = std::max(1LL, GG * std::max(1LL, LL * std::max(1LL, II)));

  // 카운터 리셋(스펙별)
  triple_done.store(0, std::memory_order_relaxed);
  tried.store(0, std::memory_order_relaxed);

  std::string out; out.reserve(1<<24);
  long long accepted = 0;

#pragma omp parallel
  {
    std::string local; local.reserve(1<<22);
    long long loc_acc = 0;

#pragma omp for schedule(dynamic)
    for (long long g_flat=0; g_flat<(GG?GG:1); ++g_flat){
      // g 인덱스 전개
      std::vector<int> gsel(NG,0);
      if (GG){
        long long t = g_flat;
        for (int k=0;k<NG;k++){ gsel[k] = (int)(t % S.gbank.N); t /= S.gbank.N; }
      }

      for (long long l_flat=0; l_flat<(LL?LL:1); ++l_flat){
        std::vector<int> lsel(NL,0);
        if (LL){
          long long t = l_flat;
          for (int k=0;k<NL;k++){ lsel[k] = (int)(t % S.lbank.N); t /= S.lbank.N; }
        }

        for (long long i_flat=0; i_flat<(II?II:1); ++i_flat){
          std::vector<int> isel(NI,0);
          if (II){
            long long t = i_flat;
            for (int k=0;k<NI;k++){ isel[k] = (int)(t % S.ibank.N); t /= S.ibank.N; }
          }

          // --- 대칭성 필터 ---
          bool sym_ok = true;
          for (int u=0; u<S.n_unordered; ++u){
            const int a = S.unordered_pairs[u].a;
            const int b = S.unordered_pairs[u].b;
            int va=-1, vb=-1;
            for (int gi=0; gi<NG; ++gi){
              if (g_pos[gi]==a) va = S.gbank.vals[gsel[gi]];
              if (g_pos[gi]==b) vb = S.gbank.vals[gsel[gi]];
            }
            if (va!=-1 && vb!=-1 && !(vb<=va)) { sym_ok=false; break; }
          }
          if (!sym_ok){
            // (g,l,i) 1건 종료 → 진행 표시
            auto done = triple_done.fetch_add(1, std::memory_order_relaxed) + 1;
            if ((done % 50 == 0) && MASTER_THREAD){
              double pct = 100.0 * (double)done / (double)TRIPLE_TOTAL;
              std::printf("\r[%.2f%%] triples %lld / %lld  (tried=%lld)",
                          pct, done, TRIPLE_TOTAL, tried.load(std::memory_order_relaxed));
              std::fflush(stdout);
            }
            continue;
          }

          // --- 부착 선택지 생성 ---
          std::vector<std::vector<std::vector<int>>> choices(S.n_attaches);
          for (int r=0; r<S.n_attaches; ++r){
            const auto& R = S.attaches[r];
            std::vector<std::vector<int>> one;
            if (R.max_count==0){
              one.push_back({});
            } else if (R.multiset){
              if (R.exact){
                std::vector<std::vector<int>> tmp;
                gen_multiset_combos(S.sbank.vals, S.sbank.N, R.max_count, tmp); // 정확히 k
                one.insert(one.end(), tmp.begin(), tmp.end());
              } else {
                for (int k=0;k<=R.max_count;k++){
                  std::vector<std::vector<int>> tmp;
                  gen_multiset_combos(S.sbank.vals, S.sbank.N, k, tmp);        // 0..k
                  one.insert(one.end(), tmp.begin(), tmp.end());
                }
              }
            } else {
              // (ordered) exact만 쓰는 경우가 대부분. exact 아니면 0..k
              if (R.exact){
                std::vector<int> cur;
                std::function<void()> dfs = [&](){
                  if ((int)cur.size()==R.max_count){ one.push_back(cur); return; }
                  for (int i=0;i<S.sbank.N;++i){ cur.push_back(S.sbank.vals[i]); dfs(); cur.pop_back(); }
                };
                dfs();
              } else {
                one.push_back({}); // 0개
                for (int kk=1; kk<=R.max_count; ++kk){
                  std::vector<int> cur;
                  std::function<void()> dfs = [&](){
                    if ((int)cur.size()==kk){ one.push_back(cur); return; }
                    for (int i=0;i<S.sbank.N;++i){ cur.push_back(S.sbank.vals[i]); dfs(); cur.pop_back(); }
                  };
                  dfs();
                }
              }
            }
            choices[r] = std::move(one);
          }

          // 최대 3규칙까지 펼침 (필요시 늘려도 됨)
          const auto& W0 = (S.n_attaches>=1?choices[0]:std::vector<std::vector<int>>{{}});
          const auto& W1 = (S.n_attaches>=2?choices[1]:std::vector<std::vector<int>>{{}});
          const auto& W2 = (S.n_attaches>=3?choices[2]:std::vector<std::vector<int>>{{}});

          for (const auto& A0: W0)
          for (const auto& A1: W1)
          for (const auto& A2: W2)
          {
            TheoryGraph G;
            std::vector<NodeRef> ref(S.n_nodes);

            // base nodes
            int gi_ptr=0, li_ptr=0, ii_ptr=0;
            for (int ni=0; ni<S.n_nodes; ++ni){
              int v=0;
              switch (S.nodes[ni].kind){
                case LKind::G: v = (NG? S.gbank.vals[gsel[gi_ptr++]] : 0); break;
                case LKind::L: v = (NL? S.lbank.vals[lsel[li_ptr++]] : 0); break;
                case LKind::I: v = (NI? S.ibank.vals[isel[ii_ptr++]] : 0); break; // instanton도 값은 ibank에서
                case LKind::S: v = 0; break; // base에 S는 거의 안 씀
              }
              ref[ni] = addNode(G, S.nodes[ni].kind, v);
            }

            // base edges
            bool ok = true;
            for (int e=0; e<S.n_edges; ++e){
              ok &= connect_safe(G, ref[S.edges[e].u], ref[S.edges[e].v]);
            }
            if (!ok) goto AFTER_TRY; // 실패 시 tried 증가 없이 스킵

            // attachments
            for (int r=0; r<S.n_attaches; ++r){
              const auto& R = S.attaches[r];
              const auto& pack = (r==0?A0:(r==1?A1:A2));

              auto sorted = pack;
              if (R.multiset) std::sort(sorted.begin(), sorted.end());
              // exact 안전장치
              if (R.exact && (int)sorted.size()!=R.max_count){ ok=false; break; }

              for (int p: sorted){
                NodeRef a = addNode(G, R.kind, p);
                // (S(or I), host) 순서 → S는 항상 왼쪽 포트로 붙음
                if (!connect_safe(G, a, ref[R.host_idx])) { ok=false; break; }
              }
              if (!ok) break;
            }
            if (!ok) goto AFTER_TRY;

            // === 그래프 1건 "시도" 카운트 ===
            tried.fetch_add(1, std::memory_order_relaxed);

            // IF & 필터
            {
              Eigen::MatrixXi preIF = G.ComposeIF_UnitGluing();
              if (pass_filter_pre_and_post_zero_zero(preIF)){
                append_matrix(preIF, local);
                ++loc_acc;
              }
            }

            AFTER_TRY:
            ; // label target
          } // attachments product

          // (g,l,i) 1건 처리 완료 → 진행률 증가 & 표시
          {
            auto done = triple_done.fetch_add(1, std::memory_order_relaxed) + 1;
            if ((done % 50 == 0) && MASTER_THREAD){
              double pct = 100.0 * (double)done / (double)TRIPLE_TOTAL;
              std::printf("\r[%.2f%%] triples %lld / %lld  (tried=%lld)",
                          pct, done, TRIPLE_TOTAL, tried.load(std::memory_order_relaxed));
              std::fflush(stdout);
            }
          }
        } // i
      } // l
    } // g

#pragma omp critical
    { out.append(local); accepted += loc_acc; }
  } // parallel

  if (FILE* fp = std::fopen(S.out_path, "w")){
    std::fwrite(out.data(), 1, out.size(), fp);
    std::fclose(fp);
  }
  std::printf("\n[Report] %s accepted=%lld  (tried=%lld)\n",
              S.out_path, accepted, tried.load(std::memory_order_relaxed));
}

// ================= 파라미터 테이블 (프로젝트 값 유지) =================
static constexpr int G_BANK[] = {4,6,7,8,12};
static constexpr int L_BANK[] = {
  11,22,33,44,55,331,32,23,42,24,43,34,53,35,54,45
};
static constexpr int S_BANK[] = {
  1, 882, 883,884,885,886,887,8881,889,8810,8811,
  22, 33, 44, 55, 331, 32, 23, 42, 24, 43, 34, 53, 35, 54, 45,
  991, 9920, 9902, 993,
  91, 92, 93, 94, 95, 96, 97, 98, 99, 910, 911, 912, 913, 914, 915, 916, 917,
  99910, 99901, 99920, 99902, 99930, 99903,
  994, 995, 996, 997, 998, 999, 9910, 9911, 9912, 9913, 9914,
  918, 919, 920, 921, 922, 923, 924, 925, 926, 927,
  928, 929, 930, 931, 932, 933, 934, 935, 936, 937,
  938, 939, 940, 941, 942, 943, 944, 945,
  9915, 9916, 9917,
  946, 947, 948, 949, 950, 951, 952, 953, 954, 955, 956, 957
};
static constexpr int I_BANK[] = {1, 882, 883,884,885,886,887,8881,889,8810,8811};

// ================= 베이스 스켈레톤 =================
static constexpr BaseNode NODES_GLG[] = { {LKind::G},{LKind::L},{LKind::G} };
static constexpr BaseEdge EDGES_GLG[] = { {0,1},{1,2} };
static constexpr UnorderedPair SYM_LR_G[] = { {0,2} };  // 좌/우 g 교환(필요 시)

// ================= 스펙들 =================
// (A) g–L–g : 부착 없음 (대칭 ON 예시)
static const TopoSpec SPEC_gLg {
  {G_BANK, int(sizeof(G_BANK)/sizeof(G_BANK[0]))},
  {L_BANK, int(sizeof(L_BANK)/sizeof(L_BANK[0]))},
  {S_BANK, int(sizeof(S_BANK)/sizeof(S_BANK[0]))},
  {I_BANK, int(sizeof(I_BANK)/sizeof(I_BANK[0]))},
  NODES_GLG, 3, EDGES_GLG, 2,
  nullptr, 0,
  SYM_LR_G, 1,
  "SCFT_gLg.txt"
};

// (B) SgLg : 왼쪽 g(0)에 S 정확히 1개 (비대칭 → 대칭 OFF)
static constexpr AttachRule ATT_SgLg[] = { {0, LKind::S, 1, true, true} };
static const TopoSpec SPEC_SgLg {
  {G_BANK, int(sizeof(G_BANK)/sizeof(G_BANK[0]))},
  {L_BANK, int(sizeof(L_BANK)/sizeof(L_BANK[0]))},
  {S_BANK, int(sizeof(S_BANK)/sizeof(S_BANK[0]))},
  {I_BANK, int(sizeof(I_BANK)/sizeof(I_BANK[0]))},
  NODES_GLG, 3, EDGES_GLG, 2,
  ATT_SgLg, 1,
  nullptr, 0,
  "SCFT_SgLg.txt"
};

// (C) SgLgS 
static constexpr AttachRule ATT_SgLgS[] = { {0, LKind::S, 1, true, true}, {2, LKind::S, 1, true, true} };
static const TopoSpec SPEC_SgLgS {
  {G_BANK, int(sizeof(G_BANK)/sizeof(G_BANK[0]))},
  {L_BANK, int(sizeof(L_BANK)/sizeof(L_BANK[0]))},
  {S_BANK, int(sizeof(S_BANK)/sizeof(S_BANK[0]))},
  {I_BANK, int(sizeof(I_BANK)/sizeof(I_BANK[0]))},
  NODES_GLG, 3, EDGES_GLG, 2,
  ATT_SgLgS, 2,           // 규칙 2개
  SYM_LR_G, 1,            // 좌/우 g 교환 대칭 허용
  "SCFT_SgLgS.txt"
};

// (D) SSgLg : 왼쪽 g(0)에 S 정확히 2개 (비대칭 → 대칭 OFF)
static constexpr AttachRule ATT_SSgLg[] = { {0, LKind::S, 2, true, true} };
static const TopoSpec SPEC_SSgLg {
  {G_BANK, int(sizeof(G_BANK)/sizeof(G_BANK[0]))},
  {L_BANK, int(sizeof(L_BANK)/sizeof(L_BANK[0]))},
  {S_BANK, int(sizeof(S_BANK)/sizeof(S_BANK[0]))},
  {I_BANK, int(sizeof(I_BANK)/sizeof(I_BANK[0]))},
  NODES_GLG, 3, EDGES_GLG, 2,
  ATT_SSgLg, 1,
  nullptr, 0,
  "SCFT_SSgLg.txt"
};

// (E) SSgLgS : 왼쪽 g에 S=2, 오른쪽 g에 S=1 (비대칭 → 대칭 OFF)
static constexpr AttachRule ATT_SSgLgS[] = { {0, LKind::S, 2, true, true}, {2, LKind::S, 1, true, true} };
static const TopoSpec SPEC_SSgLgS {
  {G_BANK, int(sizeof(G_BANK)/sizeof(G_BANK[0]))},
  {L_BANK, int(sizeof(L_BANK)/sizeof(L_BANK[0]))},
  {S_BANK, int(sizeof(S_BANK)/sizeof(S_BANK[0]))},
  {I_BANK, int(sizeof(I_BANK)/sizeof(I_BANK[0]))},
  NODES_GLG, 3, EDGES_GLG, 2,
  ATT_SSgLgS, 2,          // 규칙 2개
  nullptr, 0,
  "SCFT_SSgLgS.txt"
};

// (F) SSgLIgS : 왼쪽 g S=2, 오른쪽 g S=1 + 오른쪽 g에 instanton 1개 (비대칭 → 대칭 OFF)
static constexpr AttachRule ATT_SSgLIgS[] = {
  {0, LKind::S, 2, true, true},   // left g: 2 S
  {2, LKind::S, 1, true, true},   // right g: 1 S
  {2, LKind::I, 1, true, true}    // right g: 1 instanton (I도 s(v)로 추가됨)
};
static const TopoSpec SPEC_SSgLIgS {
  {G_BANK, int(sizeof(G_BANK)/sizeof(G_BANK[0]))},
  {L_BANK, int(sizeof(L_BANK)/sizeof(L_BANK[0]))},
  {S_BANK, int(sizeof(S_BANK)/sizeof(S_BANK[0]))},
  {I_BANK, int(sizeof(I_BANK)/sizeof(I_BANK[0]))},
  NODES_GLG, 3, EDGES_GLG, 2,
  ATT_SSgLIgS, 3,         // 규칙 3개
  nullptr, 0,
  "SCFT_SgLIgS.txt"
};

int main(){
  run_topology(SPEC_gLg);
  run_topology(SPEC_SgLg);
  run_topology(SPEC_SgLgS);
  run_topology(SPEC_SSgLg);
  run_topology(SPEC_SSgLgS);
  run_topology(SPEC_SSgLIgS);
  return 0;
}

