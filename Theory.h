// Theory.h  (파일명 통일: test.C도 "Theory.h"로 include 하세요)
#pragma once
#include "Tensor.h"
#include <vector>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <iostream>   // <-- 추가

enum class Kind { SideLink, InteriorLink, Node };

struct Spec { Kind kind; int param; };
inline Spec s(int p){ return {Kind::SideLink,    p}; }
inline Spec i(int p){ return {Kind::InteriorLink, p}; }
inline Spec n_(int p){ return {Kind::Node,         p}; }

// 공통 빌더 (간단 예시)
inline Tensor build_tensor(const Spec& sp){
    Tensor t;
    switch(sp.kind){
        case Kind::SideLink:
            t.AT(-1);
            t.AT(-2);
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

struct Piece { Kind kind; Tensor tensor; };

class Theory {
public:
    using Segment = std::vector<Piece>;

    static Theory from(std::initializer_list<std::initializer_list<Spec>> segs){
        Theory T;
        for (auto& segSpecs : segs){
            Segment seg;
            seg.reserve(segSpecs.size());
            for (auto& sp : segSpecs){
                seg.push_back(Piece{ sp.kind, build_tensor(sp) });
            }
            T.append(std::move(seg));
        }
        return T;
    }

    // ---- 추가: 간단 print ----
   
    void print() const {
	    std::cout << "Theory(sequential):\n";
	    for (size_t si=0; si<segments_.size(); ++si){
		    std::cout << "  Segment " << si << ":";
		    for (size_t pi=0; pi<segments_[si].size(); ++pi){
			    std::cout << " [kind=" << static_cast<int>(segments_[si][pi].kind)
				    << ", curves=" << segments_[si][pi].tensor.SpaceDirection()
				    << "]";
		    }
		    std::cout << "\n";
	    }
    }


    auto IF(size_t seg_idx, size_t piece_idx) const {
	    // auto를 쓰면 반환 형식이 ref든 value든 그대로 따라감
	    return segments_[seg_idx][piece_idx].tensor.GetIntersectionForm();
    }

    void PrintIF(size_t seg_idx, size_t piece_idx, std::ostream& os = std::cout) const {
	    os << "IF[segment " << seg_idx << ", piece " << piece_idx << "]:\n"
		    << IF(seg_idx, piece_idx) << '\n';
    }


    auto IF(int node_id) const {
	    return nodes_.at(node_id).GetIntersectionForm();
    }

    void PrintIF(int node_id, std::ostream& os = std::cout) const {
	    os << "IF[node " << node_id << "]:\n"
		    << IF(node_id) << '\n';
    }



    // adding method //
    

    inline Eigen::MatrixXi BlockDiag(const std::vector<Eigen::MatrixXi>& blocks){
	    Eigen::Index total = 0;
	    for (auto& M : blocks) total += M.rows();
	    Eigen::MatrixXi out = Eigen::MatrixXi::Zero(total, total);
	    Eigen::Index off = 0;
	    for (auto& M : blocks){
		    out.block(off, off, M.rows(), M.cols()) = M;
		    off += M.rows();
	    }
	    return out;
    }

    // Theory 전체
    Eigen::MatrixXi TheoryIF_BlockDiag() const {
	    std::vector<Eigen::MatrixXi> blocks;
	    for (auto& seg : segments_)
		    for (auto& p : seg)
			    blocks.push_back(p.tensor.GetIntersectionForm()); // ref든 value든 여기서 복사되어 블록으로
	    return BlockDiag(blocks);
    }

    // Graph 전체
    Eigen::MatrixXi GraphIF_BlockDiag() const {
	    std::vector<Eigen::MatrixXi> blocks; blocks.reserve(nodes_.size());
	    for (auto& t : nodes_) blocks.push_back(t.GetIntersectionForm());
	    return BlockDiag(blocks);
    }

    Eigen::MatrixXi ComposeIF_UnitGluing() const {
	    // (a) 각 노드의 로컬 IF 수집 + 사이즈/오프셋 계산
	    const int N = static_cast<int>(nodes_.size());
	    std::vector<Eigen::MatrixXi> blocks; blocks.reserve(N);
	    std::vector<int> sizes; sizes.reserve(N);
	    for (const auto& t : nodes_) {
		    auto M = t.GetIntersectionForm();   // const로 선언되어 있으면 더 깔끔
		    blocks.push_back(M);
		    sizes.push_back(M.rows());
	    }

	    // (b) 블록 대각합으로 큰 행렬 생성
	    Eigen::MatrixXi G = BlockDiag(blocks);

	    // (c) 노드별 row offset(prefix sum)
	    std::vector<int> offset(N + 1, 0);
	    for (int i = 0; i < N; ++i) offset[i + 1] = offset[i] + sizes[i];

	    // (d) 각 간선(u—v)에 대해 포트 선택 후 오프대각에 +1
	    for (auto [u, v] : edges_) {
		    // 포트 선택
		    Ports pu = choose_ports(kinds_[u], nodes_[u]);
		    Ports pv = choose_ports(kinds_[v], nodes_[v]);

		    // 기본: u의 "오른쪽", v의 "왼쪽"을 잇는다고 가정 (필요시 규칙 변경)
		    int lu = pu.right;
		    int lv = pv.left;

		    // 경계 체크(방어적)
		    if (lu < 0 || lu >= sizes[u] || lv < 0 || lv >= sizes[v]) continue;

		    int I = offset[u] + lu;
		    int J = offset[v] + lv;

		    // 단위 결합: 대칭으로 +1
		    G(I, J) += 1;
		    G(J, I) += 1;
	    }
	    return G;
    }



private:
    std::vector<Segment> segments_;

    static bool forbidden(Kind a, Kind b){
	    return ( (a==Kind::SideLink && b==Kind::InteriorLink) ||
			    (a==Kind::InteriorLink && b==Kind::SideLink) );
    }

    static void check_inside(const Segment& seg){
	    for (size_t k=1;k<seg.size();++k){
		    if (forbidden(seg[k-1].kind, seg[k].kind))
			    throw std::invalid_argument("Forbidden adjacency s-i inside segment");
	    }
    }
    void check_boundary(const Segment& seg) const {
	    if (segments_.empty() || seg.empty()) return;
	    if (forbidden(segments_.back().back().kind, seg.front().kind))
		    throw std::invalid_argument("Forbidden adjacency s-i across segments");
    }
    void append(Segment seg){
        check_inside(seg);
        check_boundary(seg);
        segments_.push_back(std::move(seg));
    }
};

// ---- 그래프 버전 ----
struct NodeRef { int id; };

class TheoryGraph {
public:
    NodeRef add(Spec sp){
        Tensor t = build_tensor(sp);
        int id = static_cast<int>(nodes_.size());
        nodes_.push_back(std::move(t));
        kinds_.push_back(sp.kind);
        return NodeRef{id};
    }

    void connect(NodeRef a, NodeRef b){
        if (forbidden(kinds_[a.id], kinds_[b.id]))
            throw std::invalid_argument("Forbidden adjacency s-i");
        edges_.push_back({a.id,b.id});
    }

    void print() const {
        std::cout << "TheoryGraph:\n";
        for (auto& e : edges_){
            std::cout << "  " << e.first << " -- " << e.second << "\n";
        }
    }

    void connect(NodeRef a, NodeRef b, int portA, int portB){
	    if (forbidden(kinds_[a.id], kinds_[b.id]))
		    throw std::invalid_argument("Forbidden adjacency s-i");

	    // 유효성 체크(간단)
	    int sa = const_cast<Tensor&>(nodes_[a.id]).SpaceDirection();
	    int sb = const_cast<Tensor&>(nodes_[b.id]).SpaceDirection();
	    if (portA < 0 || portA >= sa || portB < 0 || portB >= sb)
		    throw std::out_of_range("Bad port index");

	    edges_.push_back({a.id, b.id});
	    // (선택) 포트 선택 기록 저장 (예: 별도 map<pair<int,int>, pair<int,int>> ports)
	    port_override_[{a.id,b.id}] = {portA, portB};
    }
private:
    std::vector<Tensor> nodes_;
    std::vector<Kind> kinds_;
    std::vector<std::pair<int,int>> edges_;

    static bool forbidden(Kind a, Kind b){
        return ( (a==Kind::SideLink && b==Kind::InteriorLink) ||
                 (a==Kind::InteriorLink && b==Kind::SideLink) );
    }
};

