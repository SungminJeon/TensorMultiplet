#ifndef TRANSITION_RUNTIME_H
#define TRANSITION_RUNTIME_H

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <initializer_list>
#include <cstdint>
#include <functional>
#include <string>
#include <sstream>
#include <cstdio>

// ---------- 외부(Theory.h / topology_node2_2.C)에 있는 타입/함수들 사용 가정 ----------
// enum class LKind : int;               // 노드 종류 (G, L, I, S 등)
// struct TopoSpec { ... };              // 토폴로지 스펙 (노드/엣지/부착/뱅크들)
// struct TheoryGraph { ... };           // 그래프 본체
// struct NodeRef { ... };               // 그래프의 노드 핸들
// NodeRef addNode(TheoryGraph&, LKind, int);
// bool connect_safe(TheoryGraph&, NodeRef, NodeRef);
// Eigen::MatrixXi pass_filter_pre_and_post_zero_zero(const Eigen::MatrixXi&);

// ---------- 파라미터 도메인 표현 ----------
struct ParamSet {
  struct Range {
    int lo, hi; // [lo, hi] (양끝 포함)
  };
  std::vector<Range> ranges;

  ParamSet() = default;
  ParamSet(std::initializer_list<Range> rr){ 
    for (auto r : rr) addRange(r.lo, r.hi);
    normalize();
  }

  bool empty() const { return ranges.empty(); }

  void addRange(int a, int b){
    if (a>b) std::swap(a,b);
    ranges.push_back({a,b});
  }

  // 정렬/병합
  void normalize(){
    if (ranges.empty()) return;
    std::sort(ranges.begin(), ranges.end(),
              [](const Range& A, const Range& B){
                if (A.lo != B.lo) return A.lo < B.lo;
                return A.hi < B.hi;
              });
    std::vector<Range> merged; merged.reserve(ranges.size());
    Range cur = ranges[0];
    for (size_t i=1;i<ranges.size();++i){
      const auto& r = ranges[i];
      if (r.lo <= cur.hi+1){
        cur.hi = std::max(cur.hi, r.hi);
      } else {
        merged.push_back(cur);
        cur = r;
      }
    }
    merged.push_back(cur);
    ranges.swap(merged);
  }

  bool contains(int x) const {
    for (auto& r: ranges){
      if (x<r.lo) break;
      if (r.lo<=x && x<=r.hi) return true;
    }
    return false;
  }

  // 교집합
  void intersectWith(const ParamSet& o){
    std::vector<Range> out;
    size_t i=0, j=0;
    while (i<ranges.size() && j<o.ranges.size()){
      int L = std::max(ranges[i].lo, o.ranges[j].lo);
      int R = std::min(ranges[i].hi, o.ranges[j].hi);
      if (L<=R) out.push_back({L,R});
      if (ranges[i].hi < o.ranges[j].hi) ++i; else ++j;
    }
    ranges.swap(out);
  }
};

// 열거(모든 점 값)
static inline std::vector<int> enumerate(const ParamSet& ps){
  std::vector<int> v;
  for (auto& r: ps.ranges){
    for (int x=r.lo; x<=r.hi; ++x) v.push_back(x);
  }
  return v;
}

// ---------- 전이 DB ----------
enum class EdgeType : int { NodeToNode=0, SideToNode=1, InteriorToNode=2 };

struct TransitionKey {
  EdgeType et;
  LKind    fromK;
  LKind    toK;
};

struct KeyHash {
  size_t operator()(const TransitionKey& k) const {
    // LKind는 enum class 라고 가정 — 정수로 캐스팅
    return (size_t)k.et*1315423911u ^ ((size_t)k.fromK<<8) ^ (size_t)k.toK;
  }
};
struct KeyEq {
  bool operator()(const TransitionKey& a, const TransitionKey& b) const {
    return a.et==b.et && a.fromK==b.fromK && a.toK==b.toK;
  }
};

struct TransitionRule {
  // from 값 -> 허용되는 to 값들의 ParamSet
  std::unordered_map<int, ParamSet> map;
};

struct TransitionDB {
  std::unordered_map<TransitionKey, TransitionRule, KeyHash, KeyEq> rules_;

  void addRule(EdgeType et, LKind fk, LKind tk, int from, ParamSet ps){
    TransitionKey K{et,fk,tk};
    rules_[K].map[from] = std::move(ps);
  }

  const ParamSet* nextBanks(EdgeType et, LKind fk, int from, LKind tk) const {
    TransitionKey K{et,fk,tk};
    auto it = rules_.find(K);
    if (it==rules_.end()) return nullptr;
    auto it2 = it->second.map.find(from);
    if (it2==it->second.map.end()) return nullptr;
    return &it2->second;
  }
};

// ---------- TDSpec (전파용 경량 스펙) ----------
struct TDSEdge { int u, v; EdgeType et; };

struct TDSpec {
  const char* out_path = nullptr;
  std::vector<LKind>    kinds;      // 노드 kinds
  std::vector<ParamSet> domains;    // 각 노드 도메인
  std::vector<TDSEdge>  edges;      // 전파 엣지
  // 같은 그룹은 비내림(<=) 제약으로 permutation 중복 컷
  std::vector<std::vector<int>> sym_groups;
};

// ---------- 은행 → 도메인 ----------
template<typename Bank>
static inline ParamSet makeDomainFromBank(const Bank& B){
  ParamSet ps;
  if (B.N<=0) return ps;
  // 개별 값들을 점구간으로 추가한 뒤 normalize하여 압축
  for (int i=0;i<B.N;++i) ps.addRange(B.vals[i], B.vals[i]);
  ps.normalize();
  return ps;
}

// ---------- TopoSpec을 TDSpec으로 변환 (부착 확장 포함) ----------
// TopoSpec의 필드 가정:
//   - out_path, n_nodes, nodes[i].kind
//   - gbank/lbank/ibank/sbank  (N, vals)
//   - n_edges, edges[e].u, edges[e].v
//   - n_attaches, attaches[r].kind, attaches[r].host_idx, attaches[r].max_count, attaches[r].multiset
static inline TDSpec buildTDSpecFromTopo(const TopoSpec& S){
  TDSpec T;
  T.out_path = S.out_path;

  // 기존 노드 올림
  for (int i=0;i<S.n_nodes;++i){
    T.kinds.push_back(S.nodes[i].kind);
    switch (S.nodes[i].kind){
      case LKind::G: T.domains.push_back(makeDomainFromBank(S.gbank)); break;
      case LKind::L: T.domains.push_back(makeDomainFromBank(S.lbank)); break;
      case LKind::I: T.domains.push_back(makeDomainFromBank(S.ibank)); break;
      case LKind::S: T.domains.push_back(makeDomainFromBank(S.sbank)); break;
    }
  }
  // 기존 엣지 올림 (노드-노드로 가정)
  for (int e=0;e<S.n_edges;++e){
    T.edges.push_back({S.edges[e].u, S.edges[e].v, EdgeType::NodeToNode});
  }

  // 부착 규칙을 실제 노드로 확장: max_count 만큼 생성하여 host와 연결
  for (int r=0;r<S.n_attaches;++r){
    const auto& R = S.attaches[r];
    const int k = std::max(1, R.max_count);
    std::vector<int> pack; pack.reserve(k);

    for (int t=0;t<k;++t){
      int nid = (int)T.kinds.size();
      T.kinds.push_back(R.kind);
      switch (R.kind){
        case LKind::S: T.domains.push_back(makeDomainFromBank(S.sbank)); break;
        case LKind::I: T.domains.push_back(makeDomainFromBank(S.ibank)); break;
        case LKind::L: T.domains.push_back(makeDomainFromBank(S.lbank)); break;
        case LKind::G: T.domains.push_back(makeDomainFromBank(S.gbank)); break;
      }
      EdgeType et = (R.kind==LKind::S? EdgeType::SideToNode
                   : (R.kind==LKind::I? EdgeType::InteriorToNode
                                       : EdgeType::NodeToNode));
      T.edges.push_back({nid, R.host_idx, et});
      pack.push_back(nid);
    }

    // multiset(무순서)이면 같은 묶음을 대칭그룹으로 등록 (비내림 컷)
    if (R.kind==LKind::S && R.multiset && (int)pack.size()>=2){
      std::sort(pack.begin(), pack.end());
      T.sym_groups.push_back(std::move(pack));
    }
  }
  return T;
}

// ---------- 대칭군(같은 그룹 비내림) 위반 컷 ----------
static inline bool violatesSymGroups(const TDSpec& T,
                                     const std::vector<bool>& fixed,
                                     const std::vector<int>&  val){
  for (const auto& grp : T.sym_groups){
    int prev = -0x3f3f3f3f; bool first=true;
    for (int idx : grp){
      if (!fixed[idx]) continue;
      if (first){ prev=val[idx]; first=false; }
      else{
        if (prev > val[idx]) return true;
        prev = val[idx];
      }
    }
  }
  return false;
}

// ---------- 빠른 공백 체크 ----------
static inline bool quickCheck(const std::vector<ParamSet>& dom){
  for (auto& d: dom) if (d.empty()) return false;
  return true;
}

// ---------- 변수 선택: 가장 작은 도메인 ----------
static inline int pickVar(const std::vector<bool>& fixed,
                          const std::vector<ParamSet>& dom){
  int best=-1;
  size_t bestN = SIZE_MAX;
  for (int i=0;i<(int)dom.size();++i){
    if (fixed[i]) continue;
    size_t n=0;
    for (auto& r: dom[i].ranges) n += (size_t)(r.hi - r.lo + 1);
    if (n<bestN){ bestN=n; best=i; }
  }
  return best;
}

// ---------- 전파(단방향: S/I -> host, 그외는 i가 엣지 끝점일 때만) ----------
static inline bool reduceByTransition(const TransitionDB& DB,
                                      const TDSpec& T,
                                      int u, int v,
                                      const std::vector<bool>& fixed,
                                      const std::vector<int>&  val,
                                      std::vector<ParamSet>& dom,
                                      EdgeType et)
{
  // u가 아직 고정 아니면 여기선 전파하지 않음 (DFS에서 u를 막 셋한 경우에만 호출하도록 설계)
  if (!fixed[u]) return true;

  const ParamSet* p = DB.nextBanks(et, T.kinds[u], val[u], T.kinds[v]);
  if (!p) { 
    // 규칙 없으면 제한 없음 (현재 정책)
    return true;
  }
  dom[v].intersectWith(*p);
  return !dom[v].empty();
}

// ---------- IF 생성 + SCFT 판정 ----------
static inline bool build_if_and_check_scft(const TDSpec& T,
                                           const std::vector<int>& val,
                                           Eigen::MatrixXi& outIF){
  TheoryGraph G;
  std::vector<NodeRef> ref(T.kinds.size());
  for (int i=0;i<(int)T.kinds.size();++i){
    ref[i] = addNode(G, T.kinds[i], val[i]);
  }
  for (const auto& e: T.edges){
    if (!connect_safe(G, ref[e.u], ref[e.v])) return false;
  }
  outIF = G.ComposeIF_UnitGluing();
  return pass_filter_pre_and_post_zero_zero(outIF);
}

// ---------- 메인 DFS ----------
static inline void run_topology_transition(const TopoSpec& S, const TransitionDB& DB){
  TDSpec T = buildTDSpecFromTopo(S);
  std::vector<ParamSet> dom = T.domains;
  std::vector<bool> fixed(T.kinds.size(), false);
  std::vector<int>  val  (T.kinds.size(), 0);

  std::string out; out.reserve(1<<24);
  long long accepted=0, tried_local=0;

  std::function<void(void)> dfs = [&](){
    int i = pickVar(fixed, dom);
    if (i<0){
      ++tried_local;
      Eigen::MatrixXi preIF;
      if (build_if_and_check_scft(T, val, preIF)){
        // IF 행렬 블록 출력
        for (int r=0;r<preIF.rows();++r){
          for (int c=0;c<preIF.cols();++c){
            if (c) out.push_back(' ');
            out += std::to_string(preIF(r,c));
          }
          out.push_back('\n');
        }
        out.push_back('\n');
        ++accepted;
      }
      return;
    }

    // 도메인 열거
    auto cand = enumerate(dom[i]);
    for (int x : cand){
      auto dom_bak = dom;
      auto fix_bak = fixed;
      auto val_bak = val;

      fixed[i]=true; val[i]=x;
      bool ok=true;

      // 엣지 전파
      for (const auto& e: T.edges){
        if (e.et==EdgeType::SideToNode){
          // S -> G (host) 단방향 전파
          if (T.kinds[e.u]==LKind::S && e.u==i){
            ok &= reduceByTransition(DB, T, e.u, e.v, fixed, val, dom, e.et);
          } else if (T.kinds[e.v]==LKind::S && e.v==i){
            ok &= reduceByTransition(DB, T, e.v, e.u, fixed, val, dom, e.et);
          }
          if (!ok) break;
          continue;
        }
        if (e.et==EdgeType::InteriorToNode){
          // I -> host 단방향 전파
          if (T.kinds[e.u]==LKind::I && e.u==i){
            ok &= reduceByTransition(DB, T, e.u, e.v, fixed, val, dom, e.et);
          } else if (T.kinds[e.v]==LKind::I && e.v==i){
            ok &= reduceByTransition(DB, T, e.v, e.u, fixed, val, dom, e.et);
          }
          if (!ok) break;
          continue;
        }
        // NodeToNode는 i가 끝점일 때만 양방향 전파
        if (e.u==i){
          ok &= reduceByTransition(DB, T, e.u, e.v, fixed, val, dom, e.et);
          if (!ok) break;
        }
        if (e.v==i){
          ok &= reduceByTransition(DB, T, e.v, e.u, fixed, val, dom, e.et);
          if (!ok) break;
        }
      }

      if (ok && !violatesSymGroups(T, fixed, val) && quickCheck(dom))
        dfs();

      dom.swap(dom_bak); fixed.swap(fix_bak); val.swap(val_bak);
    }
  };

  dfs();

  if (FILE* fp = std::fopen(S.out_path, "w")){
    std::fwrite(out.data(), 1, out.size(), fp);
    std::fclose(fp);
  }
  std::printf("\n[Transition] %s accepted=%lld  (tried=%lld)\n",
              S.out_path, accepted, tried_local);
}
static inline TransitionDB make_example_DB(){
  TransitionDB T;
 
  T.addRule(EdgeType::NodeToNode,   LKind::G, LKind::L,  4,  ParamSet{ { {11,11},{22,22},{32,32},{23,23},{33,33},{24,24},{331,331},{34,34},{35,35} } } );
  T.addRule(EdgeType::NodeToNode,   LKind::G, LKind::L, 6,  ParamSet{ { {22,22},{32,32},{33,33},{42,42},{331,331},{43,43},{34,34},{44,44},{53,53},{35,35},{45,45},{54,54},{55,55} } } );
  T.addRule(EdgeType::NodeToNode,   LKind::G, LKind::L, 7,  ParamSet{ { {32,32},{33,33},{42,42},{43,43},{44,44},{53,53},{54,54},{45,45},{55,55} } } );
  T.addRule(EdgeType::NodeToNode,LKind::G, LKind::L, 8,  ParamSet{ { {32,32},{33,33},{42,42},{43,43},{44,44},{53,53},{54,54},{45,45},{55,55} } } );
  T.addRule(EdgeType::NodeToNode,LKind::G, LKind::L, 12,  ParamSet{ { {42,42},{53,53},{54,54},{55,55} } } );

  T.addRule(EdgeType::NodeToNode,LKind::L, LKind::G, 11,  ParamSet{ { {4,4} } } );
  T.addRule(EdgeType::NodeToNode,LKind::L, LKind::G, 22,  ParamSet{ { {4,4},{6,6} } } );
  T.addRule(EdgeType::NodeToNode,LKind::L, LKind::G, 32,  ParamSet{ { {4,4} } } );
  T.addRule(EdgeType::NodeToNode,LKind::L, LKind::G, 23,  ParamSet{ { {4,4},{6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::NodeToNode,LKind::L, LKind::G, 33,  ParamSet{ { {4,4},{6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::NodeToNode,LKind::L, LKind::G, 42,  ParamSet{ { {4,4} } } );
  T.addRule(EdgeType::NodeToNode,LKind::L, LKind::G, 24,  ParamSet{ { {6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::NodeToNode,LKind::L, LKind::G, 331,  ParamSet{ { {4,4},{6,6} } } );
  T.addRule(EdgeType::NodeToNode,LKind::L, LKind::G, 43,  ParamSet{ { {4,4},{6,6} } } );
  T.addRule(EdgeType::NodeToNode,LKind::L, LKind::G, 34,  ParamSet{ { {6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::NodeToNode,LKind::L, LKind::G, 44,  ParamSet{ { {6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::NodeToNode,LKind::L, LKind::G, 53,  ParamSet{ { {4,4},{6,6} } } );
  T.addRule(EdgeType::NodeToNode,LKind::L, LKind::G, 35,  ParamSet{ { {6,6},{7,7},{8,8},{12,12} } } );
  T.addRule(EdgeType::NodeToNode,LKind::L, LKind::G, 54,  ParamSet{ { {6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::NodeToNode,LKind::L, LKind::G, 45,  ParamSet{ { {6,6},{7,7},{8,8},{12,12} } } );
  T.addRule(EdgeType::NodeToNode,LKind::L, LKind::G, 55,  ParamSet{ { {6,6},{7,7},{8,8},{12,12} } } );
  
  //side links
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 11,  ParamSet{ { {4,4} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 22,  ParamSet{ { {4,4},{6,6} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 32,  ParamSet{ { {4,4} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 23,  ParamSet{ { {4,4},{6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 33,  ParamSet{ { {4,4},{6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 42,  ParamSet{ { {4,4} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 24,  ParamSet{ { {6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 331,  ParamSet{ { {4,4},{6,6} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 43,  ParamSet{ { {4,4},{6,6} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 34,  ParamSet{ { {6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 44,  ParamSet{ { {6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 53,  ParamSet{ { {4,4},{6,6} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 35,  ParamSet{ { {6,6},{7,7},{8,8},{12,12} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 54,  ParamSet{ { {6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 45,  ParamSet{ { {6,6},{7,7},{8,8},{12,12} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 55,  ParamSet{ { {6,6},{7,7},{8,8},{12,12} } } );
  
  // alkai 2-links with no -5 curves
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 991,  ParamSet{ { {4,4} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 9920,  ParamSet{ { {4,4} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 9902,  ParamSet{ { {4,4} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 993,  ParamSet{ { {6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 91,  ParamSet{ { {7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 92,  ParamSet{ { {4,4} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 93,  ParamSet{ { {4,4},{6,6},{7,7},{8,8},{12,12} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 94,  ParamSet{ { {7,7},{8,8},{12,12} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 95,  ParamSet{ { {7,7},{8,8},{12,12} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 96,  ParamSet{ { {6,6},{7,7},{8,8},{12,12} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 97,  ParamSet{ { {4,4},{6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 98,  ParamSet{ { {4,4},{6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 99,  ParamSet{ { {6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 910,  ParamSet{ { {7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 911,  ParamSet{ { {6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 912,  ParamSet{ { {4,4},{6,6} } } );
  
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 913,  ParamSet{ { {6,6} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 914,  ParamSet{ { {6,6} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 915,  ParamSet{ { {4,4},{6,6} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 916,  ParamSet{ { {4,4} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 917,  ParamSet{ { {4,4} } } );
  
  // instantons are not included. Those are rejected by the gluing rules of Theory class 

  // alkali 3-links with one -5 curve
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 99910,  ParamSet{ { {4,4},{6,6} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 99901,  ParamSet{ { {4,4},{6,6} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 99920,  ParamSet{ { {6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 99902,  ParamSet{ { {6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 99930,  ParamSet{ { {6,6},{7,7},{8,8},{12,12} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 99903,  ParamSet{ { {6,6},{7,7},{8,8},{12,12} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 994,  ParamSet{ { {6,6} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 995,  ParamSet{ { {6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 996,  ParamSet{ { {7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 997,  ParamSet{ { {7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 998,  ParamSet{ { {7,7},{8,8},{12,12} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 999,  ParamSet{ { {12,12} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 9910,  ParamSet{ { {6,6} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 9911,  ParamSet{ { {7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 9912,  ParamSet{ { {6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 9913,  ParamSet{ { {4,4},{6,6},{7,7},{8,8} } } );
  
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 9914,  ParamSet{ { {6,6},{7,7},{8,8} } } );

  // alkali 1-links with one -5 curve
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 918,  ParamSet{ { {6,6},{7,7},{8,8},{12,12} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 919,  ParamSet{ { {7,7},{8,8},{12,12} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 920,  ParamSet{ { {6,6},{7,7},{8,8},{12,12} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 921,  ParamSet{ { {6,6},{7,7},{8,8},{12,12} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 922,  ParamSet{ { {6,6},{7,7},{8,8},{12,12} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 923,  ParamSet{ { {7,7},{8,8},{12,12} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 924,  ParamSet{ { {4,4},{6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 925,  ParamSet{ { {4,4},{6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 926,  ParamSet{ { {6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 927,  ParamSet{ { {7,7},{8,8},{12,12} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 928,  ParamSet{ { {4,4},{6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 929,  ParamSet{ { {4,4},{6,6},{7,7},{8,8} } } );

  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 930,  ParamSet{ { {7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 931,  ParamSet{ { {7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 932,  ParamSet{ { {7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 933,  ParamSet{ { {6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 934,  ParamSet{ { {4,4},{6,6} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 935,  ParamSet{ { {6,6} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 936,  ParamSet{ { {4,4},{6,6} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 937,  ParamSet{ { {4,4},{6,6} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 938,  ParamSet{ { {4,4},{6,6} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 939,  ParamSet{ { {6,6} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 940,  ParamSet{ { {4,4} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 941,  ParamSet{ { {4,4} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 942,  ParamSet{ { {4,4} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 943,  ParamSet{ { {4,4},{6,6} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 944,  ParamSet{ { {6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 945,  ParamSet{ { {6,6},{7,7},{8,8},{12,12} } } );


  // alkali 2 links with two -5 curves
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 9915,  ParamSet{ { {7,7},{8,8},{12,12} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 9916,  ParamSet{ { {6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 9917,  ParamSet{ { {6,6} } } );

  // alkali 1-links with two -5 curves
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 946,  ParamSet{ { {7,7},{8,8},{12,12} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 947,  ParamSet{ { {6,6},{7,7},{8,8},{12,12} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 948,  ParamSet{ { {12,12} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 949,  ParamSet{ { {12,12} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 950,  ParamSet{ { {7,7},{8,8},{12,12} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 951,  ParamSet{ { {6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 952,  ParamSet{ { {6,6},{7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 953,  ParamSet{ { {7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 954,  ParamSet{ { {7,7},{8,8} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 955,  ParamSet{ { {6,6} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 956,  ParamSet{ { {4,4},{6,6} } } );
  T.addRule(EdgeType::SideToNode,LKind::S, LKind::G, 957,  ParamSet{ { {6,6} } } );
  


 

  return T;
}

#endif // TRANSITION_RUNTIME_H

