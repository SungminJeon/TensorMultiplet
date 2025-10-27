// topology_test.C
#pragma once
#include <cstddef>
#include <cstdint>     // for fixed-size ints and (previously) SIZE_MAX
#include <limits>      // std::numeric_limits
#include <cstdio>      // std::snprintf
#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>    // if you want std::size for arrays
#include <string_view>
#include <functional>
#include <fstream>
#include <optional>
#include <sstream>

#include <Eigen/Dense>
#include "Tensor.h"
#include "Theory.h"

// avoid exceptions bubbling up
static inline bool safe_connect(TheoryGraph &G, NodeRef a, NodeRef b) noexcept {
    try { G.connect(a, b); return true; }
    catch (const std::invalid_argument&) { return false; }
}

// gluing name toggle
static inline Eigen::MatrixXi compose_glue(const TheoryGraph& G) {
#if USE_UNIT_GLUING
    return G.ComposeIF_UnitGluing();
#else
    return G.ComposeIF_Gluing();
#endif
}

// evaluate_and_append는 이전 sink 버전 그대로
static inline bool evaluate_and_append(
    const Eigen::MatrixXi &glued,
    const std::function<void(std::string_view)> &sink)
{
    Tensor g;
    g.SetIF(glued);
    g.Setb0Q();

    // quick cut (before blowdown)
    // if (g.TimeDirection() != 0 || g.NullDirection() != 0) return false;

    const Eigen::MatrixXi IF0 = g.GetIntersectionForm();

    // validate with blowdown (not saved)
    g.ForcedBlowdown();
    if (g.TimeDirection() != 0 || g.NullDirection() != 0)
        return false;

    const int R = IF0.rows(), C = IF0.cols();
    char buf[32];
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            if (c) sink(" ");
            int len = std::snprintf(buf, sizeof(buf), "%d", IF0(r, c));
            sink(std::string_view(buf, (size_t)len));
        }
        sink("\n");
    }
    sink("\n");
    return true;
}

enum LKind { g, L, S, I };

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

const int numS = (int)(sizeof(S_BANK)/sizeof(S_BANK[0]));
const int numI = (int)(sizeof(I_BANK)/sizeof(I_BANK[0]));
const int numG = (int)(sizeof(G_BANK)/sizeof(G_BANK[0]));
const int numL = (int)(sizeof(L_BANK)/sizeof(L_BANK[0]));

struct IntView {
  const int* data = nullptr;
  std::size_t size = 0;
  bool empty() const { return size==0; }
};

// 안전한 array-size 매크로 (std::size 비의존)
#define RET_ARR(...) do { \
  static constexpr int A__[] = { __VA_ARGS__ }; \
  return IntView{A__, (std::size_t)(sizeof(A__)/sizeof(A__[0]))}; \
} while(0)

// =====================================================
// (타입, 파라미터) -> 허용 집합
// =====================================================
[[nodiscard]] inline IntView allowed(LKind k, int param)
{
  // ---------- g(kind) -> 허용 L ----------
  if (k==g){
    switch(param){
      case 4:  RET_ARR(11,22,32,23,33,24,331,34,35);
      case 6:  RET_ARR(22,32,33,42,331,43,34,44,53,35,45,54,55);
      case 7:  RET_ARR(32,33,42,43,44,53,54,45,55);
      case 8:  RET_ARR(32,33,42,43,44,53,54,45,55);
      case 12: RET_ARR(42,53,54,55);
      default: return {};
    }
  }

  // ---------- L(kind) -> 허용 g ----------
  if (k==L){
    switch(param){
      case 11:  RET_ARR(4);
      case 22:  RET_ARR(4,6);
      case 32:  RET_ARR(4);
      case 23:  RET_ARR(4,6,7,8);
      case 33:  RET_ARR(4,6,7,8);
      case 42:  RET_ARR(4);
      case 24:  RET_ARR(6,7,8,12);
      case 331: RET_ARR(4,6);
      case 43:  RET_ARR(4,6);
      case 34:  RET_ARR(6,7,8);
      case 44:  RET_ARR(6,7,8);
      case 53:  RET_ARR(4,6);
      case 35:  RET_ARR(6,7,8,12);
      case 54:  RET_ARR(6,7,8);
      case 45:  RET_ARR(6,7,8,12);
      case 55:  RET_ARR(6,7,8,12);
      default: return {};
    }
  }

  // ---------- S(kind) -> 허용 g ----------
  if (k==S){
    switch(param){
      // side links (S와 L 동일 규칙 구간)
      case 11:  RET_ARR(4);
      case 22:  RET_ARR(4,6);
      case 32:  RET_ARR(4);
      case 23:  RET_ARR(4,6,7,8);
      case 33:  RET_ARR(4,6,7,8);
      case 42:  RET_ARR(4);
      case 24:  RET_ARR(6,7,8,12);
      case 331: RET_ARR(4,6);
      case 43:  RET_ARR(4,6);
      case 34:  RET_ARR(6,7,8);
      case 44:  RET_ARR(6,7,8);
      case 53:  RET_ARR(4,6);
      case 35:  RET_ARR(6,7,8,12);
      case 54:  RET_ARR(6,7,8);
      case 45:  RET_ARR(6,7,8,12);
      case 55:  RET_ARR(6,7,8,12);
      // 이하 생략 없이 원문 그대로…
      case 991:  RET_ARR(4);
      case 9920: RET_ARR(4);
      case 9902: RET_ARR(4);
      case 993:  RET_ARR(6,7,8);
      case 91:   RET_ARR(8);
      case 92:   RET_ARR(4);
      case 93:   RET_ARR(4,6,7,8,12);
      case 94:   RET_ARR(7,8,12);
      case 95:   RET_ARR(7,8,12);
      case 96:   RET_ARR(6,7,8,12);
      case 97:   RET_ARR(4,6,7,8);
      case 98:   RET_ARR(4,6,7,8);
      case 99:   RET_ARR(6,7,8);
      case 910:  RET_ARR(7,8);
      case 911:  RET_ARR(6,7,8);
      case 912:  RET_ARR(4,6);
      case 913:  RET_ARR(6);
      case 914:  RET_ARR(6);
      case 915:  RET_ARR(4,6);
      case 916:  RET_ARR(4);
      case 917:  RET_ARR(4);
      case 99910: RET_ARR(4,6);
      case 99920: RET_ARR(6,7,8);
      case 99930: RET_ARR(6,7,8,12);
      case 994:   RET_ARR(6);
      case 995:   RET_ARR(6,7,8);
      case 996:   RET_ARR(7,8,12);
      case 997:   RET_ARR(7,8);
      case 998:   RET_ARR(7,8,12);
      case 999:   RET_ARR(12);
      case 9910:  RET_ARR(6);
      case 9911:  RET_ARR(7,8);
      case 9912:  RET_ARR(6,7,8,12);
      case 9913:  RET_ARR(4,6,7,8);
      case 9914:  RET_ARR(6,7,8);
      case 918:  RET_ARR(6,7,8,12);
      case 919:  RET_ARR(7,8,12);
      case 920:  RET_ARR(6,7,8,12);
      case 921:  RET_ARR(6,7,8,12);
      case 922:  RET_ARR(6,7,8,12);
      case 923:  RET_ARR(7,8,12);
      case 924:  RET_ARR(4,6,7,8);
      case 925:  RET_ARR(4,6,7,8);
      case 926:  RET_ARR(6,7,8);
      case 927:  RET_ARR(4,6,7,8);
      case 928:  RET_ARR(4,6,7,8);
      case 929:  RET_ARR(4,6,7,8);
      case 930:  RET_ARR(7,8);
      case 931:  RET_ARR(7,8);
      case 932:  RET_ARR(7,8);
      case 933:  RET_ARR(6,7,8);
      case 934:  RET_ARR(4,6);
      case 935:  RET_ARR(6);
      case 936:  RET_ARR(4,6);
      case 937:  RET_ARR(4,6);
      case 938:  RET_ARR(4,6);
      case 939:  RET_ARR(6);
      case 940:  RET_ARR(4);
      case 941:  RET_ARR(4);
      case 942:  RET_ARR(4);
      case 943:  RET_ARR(4,6);
      case 944:  RET_ARR(6,7,8);
      case 945:  RET_ARR(6,7,8,12);
      case 9915: RET_ARR(7,8,12);
      case 9916: RET_ARR(6,7,8);
      case 9917: RET_ARR(6);
      case 946:  RET_ARR(7,8,12);
      case 947:  RET_ARR(6,7,8,12);
      case 948:  RET_ARR(12);
      case 949:  RET_ARR(12);
      case 950:  RET_ARR(7,8,12);
      case 951:  RET_ARR(6,7,8);
      case 952:  RET_ARR(6,7,8);
      case 953:  RET_ARR(7,8);
      case 954:  RET_ARR(7,8);
      case 955:  RET_ARR(6);
      case 956:  RET_ARR(4,6);
      case 957:  RET_ARR(6);
      case 1:     RET_ARR(4,6,7,8,12);
      case 882:   RET_ARR(4,6,7,8,12);
      case 883:   RET_ARR(4,6,7,8,12);
      case 884:   RET_ARR(6,7,8,12);
      case 885:   RET_ARR(6,7,8,12);
      case 886:   RET_ARR(7,8,12);
      case 887:   RET_ARR(8,12);
      case 8881:  RET_ARR(12);
      case 889:   RET_ARR(12);
      case 8810:  RET_ARR(12);
      case 8811:  RET_ARR(12);
      default: return {};
    }
  }

  // ---------- I(kind) -> 허용 g (instantons 동일 규칙) ----------
  if (k==I){
    switch(param){
      case 1:     RET_ARR(4,6,7,8,12);
      case 882:   RET_ARR(4,6,7,8,12);
      case 883:   RET_ARR(4,6,7,8,12);
      case 884:   RET_ARR(6,7,8,12);
      case 885:   RET_ARR(6,7,8,12);
      case 886:   RET_ARR(7,8,12);
      case 887:   RET_ARR(8,12);
      case 8881:  RET_ARR(12);
      case 889:   RET_ARR(12);
      case 8810:  RET_ARR(12);
      case 8811:  RET_ARR(12);
      default: return {};
    }
  }
  return {};
}

// ================== Generalized Topology Sweeper (drop-in) ==================

struct NodeSpec { LKind kind; };

struct Topology {
    std::string name;                       // 파일명/로그 프리픽스
    std::vector<NodeSpec> nodes;            // 노드 종류들 (S,g,L,I)
    std::vector<std::pair<int,int>> edges;  // (u,v) 연결 목록 (무방향)
};

struct BankView { const int* data; int n; };
static inline BankView bank_of(LKind k){
    switch(k){
        case S: return { S_BANK, (int)numS };
        case g: return { G_BANK, (int)numG };
        case L: return { L_BANK, (int)numL };
        case I: return { I_BANK, (int)numI };
    }
    return {nullptr,0};
}

using Domain = std::vector<int>;

static inline void intersect_inplace(Domain& dst, const IntView& v){
    if (dst.empty()) return;
    Domain out;
    out.reserve(std::min(dst.size(), (size_t)v.size));
    for (int x : dst){
        for (size_t i=0;i<v.size;++i){
            if (x == v.data[i]) { out.push_back(x); break; }
        }
    }
    dst.swap(out);
}

static int pick_next_var(const std::vector<NodeSpec>& nodes,
                         const std::vector<int>& assign,
                         const std::vector<Domain>& g_domains)
{
    // 비-g 중 미정이 있으면 먼저 처리(인접 g 도메인을 빨리 줄이기 위함)
    for (int i=0;i<(int)nodes.size();++i)
        if (assign[i]==-1 && nodes[i].kind!=g) return i;

    // 그 다음 g 중 도메인 최소(MRV)
    int best=-1; size_t bestsz = std::numeric_limits<size_t>::max();
    for (int i=0;i<(int)nodes.size();++i){
        if (assign[i]!=-1 || nodes[i].kind!=g) continue;
        size_t sz = g_domains[i].size();
        if (sz < bestsz){ bestsz = sz; best = i; }
    }
    return best;
}

// 프로젝트에 l(param)이 있으면 L 분기를 G.add(l(param))으로 바꾸세요.
static inline NodeRef add_node(TheoryGraph& G, LKind k, int param){
    switch(k){
        case S: return G.add(s(param));
        case g: return G.add(n(param));
        case L: /*return G.add(l(param));*/ return G.add(i(param)); // 임시: L을 S로 생성
        case I: return G.add(s(param)); // instanton은 S와 동일 규칙을 사용
    }
    return G.add(s(param));
}

static bool evaluate_assignment(const Topology& topo,
                                const std::vector<int>& assign,
                                std::ostringstream& out)
{
    TheoryGraph G;
    std::vector<NodeRef> ref; ref.reserve(topo.nodes.size());
    for (int i=0;i<(int)topo.nodes.size();++i)
        ref.push_back(add_node(G, topo.nodes[i].kind, assign[i]));

    for (auto [u,v] : topo.edges)
        if (!safe_connect(G, ref[u], ref[v])) return false;

    const Eigen::MatrixXi glued = compose_glue(G);
    return evaluate_and_append(glued, [&](std::string_view sv){ out << sv; });
}

static void dfs(const Topology& topo,
                std::vector<int>& assign,
                std::vector<Domain>& g_domains,
                long long& tried, long long& found,
                std::ostringstream& out,
                const long long log_interval = 100000)
{
    int var = pick_next_var(topo.nodes, assign, g_domains);
    if (var < 0){
        ++tried;
        std::ostringstream local;
        if (evaluate_assignment(topo, assign, local)){
            ++found;
            out << local.str();
        }
        if ((tried % log_interval) == 0)
            std::cout << "[" << topo.name << "] tried=" << tried << " found=" << found << "\n";
        return;
    }

    LKind k = topo.nodes[var].kind;

    if (k == g){
        Domain cand = g_domains[var]; // MRV 적용됨
        for (int gv : cand){
            assign[var] = gv;
            dfs(topo, assign, g_domains, tried, found, out, log_interval);
            assign[var] = -1;
        }
        return;
    }

    // k ∈ {S,L,I} : 자신의 선택이 인접 g 도메인에 미치는 제약을 즉시 전파
    BankView b = bank_of(k);
    for (int idx=0; idx<b.n; ++idx){
        int param = b.data[idx];

        // 인접 g 수집
        std::vector<int> g_nei;
        g_nei.reserve(3);
        for (auto [u,v] : topo.edges){
            int other=-1;
            if (u==var && topo.nodes[v].kind==g) other=v;
            else if (v==var && topo.nodes[u].kind==g) other=u;
            if (other>=0) g_nei.push_back(other);
        }

        // 백업 & 전파
        std::vector<Domain> backup; backup.reserve(g_nei.size());
        bool dead=false;
        for (int gi : g_nei){
            backup.push_back(g_domains[gi]);
            intersect_inplace(g_domains[gi], allowed(k, param)); // g 허용치와 교집합
            if (g_domains[gi].empty()){ dead=true; break; }
        }
        if (dead){
            for (size_t t=0;t<g_nei.size();++t) g_domains[g_nei[t]].swap(backup[t]);
            continue;
        }

        assign[var] = param;
        dfs(topo, assign, g_domains, tried, found, out, log_interval);
        assign[var] = -1;

        for (size_t t=0;t<g_nei.size();++t) g_domains[g_nei[t]].swap(backup[t]);
    }
}

static void run_topology(const Topology& topo, const std::string& out_prefix="SCFT_"){
    const int N = (int)topo.nodes.size();
    std::vector<int> assign(N, -1);
    std::vector<Domain> g_domains(N);

    int counter = 0;

    // g 초기 도메인 = G_BANK 전체
    for (int i=0;i<N;++i){
        if (topo.nodes[i].kind==g){
            BankView gb = bank_of(g);
            g_domains[i].assign(gb.data, gb.data + gb.n);

	    counter++;
	    if (counter % 10000 == 0) { std::cout << counter << std::endl;}
        }
    }

    long long tried=0, found=0;
    std::ostringstream out;
    dfs(topo, assign, g_domains, tried, found, out);

    std::ofstream fout(out_prefix + topo.name + ".txt", std::ios::out);
    fout << out.str();

    std::cout << "[" << topo.name << "] total tried: " << tried
              << " | total found: " << found << "\n";
}

// ---- 토폴로지 선언 ----
static Topology TOPO_Sg {
    "Sg",
    /*nodes*/ { {S}, {g} },
    /*edges*/ { {0,1} }
};

static Topology TOPO_SgS {
    "SgS",
    /*nodes*/ { {S}, {g}, {S} },
    /*edges*/ { {0,1}, {2,1} }
};

static Topology TOPO_SSgS {
    "SSgS",
    /*nodes*/ { {S},{S},{g},{S} },
    /*edges*/ { {0,2},{1,2},{3,2} }
};

// 예시: S–S–g–L–g–L–g–S (체인/복합형)
static Topology TOPO_SSgLgLgS {
    "SSgLgLgS",
    /*nodes*/ { {S},{S},{g},{L},{g},{L},{g},{S} },
    /*edges*/ {
        {0,2}, {1,2},   // 앞쪽 두 S가 g(2)에
        {3,2}, {3,4},   // L(3)로 g(2)-g(4) 연결
        {5,4}, {5,6},   // L(5)로 g(4)-g(6) 연결
        {7,6}           // 끝 S가 g(6)에
    }
};

int main(){
    run_topology(TOPO_Sg);        // SCFT_Sg.txt
    run_topology(TOPO_SgS);       // SCFT_SgS.txt
    run_topology(TOPO_SSgS);      // SCFT_SSgS.txt
    run_topology(TOPO_SSgLgLgS);  // SCFT_SSgLgLgS.txt
    return 0;
}

