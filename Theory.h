// Theory.h
#pragma once
#include "Tensor.h"
#include <vector>
#include <utility>
#include <stdexcept>
#include <iostream>

// ---- 종류 & 스펙 헬퍼 ----
enum class Kind { SideLink, InteriorLink, Node };
struct Spec { Kind kind; int param; };
inline Spec s(int p){ return {Kind::SideLink,     p}; }
inline Spec i(int p){ return {Kind::InteriorLink, p}; }
inline Spec n_(int p){ return {Kind::Node,        p}; }

// ---- 0x0 행렬 안전 출력 (크래시 방지용) ----
template <class M>
inline void PrintMatrixSafe(const M& A, std::ostream& os = std::cout){
    if (A.rows()==0 || A.cols()==0) { os << "[empty 0x0 matrix]\n"; return; }
    os << A << '\n';
}

// ---- Spec -> Tensor (아주 단순 규칙) ----
inline Tensor build_tensor(const Spec& sp){
    Tensor t;
    switch (sp.kind){
        case Kind::SideLink:
            // s(12) 같은 파라미터 내용은 신경 안 쓰고, 곡선 2개만 만든다.
            t.AT(-1); t.AT(-2);
            break;
        case Kind::InteriorLink: {
            int a = sp.param / 10, b = sp.param % 10;
            if (a<=0 || b<=0) throw std::invalid_argument("i(p): two-digit positive required");
            t.AL(a,b);
            break;
        }
        case Kind::Node:
            t.AT(-sp.param);
            break;
    }
    return t;
}

// ===================== 선형 Theory =====================
struct Piece { Kind kind; Tensor tensor; };

class Theory {
public:
    using Segment = std::vector<Piece>;

    // 예) Theory::from({ { s(12), n_(7) }, { i(22) } });
    static Theory from(std::initializer_list<std::initializer_list<Spec>> segs){
        Theory T;
        for (const auto& segSpecs : segs){
            Segment seg;
            for (const auto& sp : segSpecs)
                seg.push_back(Piece{sp.kind, build_tensor(sp)});
            T.append(std::move(seg));
        }
        return T;
    }

    void print() const {
        std::cout << "Theory(sequential):\n";
        for (size_t si=0; si<segments_.size(); ++si){
            std::cout << "  Segment " << si << ":";
            for (size_t pi=0; pi<segments_[si].size(); ++pi){
                std::cout << " [kind=" << (int)segments_[si][pi].kind
                          << ", curves=" << segments_[si][pi].tensor.SpaceDirection() << "]";
            }
            std::cout << "\n";
        }
    }

    auto IF(size_t seg, size_t piece) const {
        return segments_.at(seg).at(piece).tensor.GetIntersectionForm();
    }
    void PrintIF(size_t seg, size_t piece, std::ostream& os = std::cout) const {
        os << "IF[segment " << seg << ", piece " << piece << "]:\n";
        PrintMatrixSafe(IF(seg, piece), os);
    }

    // 모든 조각의 IF를 블록대각합으로
    Eigen::MatrixXi TheoryIF_BlockDiag() const {
        std::vector<Eigen::MatrixXi> blocks;
        for (auto& seg : segments_)
            for (auto& p : seg)
                blocks.push_back(p.tensor.GetIntersectionForm());
        return BlockDiag_(blocks);
    }

private:
    std::vector<Segment> segments_;

    static bool forbidden_(Kind a, Kind b){
        // s-i 인접 금지 (요구사항 반영)
        return ( (a==Kind::SideLink && b==Kind::InteriorLink) ||
                 (a==Kind::InteriorLink && b==Kind::SideLink) );
    }
    static void check_inside_(const Segment& seg){
        for (size_t k=1; k<seg.size(); ++k)
            if (forbidden_(seg[k-1].kind, seg[k].kind))
                throw std::invalid_argument("Forbidden adjacency s-i inside segment");
    }
    void check_boundary_(const Segment& seg) const {
        if (segments_.empty() || seg.empty()) return;
        if (forbidden_(segments_.back().back().kind, seg.front().kind))
            throw std::invalid_argument("Forbidden adjacency s-i across segments");
    }
    void append(Segment seg){
        check_inside_(seg);
        check_boundary_(seg);
        segments_.push_back(std::move(seg));
    }

    static Eigen::MatrixXi BlockDiag_(const std::vector<Eigen::MatrixXi>& blocks){
        if (blocks.empty()) return Eigen::MatrixXi(); // 0x0
        Eigen::Index total = 0;
        for (auto& M : blocks) total += M.rows();
        if (total==0) return Eigen::MatrixXi();
        Eigen::MatrixXi out = Eigen::MatrixXi::Zero(total, total);
        Eigen::Index off = 0;
        for (auto& M : blocks){
            if (M.size()==0) continue;
            out.block(off, off, M.rows(), M.cols()) = M;
            off += M.rows();
        }
        return out.block(0,0,off,off);
    }
};

// ===================== 그래프 TheoryGraph (초간단) =====================
struct NodeRef { int id; };

class TheoryGraph {
public:
    NodeRef add(Spec sp){
        int id = (int)nodes_.size();
        nodes_.push_back(build_tensor(sp));
        kinds_.push_back(sp.kind);
        return NodeRef{id};
    }

    // 자동 포트만 지원 (오버라이드 없음)
    void connect(NodeRef a, NodeRef b){
        if (forbidden_(kinds_[a.id], kinds_[b.id]))
            throw std::invalid_argument("Forbidden adjacency s-i");
        edges_.push_back({a.id,b.id});
    }

    void print() const {
        std::cout << "TheoryGraph:\n";
        for (auto& e : edges_) std::cout << "  " << e.first << " -- " << e.second << "\n";
    }

    auto IF(int node) const { return nodes_.at(node).GetIntersectionForm(); }
    void PrintIF(int node, std::ostream& os = std::cout) const {
        os << "IF[node " << node << "]:\n";
        PrintMatrixSafe(IF(node), os);
    }

    // 전 노드 IF 블록대각합 + 간선마다 오프대각 +1 (간단 글루잉)
    Eigen::MatrixXi ComposeIF_UnitGluing() const {
        const int N = (int)nodes_.size();
        if (N==0) return Eigen::MatrixXi();

        std::vector<Eigen::MatrixXi> blocks; blocks.reserve(N);
        std::vector<int> sz; sz.reserve(N);
        for (auto& t : nodes_){ auto M=t.GetIntersectionForm(); blocks.push_back(M); sz.push_back(M.rows()); }
        Eigen::MatrixXi G = BlockDiag_(blocks);

        // prefix offsets
        std::vector<int> off(N+1,0);
        for (int i=0;i<N;++i) off[i+1]=off[i]+sz[i];

        // 자동 포트 규칙: (u: right=sz[u]-1) ↔ (v: left=0)
        for (auto [u,v] : edges_){
            int pu = (sz[u]>0? sz[u]-1: -1);
            int pv = (sz[v]>0? 0       : -1);
            if (pu<0 || pv<0) continue;
            G(off[u]+pu, off[v]+pv) += 1;
            G(off[v]+pv, off[u]+pu) += 1;
        }
        return G;
    }

    int nodeCount() const { return (int)nodes_.size(); }

private:
    std::vector<Tensor> nodes_;
    std::vector<Kind>   kinds_;
    std::vector<std::pair<int,int>> edges_;

    static bool forbidden_(Kind a, Kind b){
        return ( (a==Kind::SideLink && b==Kind::InteriorLink) ||
                 (a==Kind::InteriorLink && b==Kind::SideLink) );
    }
    static Eigen::MatrixXi BlockDiag_(const std::vector<Eigen::MatrixXi>& blocks){
        if (blocks.empty()) return Eigen::MatrixXi();
        Eigen::Index total = 0;
        for (auto& M : blocks) total += M.rows();
        if (total==0) return Eigen::MatrixXi();
        Eigen::MatrixXi out = Eigen::MatrixXi::Zero(total, total);
        Eigen::Index off = 0;
        for (auto& M : blocks){
            if (M.size()==0) continue;
            out.block(off, off, M.rows(), M.cols()) = M;
            off += M.rows();
        }
        return out.block(0,0,off,off);
    }
};

