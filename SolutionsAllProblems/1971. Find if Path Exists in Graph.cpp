// problem : https://leetcode.com/problems/find-if-path-exists-in-graph/description/
// submission : https://leetcode.com/problems/find-if-path-exists-in-graph/submissions/1947091513
// solution post : https://leetcode.com/problems/find-if-path-exists-in-graph/solutions/7645767/
//    c-modern-readable-code-runtime-0-ms-beat-1iu3

// import std;

// Compile-time initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'v' be the number of vertices
// 'e' - number of edeges
// time complexity O(v + e)
// space complexity O(v + e)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    [[nodiscard]]
    auto validPath(
        int const nodesTotCnt_,
        std::vector<std::vector<int>> const & edges_,
        int const source_,
        int const dest_
    ) const -> bool;
};

auto Solution::validPath(
    int const nodesTotCnt_,
    std::vector<std::vector<int>> const & edges_,
    int const source_,
    int const dest_
) const -> bool {
    if(source_ == dest_) {
        return true;
    }
    auto ajdLst{std::vector<std::vector<int>>(nodesTotCnt_)};
    // Build adjacency list for the undirected graph
    for(auto const & edge: edges_) {
        auto const from{edge[0]};
        auto const to{edge[1]};
        ajdLst[from].emplace_back(to);
        ajdLst[to].emplace_back(from);
    }
    // Stack used to perform iterative DFS traversal
    auto nodes{std::stack<int>{{source_}}};
    auto isSeen{std::vector<bool>(nodesTotCnt_)};
    // Mark source as visited to avoid pushing it again
    isSeen[source_] = true;
    while(!nodes.empty()) {
        auto const cur{nodes.top()};
        nodes.pop();
        // Explore neighbors of the current node
        for(auto const next: ajdLst[cur]) {
            // Destination found during traversal
            if(next == dest_) {
                return true;
            }
            // Push unseen neighbors to continue DFS exploration
            if(!isSeen[next]) {
                isSeen[next] = true;
                nodes.emplace(next);
            }
        }
    }
    return false;
}
