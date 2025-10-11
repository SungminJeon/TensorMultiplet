// topology_node2.C — g-L-g families with optional side-links (S)
//   Phase 1: gLg
//   Phase 2: SgLg
//   Phase 3: SgLgS
//   Phase 4: SSgLg
//
// Build tips:
//   g++ -std=c++17 -O3 -march=native -flto -fopenmp -DNDEBUG -DEIGEN_NO_DEBUG \
//       -I/usr/include/eigen3 -I. topology_node2.C -o topology_node2
//
// Runtime tips (Linux):
//   export OMP_NUM_THREADS=$(nproc)
//   export OMP_PROC_BIND=close
//   export OMP_PLACES=cores
//   export OMP_DYNAMIC=false

#ifndef USE_UNIT_GLUING
#define USE_UNIT_GLUING 1
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

static inline bool safe_connect(TheoryGraph &G, NodeRef a, NodeRef b) noexcept {
    try { G.connect(a, b); return true; }
    catch (const std::invalid_argument&) { return false; }
}

static inline Eigen::MatrixXi compose_glue(const TheoryGraph& G) {
#if USE_UNIT_GLUING
    return G.ComposeIF_UnitGluing();
#else
    return G.ComposeIF_Gluing();
#endif
}

// Save PRE-blowdown IF if it passes (time=null=0) both before and after blowdown.
static inline bool evaluate_and_append(const Eigen::MatrixXi &glued,
                                       std::string &out_buf) {
    Tensor g;
    g.SetIF(glued);
    g.Setb0Q();

    if (g.TimeDirection() != 0 || g.NullDirection() != 0) return false;

    const Eigen::MatrixXi IF0 = g.GetIntersectionForm();

    g.ForcedBlowdown();
    if (g.TimeDirection() != 0 || g.NullDirection() != 0) return false;

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
    std::cout.setf(std::ios::unitbuf);

    // ---- parameter tables ----
    // Side-link S parameter set (예시: topology_opt와 동일 세트)
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
    const int Nparams = (int)(sizeof(params)/sizeof(params[0]));

    // Interior-link L parameter set (예시)
    const int interiors[] = {
        11, 22, 33, 44, 55, 331, 32, 23, 42, 24, 43, 34, 53, 35, 54, 45
    };
    const int Nipar = (int)(sizeof(interiors)/sizeof(interiors[0]));

    // Node g choices (center nodes)
    const int ns[] = {4, 6, 8, 12};
    const int Nns  = (int)(sizeof(ns)/sizeof(ns[0]));

    // ----- totals (combinatorics matched with loop bounds) -----
    // choose unordered node pair (n1<=n2)
    const long long Cnn = (long long)Nns * (Nns + 1) / 2;
    const long long P   = (long long)Nparams;
    const long long P2  = P * (P + 1) / 2; // two S with repetition (j>=k)

    const long long total_gLg    = Cnn * (long long)Nipar;
    const long long total_SgLg   = Cnn * (long long)Nipar * P;
    const long long total_SgLgS  = Cnn * (long long)Nipar * P2;
    const long long total_SSgLg  = Cnn * (long long)Nipar * P2;

    std::cout << "[Init] totals — gLg:" << total_gLg
              << ", SgLg:" << total_SgLg
              << ", SgLgS:" << total_SgLgS
              << ", SSgLg:" << total_SSgLg << "\n";

    struct Counters { long long gLg=0, SgLg=0, SgLgS=0, SSgLg=0; } cnt;

    // ======================
    // Phase 1: gLg
    // ======================
    {
        std::string out; out.reserve(1<<20);
        long long progress = 0;

        #pragma omp parallel
        {
            std::string local_buf; local_buf.reserve(1<<18);
            long long local_cnt = 0;

            #pragma omp for collapse(2) schedule(dynamic)
            for (int inter = 0; inter < Nipar; ++inter)
            for (int il = 0; il < Nns; ++il) {
                if (il == 0) {
                    #pragma omp critical
                    std::cout << "[gLg] L=" << interiors[inter] << " start (thread " << thread_id() << ")\n";
                }
                for (int j = 0; j <= il; ++j) { // n2 <= n1 to avoid duplicates
                    TheoryGraph G;
                    auto N1 = G.add(n_(ns[il]));
                    auto I  = G.add(i(interiors[inter]));
                    auto N2 = G.add(n_(ns[j]));

                    if (!safe_connect(G, N1, I) || !safe_connect(G, I, N2)) {
                        #pragma omp atomic update
                        progress++;
                        if ((progress & 8191) == 0) print_progress("gLg", progress, total_gLg);
                        continue;
                    }

                    Eigen::MatrixXi glued = compose_glue(G);

                    #pragma omp atomic update
                    progress++;
                    if ((progress & 8191) == 0) print_progress("gLg", progress, total_gLg);

                    if (evaluate_and_append(glued, local_buf)) ++local_cnt;
                }
            }

            #pragma omp critical
            { cnt.gLg += local_cnt; out.append(local_buf); }
        }

        flush_to_file("SCFT_gLg.txt", out);
    }

    // ======================
    // Phase 2: SgLg  (S on left g)
    // ======================
    {
        std::string out; out.reserve(1<<21);
        long long progress = 0;

        #pragma omp parallel
        {
            std::string local_buf; local_buf.reserve(1<<19);
            long long local_cnt = 0;

            #pragma omp for collapse(3) schedule(dynamic)
            for (int inter = 0; inter < Nipar; ++inter)
            for (int il = 0; il < Nns; ++il)
            for (int j = 0; j < Nns; ++j) {
                if (j == 0) {
                    #pragma omp critical
                    std::cout << "[SgLg] L=" << interiors[inter] << ", n1=" << ns[il]
                              << " start (thread " << thread_id() << ")\n";
                }
                for (int p = 0; p < Nparams; ++p) {
                    TheoryGraph G;
                    auto S  = G.add(s(params[p]));
                    auto N1 = G.add(n_(ns[il]));
                    auto I  = G.add(i(interiors[inter]));
                    auto N2 = G.add(n_(ns[j]));

                    if (!safe_connect(G, S,  N1) ||
                        !safe_connect(G, N1, I)  ||
                        !safe_connect(G, I, N2)) {
                        #pragma omp atomic update
                        progress++;
                        if ((progress % 50000) == 0) print_progress("SgLg", progress, total_SgLg);
                        continue;
                    }

                    Eigen::MatrixXi glued = compose_glue(G);

                    #pragma omp atomic update
                    progress++;
                    if ((progress % 50000) == 0) print_progress("SgLg", progress, total_SgLg);

                    if (evaluate_and_append(glued, local_buf)) ++local_cnt;
                }
            }

            #pragma omp critical
            { cnt.SgLg += local_cnt; out.append(local_buf); }
        }

        flush_to_file("SCFT_SgLg.txt", out);
    }

    // ======================
    // Phase 3: SgLgS  (S on both sides)
    // ======================
    {
        std::string out; out.reserve(1<<22);
        long long progress = 0;

        #pragma omp parallel
        {
            std::string local_buf; local_buf.reserve(1<<20);
            long long local_cnt = 0;

            #pragma omp for collapse(3) schedule(dynamic)
            for (int inter = 0; inter < Nipar; ++inter)
            for (int il = 0; il < Nns; ++il)
            for (int j = 0; j < Nns; ++j) {
                if (j == 0) {
                    #pragma omp critical
                    std::cout << "[SgLgS] L=" << interiors[inter] << ", n1=" << ns[il]
                              << " start (thread " << thread_id() << ")\n";
                }
                for (int pL = 0; pL < Nparams; ++pL) {
                    for (int pR = 0; pR <= pL; ++pR) { // repetition-combination
                        TheoryGraph G;
                        auto SL = G.add(s(params[pL]));
                        auto SR = G.add(s(params[pR]));
                        auto N1 = G.add(n_(ns[il]));
                        auto I  = G.add(i(interiors[inter]));
                        auto N2 = G.add(n_(ns[j]));

                        if (!safe_connect(G, SL, N1) ||
                            !safe_connect(G, N1, I)  ||
                            !safe_connect(G, I, N2)  ||
                            !safe_connect(G, SR, N2)) {
                            #pragma omp atomic update
                            progress++;
                            if ((progress % 50000) == 0) print_progress("SgLgS", progress, total_SgLgS);
                            continue;
                        }

                        Eigen::MatrixXi glued = compose_glue(G);

                        #pragma omp atomic update
                        progress++;
                        if ((progress % 50000) == 0) print_progress("SgLgS", progress, total_SgLgS);

                        if (evaluate_and_append(glued, local_buf)) ++local_cnt;
                    }
                }
            }

            #pragma omp critical
            { cnt.SgLgS += local_cnt; out.append(local_buf); }
        }

        flush_to_file("SCFT_SgLgS.txt", out);
    }

    // ======================
    // Phase 4: SSgLg  (two S on left g)
    // ======================
    {
        std::string out; out.reserve(1<<22);
        long long progress = 0;

        #pragma omp parallel
        {
            std::string local_buf; local_buf.reserve(1<<20);
            long long local_cnt = 0;

            #pragma omp for collapse(3) schedule(dynamic)
            for (int inter = 0; inter < Nipar; ++inter)
            for (int il = 0; il < Nns; ++il)
            for (int j = 0; j < Nns; ++j) {
                if (j == 0) {
                    #pragma omp critical
                    std::cout << "[SSgLg] L=" << interiors[inter] << ", n1=" << ns[il]
                              << " start (thread " << thread_id() << ")\n";
                }
                for (int p1 = 0; p1 < Nparams; ++p1) {
                    for (int p2 = 0; p2 <= p1; ++p2) { // two S on left side
                        TheoryGraph G;
                        auto S1 = G.add(s(params[p1]));
                        auto S2 = G.add(s(params[p2]));
                        auto N1 = G.add(n_(ns[il]));
                        auto I  = G.add(i(interiors[inter]));
                        auto N2 = G.add(n_(ns[j]));

                        if (!safe_connect(G, S1, N1) ||
                            !safe_connect(G, S2, N1) ||
                            !safe_connect(G, N1, I)  ||
                            !safe_connect(G, I, N2)) {
                            #pragma omp atomic update
                            progress++;
                            if ((progress % 50000) == 0) print_progress("SSgLg", progress, total_SSgLg);
                            continue;
                        }

                        Eigen::MatrixXi glued = compose_glue(G);

                        #pragma omp atomic update
                        progress++;
                        if ((progress % 50000) == 0) print_progress("SSgLg", progress, total_SSgLg);

                        if (evaluate_and_append(glued, local_buf)) ++local_cnt;
                    }
                }
            }

            #pragma omp critical
            { cnt.SSgLg += local_cnt; out.append(local_buf); }
        }

        flush_to_file("SCFT_SSgLg.txt", out);
    }

    // ---- final report ----
    std::cout << "total SCFT gLg: "    << cnt.gLg   << "\n"
              << "total SCFT SgLg: "   << cnt.SgLg  << "\n"
              << "total SCFT SgLgS: "  << cnt.SgLgS << "\n"
              << "total SCFT SSgLg: "  << cnt.SSgLg << "\n";

    return 0;
}

