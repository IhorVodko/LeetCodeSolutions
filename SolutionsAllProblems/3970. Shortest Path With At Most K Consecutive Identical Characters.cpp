// problem : https://leetcode.com/problems/shortest-path-with-at-most-k-consecutive-identical-characters/description
// submission : https://leetcode.com/problems/shortest-path-with-at-most-k-consecutive-identical-characters/submissions/2185772527
// solution post : https://leetcode.com/problems/shortest-path-with-at-most-k-consecutive-identical-characters/solutions/8595327/
//    simplanation-simple-explanation-by-cyber-jxeu

// Approach : State-Space Modified Dijkstra Search
// Runtime : 111 ms, beats 97.48 %

// Complexity analysis
// let 'v' be the number of edges
// 'e' - number of edges
// 'k' - the maximum allowed length of consecutively identical characters limit
// Time :  O(k * (v + e) * log(v * k))
// Space : O(v + e * k)

// import std;

// #include <algorithm>
// #include <array>
// #include <functional>
// #include <ios>
// #include <iostream>
// #include <queue>
// #include <ranges>
// #include <string_view>
// #include <utility>
// #include <vector>

namespace rs = std::ranges;
namespace vs = std::views;

template <typename T_>
using vector2dT =   std::vector<std::vector<T_>>;
using pathStateT =  std::array<int, 3>; 

namespace {

auto constexpr kNoValidPath {-1};
auto constexpr kFromNodeIdx {0uz};
auto constexpr kToNodeIdx   {1uz};
auto constexpr kWIdx        {2uz};

// Helper function inserting directed edge mapping into adjacency list
auto const insertEdge{[] [[nodiscard]] (
    auto            adjLst_,
    auto const &    eAndW_
)
static
{
    adjLst_[eAndW_[kFromNodeIdx]].emplace_back(
            eAndW_[kToNodeIdx], eAndW_[kWIdx]
    );

    return adjLst_;
}};

[[maybe_unused]]
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace 

class Solution final {
public:     
    [[nodiscard]]
    static auto shortestPath(
        int                 const   nodesTot_,
        vector2dT<int>      const & eAndWLst_,
        std::string_view    const   edgeLables_,
        int                 const   streakLenUpLim_
    )
    -> int; 
};

auto Solution::shortestPath(
    int                 const   nodesTot_,
    vector2dT<int>      const & eAndWLst_,
    std::string_view    const   edgeLables_,
    int                 const   streakLenUpLim_
)
-> int
{
    // 1. Build adjacency list representation from graph edges
    auto const adjLst{rs::fold_left(
        eAndWLst_,
        vector2dT<std::pair<int, int>>(nodesTot_),
        insertEdge
    )};

    // Map minimal streak length allowed per node for pruning
    auto minStreakLenPerNode{std::vector<int>(nodesTot_, streakLenUpLim_ + 1)};

    // 2. Initialize Dijkstra's state traversal ordered by cost
    auto pQ{std::priority_queue<pathStateT, std::vector<pathStateT>, std::greater<>>{}};
    pQ.push({0, 0, 1});

    // 3. Process minimal cost path states from priority queue
    while(!pQ.empty()) {
        auto const [currCost, currNode, currStreakLen]{pQ.top()};
        pQ.pop();

        // 4. Prune state if it does not strictly decrease the streak
        if(currStreakLen >= minStreakLenPerNode[currNode]) {
            continue;
        }

        minStreakLenPerNode[currNode] = currStreakLen;

        // 5. Terminate early upon reaching the destination node
        if(currNode + 1 == nodesTot_) {
            return currCost;
        }

        // 6. Relax outgoing edges to evaluate adjacent path states
        for(auto const & nextNodeAndW: adjLst[currNode]) {
            auto const [nextNode, nextW]{nextNodeAndW};
            // Calculate new streak length by checking character labels
            auto const nextPathStreakLen{
                edgeLables_[nextNode] == edgeLables_[currNode] ? currStreakLen + 1 : 1
            };

            // Queue valid state if it improves the historical node streak
            if(nextPathStreakLen < minStreakLenPerNode[nextNode]) {
                pQ.push({currCost + nextW, nextNode, nextPathStreakLen});
            }
        }
    }
    
    return kNoValidPath;
}
