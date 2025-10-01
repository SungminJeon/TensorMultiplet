// build_if_from_block.cpp
#include <bits/stdc++.h>
#include <Eigen/Dense>
using namespace std;

// ---------- Tokenizer ----------
enum class Tok { L, R, INT };
struct T { Tok t; int v; };

static vector<T> tokenize(const string& s){
    vector<T> out;
    int n = (int)s.size();
    for(int i=0;i<n;){
        unsigned char c = s[i];
        if (isspace(c)) { ++i; continue; }
        if (c=='{'){ out.push_back({Tok::L,0}); ++i; continue; }
        if (c=='}'){ out.push_back({Tok::R,0}); ++i; continue; }
        if (c=='-' || isdigit(c)){
            int j=i; bool neg=false;
            if (s[j]=='-'){ neg=true; ++j; }
            long long val=0;
            while(j<n && isdigit((unsigned char)s[j])){ val = val*10 + (s[j]-'0'); ++j; }
            if (neg) val = -val;
            out.push_back({Tok::INT,(int)val});
            i=j; continue;
        }
        // 기타 문자 스킵
        ++i;
    }
    return out;
}

// ---------- Tree ----------
struct Node{
    bool leaf=false;
    int  val=0;
    vector<Node> ch;
};
static int parse_group(const vector<T>& ts, int i, Node& out){
    // assume ts[i] == '{'
    out.leaf=false; out.val=0; out.ch.clear();
    ++i;
    while(i<(int)ts.size()){
        if (ts[i].t==Tok::R){ ++i; break; }
        if (ts[i].t==Tok::L){
            Node g; i = parse_group(ts,i,g);
            out.ch.push_back(std::move(g));
        }else if (ts[i].t==Tok::INT){
            Node l; l.leaf=true; l.val=ts[i].v;
            out.ch.push_back(l); ++i;
        }else{
            ++i;
        }
    }
    return i;
}
static Node parse_block_tree(const vector<T>& ts){
    int i=0;
    while(i<(int)ts.size() && ts[i].t!=Tok::L) ++i;
    Node root; parse_group(ts,i,root); return root;
}

// ---------- Find last-occurring node (4,6,7,8,12) & path ----------
static const int NODESET_ARR[5]={4,6,7,8,12};
static bool is_node_val(int v){
    int a=std::abs(v);
    for(int x: NODESET_ARR) if (a==x) return true;
    return false;
}
// store path as indices along children from root to the leaf (exclusive of leaf level’s parent? we want leaf index too)
static void find_all_paths_last(const Node& u, vector<int>& cur, vector<int>& best, bool& seen){
    // inorder over group tree
    if (u.leaf) return;
    for(int i=0;i<(int)u.ch.size();++i){
        const Node& c = u.ch[i];
        if (c.leaf){
            if (is_node_val(c.val)){
                // found candidate leaf
                vector<int> cand = cur; cand.push_back(i); // include child index of leaf
                best = cand; seen=true; // overwrite -> last encountered wins
            }
        }else{
            cur.push_back(i);
            find_all_paths_last(c,cur,best,seen);
            cur.pop_back();
        }
    }
}

// ---------- Make side-link prefixes ----------
static Node clone_prefix_upto_child(const Node& parent, int child_idx){
    // parent is non-leaf. take children [0 .. child_idx-1]
    Node g; g.leaf=false;
    for(int i=0;i<child_idx;i++) g.ch.push_back(parent.ch[i]);
    return g;
}
// From root & path (indices to the leaf), build side-link nodes (skip empties)
static vector<Node> build_side_links_from_path(const Node& root, const vector<int>& path){
    vector<Node> links;
    if (path.empty()) return links; // should not happen
    // Traverse down using the path, gathering "left prefixes"
    const Node* cur = &root;
    for(size_t depth=0; depth<path.size(); ++depth){
        int idx = path[depth];
        // prefix at this depth
        Node pref = clone_prefix_upto_child(*cur, idx);
        // keep only if it has at least one number inside
        // (we'll check later by evaluating/flattening; here we just push and later drop empties)
        links.push_back(std::move(pref));
        // go down
        const Node& child = cur->ch[idx];
        if (child.leaf){
            // path should end here
            break;
        }else{
            cur = &child;
        }
    }
    // remove empties later
    return links;
}

// ---------- Build one side-link into values & edges ----------
// Rule: within any group, connect "last-of(child_k)" -> "last-of(child_{k+1})"
// Recursively, each node returns whether it contributed any indices and its "last index".
struct BuildCtx{
    vector<int> values;                     // sequence of numbers (diagonal = -values[i])
    vector<pair<int,int>> edges;            // undirected edges (+1)
    int add_leaf(int v){
        int pos = (int)values.size();
        values.push_back(v);
        return pos;
    }
    // for de-dup
    void add_edge(int a, int b){
        if (a<0 || b<0 || a==(int)values.size() || b==(int)values.size()) return;
        if (a==b) return;
        if (a>b) std::swap(a,b);
        static unordered_set<uint64_t> S; // shared across calls OK: we clear per link below
        // (we'll not use this S here; instead, edges will be deduped after build by set)
        edges.emplace_back(a,b);
    }
};
struct Ret { bool any=false; int last=-1; };

// dedup edges helper
static void dedup_edges(vector<pair<int,int>>& e){
    sort(e.begin(), e.end());
    e.erase(unique(e.begin(), e.end()), e.end());
}

// Recursively process node into ctx, return {any,last}
static Ret build_group(const Node& u, BuildCtx& ctx){
    if (u.leaf){
        int pos = ctx.add_leaf(u.val);
        return {true, pos};
    }
    vector<int> child_last_indices; child_last_indices.reserve(u.ch.size());
    for (const Node& c : u.ch){
        Ret r = build_group(c, ctx);
        if (r.any) child_last_indices.push_back(r.last);
    }
    // connect consecutive child "last"s
    for (int i=1;i<(int)child_last_indices.size();++i){
        int a = child_last_indices[i-1];
        int b = child_last_indices[i];
        ctx.edges.emplace_back(min(a,b), max(a,b));
    }
    if (child_last_indices.empty()) return {false,-1};
    return {true, child_last_indices.back()};
}

// ---------- Compose all links + central node to IF ----------
struct LinkBuilt{
    vector<int> vals;
    vector<pair<int,int>> edges;
    int last_idx=-1; // index in its own local coords
};

static LinkBuilt build_one_link(const Node& link){
    BuildCtx ctx;
    Ret r = build_group(link, ctx);
    // drop if empty
    if (!r.any){
        return LinkBuilt{};
    }
    auto es = ctx.edges;
    dedup_edges(es);
    return LinkBuilt{ctx.values, es, r.last};
}

static Eigen::MatrixXi compose_IF(const vector<LinkBuilt>& links, int node_value){
    // order: longest link first
    vector<int> order(links.size());
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int i, int j){
        return links[i].vals.size() > links[j].vals.size();
    });

    int totalN = 1; // central node
    for(int i: order) totalN += (int)links[i].vals.size();

    Eigen::MatrixXi M = Eigen::MatrixXi::Zero(totalN,totalN);

    int offset = 0;
    for(int i_idx=0;i_idx<(int)order.size();++i_idx){
        int k = order[i_idx];
        const auto& L = links[k];
        // diagonals
        for (int i=0;i<(int)L.vals.size();++i){
            M(offset+i, offset+i) = -L.vals[i];
        }
        // edges
        for (auto [a,b] : L.edges){
            M(offset+a, offset+b) = 1;
            M(offset+b, offset+a) = 1;
        }
        offset += (int)L.vals.size();
    }

    int node_idx = totalN-1;
    M(node_idx,node_idx) = -std::abs(node_value);

    // connect each link's rightmost (its last) to node
    offset = 0;
    for(int i_idx=0;i_idx<(int)order.size();++i_idx){
        int k = order[i_idx];
        const auto& L = links[k];
        if (L.vals.empty()) continue;
        int end_local = L.last_idx;
        int end_global = offset + end_local;
        M(end_global, node_idx) = 1;
        M(node_idx, end_global) = 1;
        offset += (int)L.vals.size();
    }

    return M;
}

// ---------- Utilities ----------
static bool has_any_number(const Node& g){
    if (g.leaf) return true;
    for (auto& c: g.ch) if (has_any_number(c)) return true;
    return false;
}

static string trim_copy(string s){
    // remove everything before first '{' and after last '}'
    auto l = s.find('{');
    auto r = s.rfind('}');
    if (l!=string::npos && r!=string::npos && r>=l) s = s.substr(l, r-l+1);
    return s;
}

// ---------- Main ----------
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string input;
    {
        // 읽기: 한 줄 전체(공백 포함)
        std::ostringstream oss;
        string line;
        while (getline(cin, line)){
            oss << line << ' ';
        }
        input = oss.str();
        if (input.find('{')==string::npos){
            // 샘플
            input = "{2 2 3 1 {1 5} 1 3 2 2 1 {1 {1 12}}}";
        }
    }
    input = trim_copy(input);

    auto toks = tokenize(input);
    Node root = parse_block_tree(toks);

    // 노드 경로(오른쪽/마지막으로 등장하는 4/6/7/8/12)
    vector<int> cur, best;
    bool seen=false;
    find_all_paths_last(root, cur, best, seen);
    if (!seen){
        cerr << "error: 블록 안에서 노드(4/6/7/8/12)를 찾지 못했습니다.\n";
        return 1;
    }

    // 사이드링크(각 조상 레벨의 '왼쪽 prefix')
    auto link_nodes = build_side_links_from_path(root, best);

    // 빌드 & 빈 링크 제거
    vector<LinkBuilt> links;
    for (auto& ln : link_nodes){
        if (!has_any_number(ln)) continue;
        auto L = build_one_link(ln);
        if (!L.vals.empty()) links.push_back(std::move(L));
    }

    // leaf 값(노드 값) 알아내기
    // best의 마지막 요소는 leaf의 child-index
    // parent chain을 따라 leaf를 찾아 값 획득
    const Node* par = &root;
    for(size_t d=0; d+1<best.size(); ++d){
        par = &par->ch[ best[d] ];
    }
    int leaf_idx = best.back();
    int node_value = par->ch[leaf_idx].val;

    // 합성
    Eigen::MatrixXi IF = compose_IF(links, node_value);

    // 출력
    cout << "[size] " << IF.rows() << " x " << IF.cols() << "\n";
    cout << IF << "\n";

    return 0;
}

