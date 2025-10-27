// ----- mapping_allowed.hpp -----
#pragma once
#include <cstddef>
#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <Eigen/Dense>
#include "Tensor.h"
#include "Theory.h"
#include <string_view>
#include <functional>
#include <fstream>



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
    if (g.TimeDirection() != 0 || g.NullDirection() != 0)
        return false;

    const Eigen::MatrixXi IF0 = g.GetIntersectionForm();

    // validate with blowdown (not saved)
    //g.ForcedBlowdown();
    //if (g.TimeDirection() != 0 || g.NullDirection() != 0)
    //    return false;

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

// =====================================================
// 유틸: 개수/출력
// =====================================================
inline std::size_t Nparams(LKind k, int param){
  return allowed(k,param).size;
}

inline void print_params(LKind k, int param){
  auto v = allowed(k,param);
  if (v.empty()){
    std::cout << "[empty] type=" << k << ", param=" << param << "\n";
    return;
  }
  for (std::size_t i=0;i<v.size;++i){
    std::cout << v.data[i] << (i+1<v.size? ", " : "\n");
  }
}


void run_Sg_sweep() {

		std::cout << "running " << std::endl;
		long long Sg_found = 0;
		long long Sg_total_sweep = 0;

		std::string out;
		out.reserve(1 << 20);

		for (int s1 = 0; s1 < numS; ++s1) 
		{
			const int sval = S_BANK[s1];

			// S -> g rule
			auto gv = allowed(S, sval);   // IntView {data, size}
		if (gv.empty()) continue;

		for (std::size_t j = 0; j < gv.size; ++j) 
		{
			const int gval = gv.data[j];
			++Sg_total_sweep;

			if ((Sg_total_sweep % 1000) == 0) {
				std::cout << "[Sg] sweep count: " << Sg_total_sweep << '\n';
			}

			TheoryGraph G;
			auto s1 = G.add(s(sval));
			auto g1 = G.add(n(gval));

			std::cout << " s(val) " << sval << std::endl;
			std::cout << " g(val) " << gval << std::endl;
			G.connect(s1,g1);


			const Eigen::MatrixXi glued = compose_glue(G);

			// 행렬 직렬화 → 즉시 out에 append
			const bool ok = evaluate_and_append(glued, [&](std::string_view sv){
					out.append(sv.data(), sv.size());
					});
			if (ok) ++Sg_found;
		}
		}

		// 파일로 저장
		{
			std::ofstream fout("SCFT_Sg.txt", std::ios::out);
			fout << out;
		}

		std::cout << "[Sg] total sweep: " << Sg_total_sweep
			<< " | total Sg found: " << Sg_found << '\n';
	
}
// SSgS
void run_SSgS_sweep() {

	std::cout << "running " << std::endl;
	long long SSgS_found = 0;  // adjust variable for your topology : topology_found
	long long SSgS_total_sweep = 0; // adjust variable for your topology : topology_total_sweep

	std::string out;
	out.reserve(1 << 20);

	for (int side1 = 0; side1 < numS; ++side1) //notation : side1, side2,.. 
	{
		const int sval = S_BANK[side1]; //notation sval.

		// S -> g rule
		auto gv = allowed(S, sval);   // IntView {data, size}
	if (gv.empty()) continue;

	for (std::size_t j = 0; j < gv.size; ++j) 
	{
		for ( int side2 = 0; side2<=side1; ++side2)
		{
			for ( int side3 = 0; side3 <=side2; ++side3) 
			{
				const int gval = gv.data[j];
				const int sval2 = S_BANK[side2];
				const int sval3 = S_BANK[side3];
				++SSgS_total_sweep; // adjust : topology_total_sweep

				// adjust : topology_total sweep
				if ((SSgS_total_sweep % 1000) == 0) {
					std::cout << "[SSgS] sweep count: " << SSgS_total_sweep << '\n';
				}

				// type connection structure
				TheoryGraph G;
				auto s1 = G.add(s(sval));
				auto g1 = G.add(n(gval));
				auto s2 = G.add(s(sval2));
				auto s3 = G.add(s(sval3));

				//	std::cout << " s(val) " << sval << std::endl;
				//	std::cout << " g(val) " << gval << std::endl;


				if( !safe_connect(G,s1,g1) || !safe_connect(G,s2,g1) || !safe_connect(G,s3,g1)) {continue;}


				const Eigen::MatrixXi glued = compose_glue(G);

				// 행렬 직렬화 → 즉시 out에 append
				const bool ok = evaluate_and_append(glued, [&](std::string_view sv){
						out.append(sv.data(), sv.size());
						});
				if (ok) ++SSgS_found; // adjust :: topology_found
			}
		}
	}
	}

	// 파일로 저장
	{
		std::ofstream fout("SCFT_SSgS.txt", std::ios::out); //adjust : SCFT/LST_topology.txt
		fout << out;
	}

	std::cout << "[SSgS] total sweep: " << SSgS_total_sweep // adjust : topology
		<< " | total SSgS found: " << SSgS_found << '\n'; 

}

void run_SgS_sweep() {

		std::cout << "running " << std::endl;
		long long SgS_found = 0;
		long long SgS_total_sweep = 0;

		std::string out;
		out.reserve(1 << 20);

		for (int side1 = 0; side1 < numS; ++side1) 
		{
			const int sval = S_BANK[side1];

			// S -> g rule
			auto gv = allowed(S, sval);   // IntView {data, size}
		if (gv.empty()) continue;

		for (std::size_t j = 0; j < gv.size; ++j) 
		{
			for ( int side2 = 0; side2<=side1; ++side2)
			{
			const int gval = gv.data[j];
			const int sval2 = S_BANK[side2];
			++SgS_total_sweep;

			if ((SgS_total_sweep % 1000) == 0) {
				std::cout << "[Sg] sweep count: " << SgS_total_sweep << '\n';
			}

			TheoryGraph G;
			auto s1 = G.add(s(sval));
			auto g1 = G.add(n(gval));
			auto s2 = G.add(s(sval2));

			std::cout << " s(val) " << sval << std::endl;
			std::cout << " g(val) " << gval << std::endl;
			

			if( !safe_connect(G,s1,g1) || !safe_connect(G,s2,g1)) {continue;}


			const Eigen::MatrixXi glued = compose_glue(G);

			// 행렬 직렬화 → 즉시 out에 append
			const bool ok = evaluate_and_append(glued, [&](std::string_view sv){
					out.append(sv.data(), sv.size());
					});
			if (ok) ++SgS_found;
		}
		}
		}

		// 파일로 저장
		{
			std::ofstream fout("SCFT_SgS.txt", std::ios::out);
			fout << out;
		}

		std::cout << "[SgS] total sweep: " << SgS_total_sweep
			<< " | total SgS found: " << SgS_found << '\n';
	
}



void run_gLgLgLgLg_sweep() {

	std::cout << "running " << std::endl;
	long long gLgLgLgLg_found = 0;
	long long gLgLgLgLg_sweep = 0;

	std::string out;
	out.reserve(1 << 20);

	for (int node1 = 0; node1 < numG; ++node1) 
	{
		const int g1val = G_BANK[node1];

		// S -> g rule
		auto gv = allowed(g, g1val);   // IntView {data, size}
	if (gv.empty()) continue;

	for (std::size_t j = 0; j < gv.size; ++j) 
	{

		const int l1val = gv.data[j];

		auto lv = allowed(L,l1val);

		if (lv.empty()) continue;

		for ( int node2 = 0; node2 < lv.size; ++node2)
		{
			const int g2val = lv.data[node2];

			auto gv2 = allowed(g, g2val);
			if(gv2.empty()) continue;

			for (int l2 =0; l2 < gv2.size; ++l2)
			{
				const int l2val = gv2.data[l2];

				auto lv2 = allowed(L, l2val);
				if(lv2.empty())	continue;

				for (int node3 = 0; node3 < lv2.size; node3++)
				{
					const int g3val = lv2.data[node3];

					auto gv3 = allowed(g, g3val);
					if(gv3.empty()) continue;

					for (int l3 = 0; l3 < gv3.size; l3++)
					{
						const int l3val = gv3.data[l3];

						auto lv3 = allowed(L, l3val);
						if(lv3.empty()) continue;
						for (int node4=0; node4< lv3.size; node4++)
						{
							const int g4val = lv3.data[node4];

							auto gv4 = allowed(g, g4val);
							if (gv4.empty()) continue;
							for (int l4 = 0; l4 < gv4.size; l4++)
							{
								const int l4val = gv4.data[l4];

								auto lv4 = allowed(L, l4val);
								if(lv4.empty()) continue;

								for (int g5 = 0; g5 < lv4.size; g5++)
								{
									const int g5val = lv4.data[g5];

									TheoryGraph G;

									auto G1 = G.add(n(g1val));
									auto L1 = G.add(i(l1val));
									auto G2 = G.add(n(g2val));
									auto L2 = G.add(i(l2val));
									auto G3 = G.add(n(g3val));
									auto L3 = G.add(i(l3val));
									auto G4 = G.add(n(g4val));
									auto L4 = G.add(i(l4val));
									auto G5 = G.add(n(g5val));


									if (!safe_connect(G,G1,L1) || !safe_connect(G,L1,G2) || !safe_connect(G,G2,L2) || !safe_connect(G,L2,G3) || !safe_connect(G,G3,L3) || !safe_connect(G,L3,G4) || !safe_connect(G,G4,L4) || !safe_connect(G,L4,G5)) {continue;}


									gLgLgLgLg_sweep++;
									if (gLgLgLgLg_sweep % 1000 == 0) {std::cout << "processing: " << gLgLgLgLg_sweep << std::endl;}







									const Eigen::MatrixXi glued = compose_glue(G);

									// 행렬 직렬화 → 즉시 out에 append
									const bool ok = evaluate_and_append(glued, [&](std::string_view sv){
											out.append(sv.data(), sv.size());
											});
									if (ok) ++gLgLgLgLg_found;
								}
							}
						}
					}
				}
			}
		}
	}
	}
	// 파일로 저장
	{
		std::ofstream fout("SCFT_gLgLgLgLg.txt", std::ios::out);
		fout << out;
	}

	std::cout << "[g5] total sweep: " << gLgLgLgLg_sweep
		<< " | total g5 found: " << gLgLgLgLg_found << '\n';










}

int main() {



	run_Sg_sweep();
	run_SgS_sweep();

	//run_SSgS_sweep();
	run_gLgLgLgLg_sweep();
	std::cout << "dfjkajfkld " << std::endl;

}
