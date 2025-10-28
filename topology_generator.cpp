#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Tensor.h"
#include "Theory.h"
#include "Topology.h"
#include "TopologyDB.hpp"


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

#define RET_ARR(...) do { \
  static constexpr int A__[] = { __VA_ARGS__ }; \
  return IntView{A__, std::size(A__)}; \
} while(0)

// =====================================================
// (타입, 파라미터) -> 허용 집합
// =====================================================
[[nodiscard]] inline IntView allowed(LKind k, int param)
{
  // ---------- g(kind) -> 허용 L ----------
  if (k==LKind::g){
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
  if (k==LKind::L){
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
  if (k==LKind::S){
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

      // alkali 2-links with no -5 curves
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

      // alkali 3-links with one -5 curve
      case 99910: RET_ARR(4,6);
      //case 99901: RET_ARR();
      case 99920: RET_ARR(6,7,8);
      //case 99902: RET_ARR(6,7,8);
      case 99930: RET_ARR(6,7,8,12);
      //case 99903: RET_ARR(6,7,8,12);
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

      // alkali 1-links with one -5 curve
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

      // alkali 2-links with two -5 curves
      case 9915: RET_ARR(7,8,12);
      case 9916: RET_ARR(6,7,8);
      case 9917: RET_ARR(6);

      // alkali 1-links with two -5 curves
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

      // instantons (S)
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
  if (k==LKind::I){
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






static int generate_seq_one(const Topology& base, const std::string& name_prefix, TopologyDB& db)
{
    if (base.block.empty()) return 0;

    const auto& last = base.block.back();
    const auto  k    = last.kind;
    const int   p    = last.param;

    const IntView opts = allowed(k, p);
    if (opts.empty()) return 0;

    int saved = 0;
    for (std::size_t i=0;i<opts.size;i++){
        Topology t = base;

        if (k == LKind::g) {
            // g 다음엔 L을 붙임
            t.addBlockRight(LKind::L, opts.data[i]);
        } else if (k == LKind::L) {
            // L 다음엔 g를 붙임
            t.addBlockRight(LKind::g, opts.data[i]);
        } else {
            continue; // S/I는 여기서 확장 안 함 (원하면 분기 추가)
        }

        t.name = name_prefix + "_add(" + std::to_string((int)k) + "," + std::to_string(p) + ")->" + std::to_string(opts.data[i]);
        if (db.append(t)) ++saved;
    }
    return saved;
}

int main(){
    TopologyDB db("autogen/g.txt");

    // 1) 모든 토폴로지 로드
    auto all = db.loadAll();
    std::cout << "Loaded " << all.size() << " topologies\n";

    // 2) 각 토폴로지에 대해 한 칸 확장 시도 → DB에 추가
    int total_saved = 0;
    for (auto& rec : all){
        total_saved += generate_seq_one(rec.topo, rec.topo.name, db);
    }
    std::cout << "Saved " << total_saved << " new topologies\n";
    return 0;
}
