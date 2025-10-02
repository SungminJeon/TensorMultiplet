// topology_node2_scft.cpp
// 목적: 두 노드(g–L–g), SgLg, SgLgS 전수 탐색 → IF 구성 → SCFT 판정(블로우다운 포함) → "통과 개수" 집계
// 빌드 예:
//   g++ -std=c++17 -O3 -Wall -Wextra -I/usr/include/eigen3 \
//       topology_node2_scft.cpp Tensor.C Theory.C -o topology_node2
// 실행 예:
//   ./topology_node2           # 카운트만
//   ./topology_node2 dump      # 통과한 IF 스냅샷을 SCFT_node2_*.txt로 저장
//
// 메모:
//  - 이 파일은 Tensor/Theory 구현에 의존합니다. (SetIF/Setb0Q/TimeDirection/NullDirection/ForcedBlowdown, ComposeIF_* 등)

#ifndef USE_UNIT_GLUING
#define USE_UNIT_GLUING 1    // 1: ComposeIF_UnitGluing(), 0: ComposeIF_Gluing()
#endif

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include <Eigen/Dense>
#include "Tensor.h"
#include "Theory.h"

// ---------------- 단순 유틸 ----------------
static inline void print_progress(const char* name, long long done, long long total) {
    if (total <= 0) return;
    const long long step = std::max(1LL, total / 100); // 1% 단위
    if ((done % step) == 0 || done == total) {
        const double pct = 100.0 * double(done) / double(total);
        std::cerr << "[" << name << "] " << done << "/" << total
                  << " (" << std::fixed << std::setprecision(1) << pct << "%)\n";
    }
}

static inline void append_to_file(const std::string& path, const std::string& buf) {
    if (buf.empty()) return;
    std::ofstream ofs(path, std::ios::app);
    if (!ofs) { std::cerr << "[!] cannot open: " << path << "\n"; return; }
    ofs << buf;
}

// TheoryGraph::connect() 예외를 안전히 잡기 위한 래퍼
template <class A, class B>
static inline bool safe_connect(TheoryGraph& G, A a, B b) noexcept {
    try { G.connect(a, b); return true; }
    catch (const std::invalid_argument&) { return false; }
}

// IF → SCFT 판정 (블로우다운 포함)
static inline bool scft_pass(const Eigen::MatrixXi& IF) {
    Tensor T;
    T.SetIF(IF);
    T.Setb0Q();
    if (T.TimeDirection() != 0 || T.NullDirection() != 0) return false;
    T.ForcedBlowdown();
    return T.TimeDirection() == 0 && T.NullDirection() == 0;
}

static inline Eigen::MatrixXi compose_glue(const TheoryGraph& G) {
#if USE_UNIT_GLUING
    return G.ComposeIF_UnitGluing();
#else
    return G.ComposeIF_Gluing();
#endif
}

// IF 직렬화(공백 구분, 줄 바꿈; 블록마다 빈 줄 하나)
static inline void serialize_IF(const Eigen::MatrixXi& IF, std::string& out) {
    const int R = IF.rows(), C = IF.cols();
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            if (c) out.push_back(' ');
            out.append(std::to_string(IF(r, c)));
        }
        out.push_back('\n');
    }
    out.push_back('\n');
}

// ---------------- 메인 ----------------
int main(int argc, char** argv) {
    const bool dump = (argc >= 2 && std::string(argv[1]) == "dump");

    // 파라미터 테이블 (이전 대화 기준)
    const int PARAMS[] = {
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
    const int INTERIORS[] = { 11,22,33,44,55,331,32,23,42,24,43,34,53,35,54,45 };
    const int NS[]        = { 4,6,7,8,12 };

    const int Nparams = int(sizeof(PARAMS)    / sizeof(PARAMS[0]));
    const int Nipar   = int(sizeof(INTERIORS) / sizeof(INTERIORS[0]));
    const int Nns     = int(sizeof(NS)        / sizeof(NS[0]));

    // 토탈(진행률 표시에 사용)
    const long long total_node2 = 1LL * Nns * Nns * Nipar;
    const long long total_sglg  = 1LL * Nns * Nns * Nparams * Nipar;
    const long long total_sglgs = 1LL * Nns * Nns * (long long)Nparams * (Nparams - 1) / 2 * Nipar;

    std::cout << "[Init] totals — "
              << "node2_gLg:" << total_node2
              << ", SgLg:"    << total_sglg
              << ", SgLgS:"   << total_sglgs
              << std::endl;

    if (dump) {
        std::ofstream("SCFT_node2_gLg.txt",  std::ios::trunc).close();
        std::ofstream("SCFT_node2_SgLg.txt", std::ios::trunc).close();
        std::ofstream("SCFT_node2_SgLgS.txt",std::ios::trunc).close();
    }

    long long cnt_node2 = 0, cnt_sglg = 0, cnt_sglgs = 0;

    // -------- Phase 0: node2_gLg (두 노드 + interior 하나) --------
    {
        std::string out; out.reserve(1<<21);
        long long done = 0;

        for (int ia=0; ia<Nns; ++ia)
        for (int ib=0; ib<=ia; ++ib)
        for (int t=0; t<Nipar; ++t) {
            const int na = NS[ia], nb = NS[ib], gi = INTERIORS[t];

            TheoryGraph G;
            auto NA = G.add(n_(na));
            auto GB = G.add(i(gi));   // 주의: i_()가 아니라 i() 네이밍 가정
            auto NB = G.add(n_(nb));
            if (!safe_connect(G, NA, GB) || !safe_connect(G, GB, NB)) {
                ++done; print_progress("node2_gLg", done, total_node2); continue;
            }

            Eigen::MatrixXi IF = compose_glue(G);
            if (scft_pass(IF)) {
                ++cnt_node2;
                if (dump) serialize_IF(IF, out);
            }

            ++done; print_progress("node2_gLg", done, total_node2);
        }

        if (dump) append_to_file("SCFT_node2_gLg.txt", out);
        std::cout << "[Done] node2_gLg: " << cnt_node2
                  << (dump ? " (dumped)" : "") << std::endl;
    }

    // -------- Phase 0.5: node2_SgLg (한쪽 노드에 사이드 링크 1개) --------
    {
        std::string out; out.reserve(1<<21);
        long long done = 0;

        for (int ia=0; ia<Nns; ++ia)
        for (int ib=0; ib<Nns; ++ib)
        for (int t=0; t<Nipar; ++t)
        for (int p=0; p<Nparams; ++p) {
            const int na = NS[ia], nb = NS[ib], gi = INTERIORS[t], sp = PARAMS[p];

            TheoryGraph G;
            auto NA = G.add(n_(na));
            auto GB = G.add(i(gi));
            auto NB = G.add(n_(nb));
            auto SA = G.add(s(sp));   // 주의: s_()가 아니라 s() 네이밍 가정

            if (!safe_connect(G, NA, GB) || !safe_connect(G, GB, NB) || !safe_connect(G, SA, NA)) {
                ++done; print_progress("node2_SgLg", done, total_sglg); continue;
            }

            Eigen::MatrixXi IF = compose_glue(G);
            if (scft_pass(IF)) {
                ++cnt_sglg;
                if (dump) serialize_IF(IF, out);
            }

            ++done; print_progress("node2_SgLg", done, total_sglg);
        }

        if (dump) append_to_file("SCFT_node2_SgLg.txt", out);
        std::cout << "[Done] node2_SgLg: " << cnt_sglg
                  << (dump ? " (dumped)" : "") << std::endl;
    }

    // -------- Phase 0.6: node2_SgLgS (양쪽 노드에 서로 다른 사이드 링크 2개; p<q) --------
    {
        std::string out; out.reserve(1<<22);
        long long done = 0;

        for (int ia=0; ia<Nns; ++ia)
        for (int ib=0; ib<=ia; ++ib)
        for (int t=0; t<Nipar; ++t)
        for (int p=0; p<Nparams; ++p) {
            for (int q=p+1; q<Nparams; ++q) {
                const int na = NS[ia], nb = NS[ib], gi = INTERIORS[t];
                const int spL = PARAMS[p], spR = PARAMS[q];

                TheoryGraph G;
                auto NA = G.add(n_(na));
                auto GB = G.add(i(gi));
                auto NB = G.add(n_(nb));
                auto SA = G.add(s(spL));
                auto SB = G.add(s(spR));

                if (!safe_connect(G, NA, GB) || !safe_connect(G, GB, NB) ||
                    !safe_connect(G, SA, NA) || !safe_connect(G, SB, NB)) {
                    ++done; print_progress("node2_SgLgS", done, total_sglgs); continue;
                }

                Eigen::MatrixXi IF = compose_glue(G);
                if (scft_pass(IF)) {
                    ++cnt_sglgs;
                    if (dump) serialize_IF(IF, out);
                }

                ++done; print_progress("node2_SgLgS", done, total_sglgs);
            }
        }

        if (dump) append_to_file("SCFT_node2_SgLgS.txt", out);
        std::cout << "[Done] node2_SgLgS: " << cnt_sglgs
                  << (dump ? " (dumped)" : "") << std::endl;
    }

    // 최종 요약
    std::cout << "\n=== TOTAL (SCFT-passed) ===\n"
              << "node2_gLg :  " << cnt_node2  << "\n"
              << "node2_SgLg:  " << cnt_sglg   << "\n"
              << "node2_SgLgS: " << cnt_sglgs  << "\n";
    return 0;
}

