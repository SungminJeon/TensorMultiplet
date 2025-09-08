// Theory.h
#pragma once
#include "Tensor.h"
#include <vector>
#include <utility>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <map>
#include <sstream>
#include <unordered_map>

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
			// s(12) 등 파라미터 내용은 현재 무시: 곡선 2개만 만든다.
			// instantons
			if (sp.param == 1) {t.AT(-1);}
			else if (sp.param == 12 ) {t.AT(-1); t.AT(-2);}
			else if (sp.param == 122 ) {t.AT(-1); t.AT(-2); t.AT(-2);}	
			else if (sp.param == 1222 ) {t.AT(-1); t.AT(-2); t.AT(-2); t.AT(-2);}	
			else if (sp.param == 12222 ) {t.AT(-1); t.AT(-2); t.AT(-2); t.AT(-2); t.AT(-2);}	
			else if (sp.param == 122222 ) {t.AT(-1); t.AT(-2); t.AT(-2); t.AT(-2); t.AT(-2); t.AT(-2);}	
			else if (sp.param == 1222222 ) {t.AT(-1); t.AT(-2); t.AT(-2); t.AT(-2); t.AT(-2); t.AT(-2); t.AT(-2);}	
			else if (sp.param == 12222222 ) {t.AT(-1); t.AT(-2); t.AT(-2); t.AT(-2); t.AT(-2); t.AT(-2); t.AT(-2); t.AT(-2);}
			else if (sp.param == 122222222 ) {t.AT(-1); t.AT(-2); t.AT(-2); t.AT(-2); t.AT(-2); t.AT(-2); t.AT(-2); t.AT(-2); t.AT(-2);}
			else if (sp.param == 1222222222 ) {t.AT(-1); t.AT(-2); t.AT(-2); t.AT(-2); t.AT(-2); t.AT(-2); t.AT(-2); t.AT(-2); t.AT(-2); t.AT(-2);}
			// interiors
			else if (sp.param == 11 ) { t.AL(1,1); }
			else if (sp.param == 22 ) { t.AL(2,2); }
			else if (sp.param == 33 ) { t.AL(3,3); }
			else if (sp.param == 44 ) { t.AL(4,4); }
			else if (sp.param == 55 ) { t.AL(5,5); }
			else if (sp.param == 331 ) { t.AL(3,3,1); }
			else if (sp.param == 32 ) { t.AL(3,2); }
			else if (sp.param == 23 ) { t.AL(2,3); }
			else if (sp.param == 42 ) { t.AL(4,2); }
			else if (sp.param == 24 ) { t.AL(2,4); }
			else if (sp.param == 43 ) { t.AL(4,3); }
			else if (sp.param == 34 ) { t.AL(3,4); }
			else if (sp.param == 53 ) { t.AL(5,3); }
			else if (sp.param == 35 ) { t.AL(3,5); }
			else if (sp.param == 54 ) { t.AL(5,4); }
			else if (sp.param == 45 ) { t.AL(4,5); }

			// alkali 2 links with no -5 

			else if (sp.param == 91 ) { t.AL(5,3); }
			else if (sp.param == 92 ) { t.AL(5,3); }
			else if (sp.param == 93 ) { t.AL(5,3); }
			else if (sp.param == 53 ) { t.AL(5,3); }

			break;
		case Kind::InteriorLink: 
			{
				std::string s = std::to_string(sp.param);
				if (s.size() == 2) {
					int a = s[0]-'0';
					int b = s[1]-'0';
					t.AL(a,b,0);   // 기본 branch = 0
				} else if (s.size() == 3) {
					int a = s[0]-'0';
					int b = s[1]-'0';
					int flag = s[2]-'0';
					t.AL(a,b,flag);
				} else {
					throw std::invalid_argument("i(p): param must be 2 or 3 digits");
				}
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

// ===================== 그래프 TheoryGraph (포트/가중치 확장) =====================

// 포트 라벨
enum class Port : int { Left=0, Right=1, Custom=2 };

// 가중치 간선
struct EdgeW {
    int  u, v;     // 노드 id
    Port pu, pv;   // u의 포트, v의 포트
    int  w;        // 글루잉 강도(대칭 오프대각에 +w)
};

// 기본 포트 선택 정책 (필요하면 강화 가능)
inline int pickPortIndex(Kind /*k*/, const Tensor& t, Port which){
    const auto IF = t.GetIntersectionForm();
    const int sz = static_cast<int>(IF.rows());
    if (sz <= 0) return -1;
    switch(which){
        case Port::Left:   return 0;
        case Port::Right:  return sz - 1;
        case Port::Custom: return (sz >= 2 ? 1 : 0);
    }
    return -1;
}

struct NodeRef { int id; };

class TheoryGraph {
public:
    NodeRef add(Spec sp){
        int id = (int)nodes_.size();
        nodes_.push_back(build_tensor(sp));
        kinds_.push_back(sp.kind);
        params_.push_back(sp.param); // param 저장
        return NodeRef{id};
    }

    // 자동 포트(우↔좌), weight=1
    void connect(NodeRef a, NodeRef b){
        if (forbidden_(kinds_[a.id], kinds_[b.id]))
            throw std::invalid_argument("Forbidden adjacency s-i");
        edgesW_.push_back( EdgeW{a.id,b.id,Port::Right,Port::Left,1} );
    }

    // 포트/가중치 명시 연결
    void connect(NodeRef a, Port pa, NodeRef b, Port pb, int weight=1){
        if (forbidden_(kinds_[a.id], kinds_[b.id]))
            throw std::invalid_argument("Forbidden adjacency s-i");
        if (weight <= 0) throw std::invalid_argument("weight must be positive");
        edgesW_.push_back( EdgeW{a.id,b.id,pa,pb,weight} );
    }

    void print() const {
        std::cout << "TheoryGraph:\n";
        for (auto& e : edgesW_){
            std::cout << "  " << e.u << "(" << (int)e.pu << ") --(" << e.w
                      << ")-- " << e.v << "(" << (int)e.pv << ")\n";
        }
    }

    auto IF(int node) const { return nodes_.at(node).GetIntersectionForm(); }
    void PrintIF(int node, std::ostream& os = std::cout) const {
        os << "IF[node " << node << "]:\n";
        PrintMatrixSafe(IF(node), os);
    }

    // 전 노드 IF 블록대각합 + 포트/가중치 반영
    Eigen::MatrixXi ComposeIF_Gluing() const {
        const int N = (int)nodes_.size();
        if (N==0) return Eigen::MatrixXi();

        // 1) 블록 대각합
        std::vector<Eigen::MatrixXi> blocks; blocks.reserve(N);
        std::vector<int> sz; sz.reserve(N);
        for (auto& t : nodes_) { auto M=t.GetIntersectionForm(); blocks.push_back(M); sz.push_back(M.rows()); }
        Eigen::MatrixXi G = BlockDiag_(blocks);

        // 2) prefix offsets
        std::vector<int> off(N+1,0);
        for (int i=0;i<N;++i) off[i+1]=off[i]+sz[i];

        // 3) 간선마다 포트/가중치 반영
        for (const auto& e : edgesW_){
            int iu = pickPortIndex(kinds_[e.u], nodes_[e.u], e.pu);
            int iv = pickPortIndex(kinds_[e.v], nodes_[e.v], e.pv);
            if (iu<0 || iv<0 || iu>=sz[e.u] || iv>=sz[e.v]) continue; // 방어
            int I = off[e.u] + iu;
            int J = off[e.v] + iv;
            G(I,J) += e.w;
            G(J,I) += e.w;
        }
        return G;
    }

    // 호환: 예전 이름 유지(단, 내부는 가중 글루잉 사용)
    Eigen::MatrixXi ComposeIF_UnitGluing() const {
        return ComposeIF_Gluing();
    }

    int nodeCount() const { return (int)nodes_.size(); }

    // Node/InteriorLink는 가로로, SideLink는 위/아래 분산 + (끝 노드/3개↑) 좌/우 분산 출력
    void printLinearWithSides(bool splitSidesVertically = true) const {
        if (nodes_.empty()) { std::cout << "(empty graph)\n"; return; }

        auto isMain = [&](int id){
            return kinds_[id] == Kind::Node || kinds_[id] == Kind::InteriorLink;
        };
        auto isSide = [&](int id){
            return kinds_[id] == Kind::SideLink;
        };

        const int N = (int)nodes_.size();
        std::vector<std::vector<std::pair<int,int>>> adjMain(N); // (to, weightSum)

        // (min(u,v),max(u,v)) -> weight sum
        std::map<std::pair<int,int>, int> wMain;

        // 메인–메인 간선 집계
        for (const auto& e : edgesW_) {
            int u = e.u, v = e.v, w = e.w;
            if (isMain(u) && isMain(v)) {
                auto key = std::minmax(u,v);
                wMain[key] += w;
            }
        }
        for (auto &kv : wMain) {
            int a = kv.first.first;
            int b = kv.first.second;
            int w = kv.second;
            adjMain[a].emplace_back(b, w);
            adjMain[b].emplace_back(a, w);
        }

        // 메인 컴포넌트 선형화
        std::vector<char> vis(N,0);
        std::vector<std::vector<int>> components;
        for (int i=0;i<N;++i){
            if (!isMain(i) || vis[i]) continue;
            std::vector<int> stack = {i};
            vis[i]=1;
            std::vector<int> order;
            while(!stack.empty()){
                int u = stack.back(); stack.pop_back();
                order.push_back(u);
                for (auto &p : adjMain[u]){
                    int v = p.first;
                    if (!vis[v]){ vis[v]=1; stack.push_back(v); }
                }
            }
            std::sort(order.begin(), order.end());
            components.push_back(std::move(order));
        }

        // 메인 노드별 사이드 id 목록 집계 (mainId -> [side node ids])
        std::unordered_map<int, std::vector<int>> sidesByMain;
        for (const auto& e : edgesW_) {
            int u=e.u, v=e.v;
            bool uSide = isSide(u), vSide = isSide(v);
            bool uMain = !uSide,     vMain = !vSide;
            if (uSide && vMain) sidesByMain[v].push_back(u);
            if (vSide && uMain) sidesByMain[u].push_back(v);
        }

        // 라벨: s12 / n7 / i22
        auto labelNode = [&](int id){
            std::ostringstream ss;
            char kchar = '?';
            switch (kinds_[id]) {
                case Kind::SideLink:     kchar = 's'; break;
                case Kind::InteriorLink: kchar = 'i'; break;
                case Kind::Node:         kchar = 'n'; break;
            }
            ss << kchar << params_[id];
            return ss.str();
        };
        auto betweenWeight = [&](int a, int b)->int{
            auto key = std::minmax(a,b);
            auto it = wMain.find(key);
            return (it==wMain.end()? 0 : it->second);
        };

        // 사이드 분산: 위/아래 + (끝노드에서 3개 이상이면) 좌/우로 1개 이동
        struct SideSplit { std::vector<int> up, dn, left, right; };
        std::unordered_map<int, SideSplit> split; // mainId -> 분산 결과

        auto performSplit = [&](const std::vector<int>& seq){
            for (size_t k=0;k<seq.size();++k){
                int id = seq[k];
                auto it = sidesByMain.find(id);
                SideSplit sp;
                if (it != sidesByMain.end() && !it->second.empty()){
                    auto ids = it->second; // 복사
                    // 기본: 위/아래 분할
                    if (!splitSidesVertically){
                        sp.up = ids; // 모두 위
                    } else {
                        int m = (int)ids.size();
                        int cut = (m+1)/2; // 위가 하나 더 많게
                        sp.up.assign(ids.begin(), ids.begin()+cut);
                        sp.dn.assign(ids.begin()+cut, ids.end());
                    }
                    // 끝 노드 & 3개 이상 → 좌/우로 1개 이동
                    if ((int)ids.size() >= 3){
                        bool isFirst = (k==0);
                        bool isLast  = (k+1==seq.size());
                        if (isFirst ^ isLast){ // 정확히 한쪽 끝일 때
                            // 위/아래 중에서 하나를 빼서 좌/우로
                            auto& pickFrom = (!sp.up.empty() ? sp.up : sp.dn);
                            if (!pickFrom.empty()){
                                int moved = pickFrom.back();
                                pickFrom.pop_back();
                                if (isFirst) sp.left.push_back(moved);
                                else         sp.right.push_back(moved);
                            }
                        }
                    }
                }
                split[id] = std::move(sp);
            }
        };

        std::cout << "Linear-with-sides layout";
        if (splitSidesVertically) std::cout << " (split)";
        std::cout << " (with L/R for 3+ at ends):\n";
        if (components.empty()){ std::cout << "[no main nodes]\n"; return; }

        for (size_t ci=0; ci<components.size(); ++ci){
            const auto& seq = components[ci];
            if (seq.empty()) continue;

            performSplit(seq);

            // 칸 폭 계산
            std::vector<std::string> labels; labels.reserve(seq.size());
            size_t cell = 9;
            for (int id : seq){
                auto L = labelNode(id);
                labels.push_back(L);
                cell = std::max(cell, L.size()+2);
            }

            auto joinIds = [&](const std::vector<int>& v){
                std::ostringstream ss;
                for (size_t i=0;i<v.size();++i){
                    if (i) ss << ",";      // 공백만 원하면 " "로 교체
                    ss << labelNode(v[i]); // s12 등
                }
                return ss.str();
            };

            auto pad = [&](const std::string& s)->std::string{
                if (s.size() >= cell) return s;
                return s + std::string(cell - s.size(), ' ');
            };

            // 1) 위줄
            std::ostringstream top;
            for (size_t k=0;k<seq.size();++k){
                int id=seq[k];
                std::string s = split[id].up.empty() ? std::string(cell,' ')
                                                      : pad(joinIds(split[id].up));
                top << s; if (k+1<seq.size()) top << " ";
            }

            // 2) 중간(위 연결막대)
            std::ostringstream midTop;
            for (size_t k=0;k<seq.size();++k){
                int id=seq[k];
                std::string s(cell,' ');
                if (!split[id].up.empty()){
                    size_t pos = std::min(cell-1, cell/2);
                    s[pos] = '|';
                }
                midTop << s; if (k+1<seq.size()) midTop << " ";
            }

            // 3) 좌/우 보조 라인 (셀 내부 좌/우에 배치)
            std::ostringstream lrLine;
            for (size_t k=0;k<seq.size();++k){
                int id=seq[k];
                std::string s(cell,' ');
                // 왼쪽 (끝 좌측에만 배치)
                if (!split[id].left.empty()){
                    auto txt = joinIds(split[id].left) + "←";
                    for (size_t i=0;i<txt.size() && i<cell; ++i) s[i]=txt[i];
                }
                // 오른쪽 (끝 우측에만 배치)
                if (!split[id].right.empty()){
                    auto txt = "→" + joinIds(split[id].right);
                    if (txt.size() < cell){
                        size_t start = cell - txt.size();
                        for (size_t i=0;i<txt.size(); ++i) s[start+i]=txt[i];
                    } else {
                        // 길면 잘라서 우측 끝에 맞춤
                        for (size_t i=0;i<cell; ++i) s[i]=txt[txt.size()-cell+i];
                    }
                }
                lrLine << s; if (k+1<seq.size()) lrLine << " ";
            }

            // 4) 메인 라인(노드 + 메인 간선 가중치)
            std::ostringstream middle;
            for (size_t k=0;k<seq.size();++k){
                std::string s = labels[k];
                if (s.size()<cell) s += std::string(cell - s.size(), ' ');
                middle << s;
                if (k+1<seq.size()){
                    int w = betweenWeight(seq[k], seq[k+1]);
                    if (w>0) middle << "--";
                    else     middle << "      ";
                }
            }

            // 5) 중간(아래 연결막대)
            std::ostringstream midBot;
            for (size_t k=0;k<seq.size();++k){
                int id=seq[k];
                std::string s(cell,' ');
                if (!split[id].dn.empty()){
                    size_t pos = std::min(cell-1, cell/2);
                    s[pos] = '|';
                }
                midBot << s; if (k+1<seq.size()) midBot << " ";
            }

            // 6) 아래줄
            std::ostringstream bottom;
            for (size_t k=0;k<seq.size();++k){
                int id=seq[k];
                std::string s = split[id].dn.empty() ? std::string(cell,' ')
                                                      : pad(joinIds(split[id].dn));
                bottom << s; if (k+1<seq.size()) bottom << " ";
            }

            if (ci>0) std::cout << "\n";
            std::cout << top.str()    << "\n";
            std::cout << midTop.str() << "\n";
            std::cout << lrLine.str() << "\n";   // 좌/우 라인
            std::cout << middle.str() << "\n";
            std::cout << midBot.str() << "\n";
            std::cout << bottom.str() << "\n";
        }
    }

private:
    std::vector<Tensor> nodes_;
    std::vector<Kind>   kinds_;
    std::vector<int>    params_;   // 각 노드의 Spec.param 저장
    std::vector<EdgeW>  edgesW_;

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

