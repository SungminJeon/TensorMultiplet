// topology_opt_fix.C — robust build, progress, phase4, pre-blowdown save

#ifndef USE_UNIT_GLUING
#define USE_UNIT_GLUING 1
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#ifdef _OPENMP
  #include <omp.h>
#endif

#include <Eigen/Dense>
#include "Tensor.h"
#include "Theory.h"

// ---------- helpers ----------

static inline int thread_id() noexcept {
#ifdef _OPENMP
    return omp_get_thread_num();
#else
    return 0;
#endif
}

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

// save PRE-blowdown IF; use blowdown ONLY for validation
static inline bool evaluate_and_append(const Eigen::MatrixXi &glued,
                                       std::string &out_buf) {
    Tensor g;
    g.SetIF(glued);
    g.Setb0Q();

    // quick cut (before blowdown)
    if (g.TimeDirection() != 0 || g.NullDirection() != 0) return false;

    // snapshot pre-blowdown matrix
    const Eigen::MatrixXi IF0 = g.GetIntersectionForm();

    // validate with blowdown (not saved)
    g.ForcedBlowdown();
    if (g.TimeDirection() != 0 || g.NullDirection() != 0) return false;

    // serialize IF0
    const int R = IF0.rows(), C = IF0.cols();
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            if (c) out_buf.push_back(' ');
            out_buf.append(std::to_string(IF0(r, c)));
        }
        out_buf.push_back('\n');
    }
    out_buf.push_back('\n');
    return true;
}

static inline void flush_to_file(const char *path, const std::string &buf) {
    if (buf.empty()) return;
    std::ofstream ofs(path, std::ios::app);
    if (!ofs) { std::cerr << "[!] cannot open: " << path << "\n"; return; }
    ofs << buf;
}

static inline void print_progress(const char* phase, long long cur, long long tot) {
    if (tot == 0) return;
    const double pct = 100.0 * double(cur) / double(tot);
    std::cout << "[" << phase << "] " << cur << "/" << tot << " (" << pct << "%)\n";
}

int main() {
    // line-buffered stdout
    std::cout.setf(std::ios::unitbuf);

    // ---- parameter tables ----
    const int params[] = {
	    1, 882, 883, 884, 885, 886, 887, 8881, 889, 8810, 8811,
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
    const int params2[] = {
	    1, 288, 388, 488, 588, 688, 788, 1888, 988, 1088, 1188,
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

    const int interiors[] = { 11,22,33,44,55,331,32,23,42,24,43,34,53,35,54,45 };

    const int Nparams = (int)(sizeof(params)/sizeof(params[0]));

    const int instantons[] = {
        1, 288, 388, 488, 588, 688, 788, 1888, 988, 1088, 1188,
    };
    const int Ninsts = (int)(sizeof(instantons)/sizeof(instantons[0]));

    const int iparams = (int)(sizeof(interiors)/sizeof(interiors[0]));

    const int ns[] = {4, 6, 7, 8, 12};
    const int Nns  = (int)(sizeof(ns)/sizeof(ns[0]));






struct Counters {
        long long node2=0, node2_sglg=0, node2_sglgs=0;
    } cnt;

    const long long total_node2     = (long long)Nns * Nns * iparams;
    const long long total_gLg       = (long long)Nns * Nns * iparams;
    const long long total_SgLg      = (long long)Nns * Nns * Nparams * iparams;
    const long long total_SgLgS     = (long long)Nns * Nns * (long long)Nparams * (Nparams - 1) / 2 * iparams;
    const long long total_SgSg      = (long long)Nns* Nns* Nparams * (Nparams -1)/2 * iparams;

    std::cout << "[Init] totals — "
              << "node2_gLg:" << total_node2
              << ", gLg:" << total_gLg
              << ", SgLg:" << total_SgLg
              << ", SgLgS:" << total_SgLgS
              << ", S{S,g}gLg:" << total_SgSg << "\n";

    // ---- Phase 0: node2_gLg ----
    {
        std::string out; out.reserve(1<<21);
        long long progress = 0;
        #pragma omp parallel
        {
            std::string local_buf; local_buf.reserve(1<<19);
            long long local_cnt = 0;
            #pragma omp for collapse(3) schedule(dynamic)
            for (int nia=0; nia<Nns; ++nia)
            for (int nib=0; nib<Nns; ++nib)
            for (int t=0; t<iparams; ++t) {
                const int na = ns[nia], nb = ns[nib], gi = interiors[t];
                TheoryGraph G;
                auto NA = G.add(n_(na));
                auto GB = G.add(i(gi));
                auto NB = G.add(n_(nb));
                if (!safe_connect(G,NA,GB) || !safe_connect(G,GB,NB)) {
                    #pragma omp atomic update
                    progress++;
                    continue;
                }
                Eigen::MatrixXi glued = compose_glue(G);
                #pragma omp atomic update
                progress++;
                if (evaluate_and_append(glued, local_buf)) ++local_cnt;
            }
            #pragma omp critical
            { cnt.node2 += local_cnt; out.append(local_buf); }
        }
        flush_to_file("SCFT_node2_gLg.txt", out);
    }

    // ---- Phase 0.5: node2_SgLg (왼쪽에만 사이드 링크) ----
    {
        std::string out; out.reserve(1<<21);
        long long progress = 0;
        #pragma omp parallel
        {
            std::string local_buf; local_buf.reserve(1<<19);
            long long local_cnt = 0;
            #pragma omp for collapse(4) schedule(dynamic)
            for (int nia=0; nia<Nns; ++nia)
            for (int nib=0; nib<Nns; ++nib)
            for (int t=0; t<iparams; ++t)
            for (int p=0; p<Nparams; ++p) {
                const int na = ns[nia], nb = ns[nib], gi = interiors[t], sp = params[p];
                TheoryGraph G;
                auto NA = G.add(n_(na));
                auto GB = G.add(i(gi));
                auto NB = G.add(n_(nb));
                auto SA = G.add(s(sp));
                if (!safe_connect(G,NA,GB) || !safe_connect(G,GB,NB) || !safe_connect(G,SA,NA)) {
                    #pragma omp atomic update
                    progress++;
                    continue;
                }
                Eigen::MatrixXi glued = compose_glue(G);
                #pragma omp atomic update
                progress++;
                if (evaluate_and_append(glued, local_buf)) ++local_cnt;
            }
            #pragma omp critical
            { cnt.node2_sglg += local_cnt; out.append(local_buf); }
        }
        flush_to_file("SCFT_node2_SgLg.txt", out);
    }

    // ---- Phase 0.6: node2_SgLgS (양쪽에 사이드 링크 두 개) ----
    {
        std::string out; out.reserve(1<<21);
        long long progress = 0;
        #pragma omp parallel
        {
            std::string local_buf; local_buf.reserve(1<<19);
            long long local_cnt = 0;
            #pragma omp for collapse(4) schedule(dynamic)
            for (int nia=0; nia<Nns; ++nia)
            for (int nib=0; nib<Nns; ++nib)
            for (int t=0; t<iparams; ++t)
            for (int p=0; p<Nparams; ++p)
            for (int q=p+1; q<Nparams; ++q) {
                const int na = ns[nia], nb = ns[nib], gi = interiors[t];
                const int spL = params[p], spR = params[q];
                TheoryGraph G;
                auto NA = G.add(n_(na));
                auto GB = G.add(i(gi));
                auto NB = G.add(n_(nb));
                auto SA = G.add(s(spL));
                auto SB = G.add(s(spR));
                if (!safe_connect(G,NA,GB) || !safe_connect(G,GB,NB) ||
                    !safe_connect(G,SA,NA) || !safe_connect(G,SB,NB)) {
                    #pragma omp atomic update
                    progress++;
                    continue;
                }
                Eigen::MatrixXi glued = compose_glue(G);
                #pragma omp atomic update
                progress++;
                if (evaluate_and_append(glued, local_buf)) ++local_cnt;
            }
            #pragma omp critical
            { cnt.node2_sglgs += local_cnt; out.append(local_buf); }
        }
        flush_to_file("SCFT_node2_SgLgS.txt", out);
    }

    // ---- 이후 Phase1~PhaseN: 기존 Sg, SgS 등 기존 코드 그대로 유지 ----
    // (여기서는 생략했지만, 원래 topology_node2.C에 있는 Phase1~Phase4 부분 붙이면 됨)

    std::cout << "total SCFT node2_gLg:  " << cnt.node2      << "\n"
              << "total SCFT node2_SgLg: " << cnt.node2_sglg << "\n"
              << "total SCFT node2_SgLgS:" << cnt.node2_sglgs<< "\n";
             
}

