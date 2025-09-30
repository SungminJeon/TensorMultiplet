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

    const int Nparams = (int)(sizeof(params)/sizeof(params[0]));

    const int instantons[] = {
        1, 288, 388, 488, 588, 688, 788, 1888, 988, 1088, 1188,
    };
    const int Ninsts = (int)(sizeof(instantons)/sizeof(instantons[0]));

    const int ns[] = {4, 6, 7, 8, 12};
    const int Nns  = (int)(sizeof(ns)/sizeof(ns[0]));

    struct Counters { long long sg=0, sgs=0, ssgs=0, s4=0; } cnt;

    const long long total_sg   = (long long)Nns * Nparams;
    const long long total_sgs  = (long long)Nns * Nparams * (Nparams + 1) / 2;
    const long long total_ssgs = (long long)Nns * Nparams * (Nparams + 1) * (Nparams + 2) / 6;
    const long long total_s4   = total_ssgs * (long long)Ninsts;

    std::cout << "[Init] totals — Sg:" << total_sg
              << ", SgS:" << total_sgs
              << ", S{S,g}S:" << total_ssgs
              << ", S4:" << total_s4 << "\n";

    // ---- Phase 1: Sg ----
    {
        std::string out; out.reserve(1<<20);
        long long progress = 0;

        #pragma omp parallel
        {
            std::string local_buf; local_buf.reserve(1<<18);
            long long local_cnt = 0;

            #pragma omp for schedule(dynamic)
            for (int ni = 0; ni < Nns; ++ni) {
                #pragma omp critical
                std::cout << "[Sg] ns=" << ns[ni] << " start (thread " << thread_id() << ")\n";

                const int n = ns[ni];
                for (int i = 0; i < Nparams; ++i) {
                    TheoryGraph G;
                    auto S1 = G.add(s(params[i]));
                    auto N  = G.add(n_(n));
                    if (!safe_connect(G, S1, N)) {
                        #pragma omp atomic update
                        progress++;
                        if ((progress & 511) == 0) print_progress("Sg", progress, total_sg);
                        continue;
                    }

                    Eigen::MatrixXi glued = compose_glue(G);

                    #pragma omp atomic update
                    progress++;
                    if ((progress & 511) == 0) print_progress("Sg", progress, total_sg);

                    if (evaluate_and_append(glued, local_buf)) ++local_cnt;
                }
            }

            #pragma omp critical
            { cnt.sg += local_cnt; out.append(local_buf); }
        }

        flush_to_file("SCFT_Sg.txt", out);
    }

    // ---- Phase 2: SgS ----
    {
        std::string out; out.reserve(1<<21);
        long long progress = 0;

        #pragma omp parallel
        {
            std::string local_buf; local_buf.reserve(1<<19);
            long long local_cnt = 0;

            #pragma omp for collapse(2) schedule(dynamic)
            for (int ni = 0; ni < Nns; ++ni)
            for (int i  = 0;  i < Nparams; ++i) {
                if (i == 0) {
                    #pragma omp critical
                    std::cout << "[SgS] ns=" << ns[ni] << " start (thread " << thread_id() << ")\n";
                }

                const int n = ns[ni];
                for (int j = 0; j <= i; ++j) {
                    TheoryGraph G;
                    auto S1 = G.add(s(params[i]));
                    auto N  = G.add(n_(n));
                    auto S2 = G.add(s(params[j]));
                    if (!safe_connect(G, S1, N) || !safe_connect(G, S2, N)) {
                        #pragma omp atomic update
                        progress++;
                        if ((progress & 4095) == 0) print_progress("SgS", progress, total_sgs);
                        continue;
                    }

                    Eigen::MatrixXi glued = compose_glue(G);

                    #pragma omp atomic update
                    progress++;
                    if ((progress & 4095) == 0) print_progress("SgS", progress, total_sgs);

                    if (evaluate_and_append(glued, local_buf)) ++local_cnt;
                }
            }

            #pragma omp critical
            { cnt.sgs += local_cnt; out.append(local_buf); }
        }

        flush_to_file("SCFT_SgS.txt", out);
    }

    // ---- Phase 3: S{S,g}S ----
    {
        std::string out; out.reserve(1<<22);
        long long progress = 0;

        #pragma omp parallel
        {
            std::string local_buf; local_buf.reserve(1<<20);
            long long local_cnt = 0;

            #pragma omp for collapse(2) schedule(dynamic)
            for (int ni = 0; ni < Nns; ++ni)
            for (int i  = 0;  i < Nparams; ++i) {
                if (i == 0) {
                    #pragma omp critical
                    std::cout << "[S{S,g}S] ns=" << ns[ni] << " start (thread " << thread_id() << ")\n";
                }

                const int n = ns[ni];
                for (int j = 0; j <= i; ++j) {
                    for (int k = 0; k <= j; ++k) {
                        TheoryGraph G;
                        auto S1 = G.add(s(params[i]));
                        auto N  = G.add(n_(n));
                        auto S2 = G.add(s(params[j]));
                        auto S3 = G.add(s(params[k]));
                        if (!safe_connect(G, S1, N) || !safe_connect(G, S2, N) || !safe_connect(G, S3, N)) {
                            #pragma omp atomic update
                            progress++;
                            if ((progress % 50000) == 0) print_progress("S{S,g}S", progress, total_ssgs);
                            continue;
                        }

                        Eigen::MatrixXi glued = compose_glue(G);

                        #pragma omp atomic update
                        progress++;
                        if ((progress % 50000) == 0) print_progress("S{S,g}S", progress, total_ssgs);

                        if (evaluate_and_append(glued, local_buf)) ++local_cnt;
                    }
                }
            }

            #pragma omp critical
            { cnt.ssgs += local_cnt; out.append(local_buf); }
        }

        flush_to_file("SCFT_S{S,g}S.txt", out);
    }

    // ---- Phase 4: S4 (instantons) ----
    {
        std::string out; out.reserve(1<<22);
        long long progress = 0;

        #pragma omp parallel
        {
            std::string local_buf; local_buf.reserve(1<<20);
            long long local_cnt = 0;

            #pragma omp for collapse(2) schedule(dynamic)
            for (int ni = 0; ni < Nns; ++ni)
            for (int i  = 0;  i < Nparams; ++i) {
                if (i == 0) {
                    #pragma omp critical
                    std::cout << "[S4] ns=" << ns[ni] << " start (thread " << thread_id() << ")\n";
                }

                const int n = ns[ni];
                for (int j = 0; j <= i; ++j) {
                    for (int k = 0; k <= j; ++k) {
			    int aux;
			    if ( k > Ninsts-1 ) { aux = Ninsts-1;}
			    else if( k<= Ninsts-1) { aux = k;}
                        for (int l = 0; l <= aux; ++l) {
                            TheoryGraph G;
                            auto S1   = G.add(s(params[i]));
                            auto Nref = G.add(n_(n));
                            auto S2   = G.add(s(params[j]));
                            auto S3   = G.add(s(params[k]));
                            auto Inst = G.add(s(instantons[l]));

                            if (!safe_connect(G, S1, Nref) ||
                                !safe_connect(G, S2, Nref) ||
                                !safe_connect(G, S3, Nref) ||
                                !safe_connect(G, Nref, Inst)) {
                                #pragma omp atomic update
                                progress++;
                                if ((progress % 50000) == 0) print_progress("S4", progress, total_s4);
                                continue;
                            }

                            Eigen::MatrixXi glued = compose_glue(G);

                            #pragma omp atomic update
                            progress++;
                            if ((progress % 50000) == 0) print_progress("S4", progress, total_s4);

                            if (evaluate_and_append(glued, local_buf)) ++local_cnt;
                        }
                    }
                }
            }

            #pragma omp critical
            { cnt.s4 += local_cnt; out.append(local_buf); }
        }

        flush_to_file("SCFT_S4.txt", out);
    }

    // ---- final report ----
    std::cout << "total SCFT Sg: "        << cnt.sg   << "\n"
              << "total SCFT SgS: "       << cnt.sgs  << "\n"
              << "total SCFT S{S,g}S: "   << cnt.ssgs << "\n"
              << "total SCFT S{S,g,I}S: " << cnt.s4   << "\n";

    return 0;
}

