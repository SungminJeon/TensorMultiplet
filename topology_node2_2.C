// topology_node2_2_fixed.C
// Fixes: Kind name clash, bad pragmas, symbol confusion.
// Build: g++ -std=c++17 -O3 -fopenmp -I/usr/include/eigen3 -DNDEBUG topology_node2_2_fixed.C -o runner

#include "Theory.h"
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#ifdef _OPENMP
#include <omp.h>
#endif

enum class LKind : unsigned char { G=0, L=1, S=2, I=3 };

struct ParamBank { const int* vals; int N; };
struct BaseNode  { LKind kind; };
struct BaseEdge  { int u, v; };

struct AttachRule {
	int   host_idx;
	LKind kind;
	int   max_count;
	bool  multiset;
	bool  exact;
};

struct UnorderedPair { int a, b; };

struct TopoSpec {
	ParamBank gbank, lbank, sbank, ibank;
	const BaseNode* nodes; int n_nodes;
	const BaseEdge* edges; int n_edges;
	const AttachRule* attaches; int n_attaches;
	const UnorderedPair* unordered_pairs; int n_unordered;
	const char* out_path;
};

static inline bool connect_safe(TheoryGraph& graph, NodeRef a, NodeRef b){
	try { graph.connect(a, b); return true; }
	catch (const std::invalid_argument&) { return false; }
}

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
	buf.push_back('\n');
}

static inline NodeRef addNode(TheoryGraph& graph, LKind k, int v){
	switch(k){
		case LKind::G: return graph.add(n_(v));
		case LKind::L: return graph.add(i(v));
		case LKind::S: return graph.add(s(v));
		case LKind::I: return graph.add(s(v));
	}
	return NodeRef{-1};
}

////////////////SCFT filter////////////////////////

static inline bool pass_filter_pre_and_post_zero_zero(const Eigen::MatrixXi& pre){   
	Tensor T;
	T.SetIF(pre);
	T.Setb0Q();
	if (T.TimeDirection()!=0 || T.NullDirection()!=0) return false;
	T.ForcedBlowdown();
	return (T.TimeDirection()==0 && T.NullDirection()==0);
}

///////////////topology runner ////////////////////

void run_topology(const TopoSpec& spec){
	std::vector<int> g_pos, l_pos, i_pos;
	g_pos.reserve(spec.n_nodes); l_pos.reserve(spec.n_nodes); i_pos.reserve(spec.n_nodes);
	for (int ni=0; ni<spec.n_nodes; ++ni){
		if (spec.nodes[ni].kind==LKind::G) g_pos.push_back(ni);
		else if (spec.nodes[ni].kind==LKind::L) l_pos.push_back(ni);
		else if (spec.nodes[ni].kind==LKind::I) i_pos.push_back(ni);
	}
	const int NG = (int)g_pos.size();
	const int NL = (int)l_pos.size();
	const int NI = (int)i_pos.size();

	std::string out; out.reserve(1<<24);
	long long accepted = 0;

#pragma omp parallel
	{
		std::string local; local.reserve(1<<22);
		long long loc_acc = 0;

		const long long GG = (long long)std::pow((double)spec.gbank.N, NG);
#pragma omp for schedule(dynamic)
		for (long long g_flat=0; g_flat<GG; ++g_flat){
			std::vector<int> gsel(NG,0);
			{
				long long t = g_flat;
				for (int k=0;k<NG;k++){ gsel[k] = (int)(t % spec.gbank.N); t /= spec.gbank.N; }
			}

			const long long LL = (long long)std::pow((double)spec.lbank.N, NL);
			for (long long l_flat=0; l_flat<LL; ++l_flat){
				std::vector<int> lsel(NL,0);
				{
					long long t = l_flat;
					for (int k=0;k<NL;k++){ lsel[k] = (int)(t % spec.lbank.N); t /= spec.lbank.N; }
				}

				const long long II = (long long)std::pow((double)spec.ibank.N, NI);
				for (long long i_flat=0; i_flat<II; ++i_flat){
					std::vector<int> isel(NI,0);
					{
						long long t = i_flat;
						for (int k=0;k<NI;k++){ isel[k] = (int)(t % spec.ibank.N); t /= spec.ibank.N; }
					}

					bool sym_ok = true;
					for (int u=0; u<spec.n_unordered; ++u){
						const int a = spec.unordered_pairs[u].a;
						const int b = spec.unordered_pairs[u].b;
						int va=-1, vb=-1;
						for (int gi=0; gi<NG; ++gi){
							if (g_pos[gi]==a) va = spec.gbank.vals[gsel[gi]];
							if (g_pos[gi]==b) vb = spec.gbank.vals[gsel[gi]];
						}
						if (va!=-1 && vb!=-1 && !(vb<=va)) { sym_ok=false; break; }
					}
					if (!sym_ok){
						continue;
					}

					std::vector<std::vector<std::vector<int>>> choices(spec.n_attaches);
					for (int r=0; r<spec.n_attaches; ++r){
						const auto& R = spec.attaches[r];
						std::vector<std::vector<int>> one;
						if (R.max_count==0){
							one.push_back({});
						} else if (R.multiset){
							if (R.exact){
								std::vector<std::vector<int>> tmp;
								gen_multiset_combos(spec.sbank.vals, spec.sbank.N, R.max_count, tmp);
								one.insert(one.end(), tmp.begin(), tmp.end());
							} else {
								for (int k=0;k<=R.max_count;k++){
									std::vector<std::vector<int>> tmp;
									gen_multiset_combos(spec.sbank.vals, spec.sbank.N, k, tmp);
									one.insert(one.end(), tmp.begin(), tmp.end());
								}
							}
						} else {
							one.push_back({});
							for (int k=1;k<=R.max_count;k++)
								for (int si=0; si<spec.sbank.N; ++si) one.push_back({spec.sbank.vals[si]});
						}
						choices[r] = std::move(one);
					}

					const auto& W0 = (spec.n_attaches>=1?choices[0]:std::vector<std::vector<int>>{{}});
					const auto& W1 = (spec.n_attaches>=2?choices[1]:std::vector<std::vector<int>>{{}});
					const auto& W2 = (spec.n_attaches>=3?choices[2]:std::vector<std::vector<int>>{{}});

					for (const auto& A0: W0)
						for (const auto& A1: W1)
							for (const auto& A2: W2)
							{
								TheoryGraph graph;
								std::vector<NodeRef> ref(spec.n_nodes);

								int gi_ptr=0, li_ptr=0, ii_ptr=0;
								for (int ni=0; ni<spec.n_nodes; ++ni){
									int v=0;
									switch (spec.nodes[ni].kind){
										case LKind::G: v = spec.gbank.vals[gsel[gi_ptr++]]; break;
										case LKind::L: v = spec.lbank.vals[lsel[li_ptr++]]; break;
										case LKind::I: v = spec.ibank.vals[isel[ii_ptr++]]; break;
										case LKind::S: v = 0; break;
									}
									ref[ni] = addNode(graph, spec.nodes[ni].kind, v);
								}

								bool ok = true;
								for (int e=0; e<spec.n_edges; ++e){
									ok &= connect_safe(graph, ref[spec.edges[e].u], ref[spec.edges[e].v]);
								}
								if (!ok){
									continue;
								}

								for (int r=0; r<spec.n_attaches; ++r){
									const auto& R = spec.attaches[r];
									const auto& pack = (r==0?A0:(r==1?A1:A2));
									auto sorted = pack;
									if (R.multiset) std::sort(sorted.begin(), sorted.end());
									for (int p: sorted){
										NodeRef a = addNode(graph, R.kind, p);
										if (!connect_safe(graph, a, ref[R.host_idx])) { ok=false; break; }
									}
									if (!ok) break;
								}
								if (!ok){
									continue;
								}

								Eigen::MatrixXi preIF = graph.ComposeIF_UnitGluing();
								if (pass_filter_pre_and_post_zero_zero(preIF)){
									append_matrix(preIF, local);
									++loc_acc;
								}
							} // attachments
				} // I
			} // L
		} // G

#pragma omp critical
		{ out.append(local); accepted += loc_acc; }
	} // parallel

	if (FILE* fp = std::fopen(spec.out_path, "w")){
		std::fwrite(out.data(), 1, out.size(), fp);
		std::fclose(fp);
	}
	std::printf("[Report] %s accepted=%lld\n", spec.out_path, accepted);
}

// ---- Example specs (edit banks to your real params) ----
static constexpr int G_BANK[] = {4,6,7,8,12};
static constexpr int L_BANK[] = {11,22,33,44,55,331,32,23,42,24,43,34,53,35,54,45};
static constexpr int S_BANK[] = {1, 882, 883, 884, 885, 886, 887, 8881, 889, 8810, 8811,
        22, 33, 44, 55, 331, 32, 23, 42, 24, 43, 34, 53, 35, 54, 45,
        991, 9920, 9902, 993,
        91, 92, 93, 94, 95, 96, 97, 98, 99, 910, 911, 912, 913, 914, 915, 916, 917,
        99910, 99901, 99920, 99902, 99930, 99903,
        994, 995, 996, 997, 998, 999, 9910, 9911, 9912, 9913, 9914,
        918, 919, 920, 921, 922, 923, 924, 925, 926, 927,
        928, 929, 930, 931, 932, 933, 934, 935, 936, 937,
        938, 939, 940, 941, 942, 943, 944, 945,
        9915, 9916, 9917,
        946, 947, 948, 949, 950, 951, 952, 953, 954, 955, 956, 957};
static constexpr int I_BANK[] = {1, 882, 883,884,885,886,887,8881,889,8810,8811};

// BaseNode = elements of basic tree, BaseEdge = intersection structure of the base ////////////

static constexpr BaseNode NODES_GLG[] = { {LKind::G},{LKind::L},{LKind::G} };
static constexpr BaseEdge EDGES_GLG[] = { {0,1},{1,2} };
static constexpr UnorderedPair SYM_LR_G[] = { {0,2} };  // can be choosed for topology



static constexpr AttachRule ATT_SSgLgS[] = { {0, LKind::S, 2, true, true} {0,Lkind::S,2,true,true }};
static const TopoSpec SPEC_SSgLgS {
	{G_BANK, int(sizeof(G_BANK)/sizeof(G_BANK[0]))},
		{L_BANK, int(sizeof(L_BANK)/sizeof(L_BANK[0]))},
		{S_BANK, int(sizeof(S_BANK)/sizeof(S_BANK[0]))},
		{I_BANK, int(sizeof(I_BANK)/sizeof(I_BANK[0]))},
		NODES_GLG, 3, EDGES_GLG, 2,
		ATT_SSgLgS, 1,
		nullptr, 0,
		"SCFT_SSgLgS.txt"
};

static constexpr AttachRule ATT_SSgLIgS[] = { {0,LKind::S,2,true,true}, {2,LKind::S,1,true,true}, {2,LKind::I,1,true,true} };
static const TopoSpec SPEC_SSgLIgS {
	{G_BANK, int(sizeof(G_BANK)/sizeof(G_BANK[0]))},
		{L_BANK, int(sizeof(L_BANK)/sizeof(L_BANK[0]))},
		{S_BANK, int(sizeof(S_BANK)/sizeof(S_BANK[0]))},
		{I_BANK, int(sizeof(I_BANK)/sizeof(I_BANK[0]))},
		NODES_GLG, 3, EDGES_GLG, 2,
		ATT_SSgLIgS, 2,
		SYM_LR_G, 1,
		"SCFT_SgLIgS.txt"
};

int main(){
	run_topology(SPEC_SSgLgS);
	run_topology(SPEC_SSgLIgS);
	return 0;
}

