// problem : https://leetcode.com/problems/path-existence-queries-in-a-graph-i/description
// submission : https://leetcode.com/problems/path-existence-queries-in-a-graph-i/submissions/2061895371
// solution post : https://leetcode.com/problems/path-existence-queries-in-a-graph-i/solutions/8386637/
//    modern-readable-code-optimal-time-comple-4cvy

// Approach : Connected Components via Prefix Sums
// Runtime : 3 ms, beats 96.99 %

// Complexity analysis
// let 'n' be the number of nodes
// 'm' - number of queries
// Time :  O(n + m)
// Space : O(n), auxiliary space

// import std;

class Solution final {
public:
    [[nodiscard]]
    static auto pathExistenceQueries(
        int const nodesTot_,
        std::vector<int> const & nodeVals_,
        int const diffUpLim_,
        std::vector<std::vector<int>> const & pathQueries_
    ) -> std::vector<bool>;
};

auto Solution::pathExistenceQueries(
    int const nodesTot_,
    std::vector<int> const & nodeVals_,
    int const diffUpLim_,
    std::vector<std::vector<int>> const & pathQueries_
) -> std::vector<bool> {
    namespace vs = std::views;
    namespace rs = std::ranges;

    // Single-node graphs are trivially fully connected
    if(nodesTot_ == 1) {
        return std::vector(pathQueries_.size(), true);
    }

    // Stores a unique component identifier for each node based on its sorted index
    auto setIdPerNode{std::vector(nodesTot_, 0)};

    // Map adjacent node values to a binary boundary flag (1 if edge is broken, 0 if
    // connected)
    auto setBoundaries{
        nodeVals_ |
        vs::adjacent_transform<2>([=] (auto const num1_, auto const num2_) {
            return num2_ - num1_ > diffUpLim_ ? 1 : 0;
    })};
    // Group nodes into components via prefix sums of boundaries
    std::inclusive_scan(setBoundaries.begin(), setBoundaries.end(),
        setIdPerNode.begin() + 1);

    // Queries are valid if both nodes share the same component ID
    return 
        pathQueries_ |
        vs::transform([&] (auto const & query_) {
                return setIdPerNode[query_[0]] == setIdPerNode[query_[1]];
        }) |
        rs::to<std::vector>();
}

namespace {

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace
