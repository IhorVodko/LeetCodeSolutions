// problem : https://leetcode.com/problems/network-recovery-pathways/description
// submission : https://leetcode.com/problems/network-recovery-pathways/submissions/2055041690
// solution post : https://leetcode.com/problems/network-recovery-pathways/solutions/8374452/modern-readable-code-optimal-time-comple-u70u

// Approach : Binary Search with Topological Sort (Dynamic Programming on DAG)
// Runtime : 102 ms, beats 94.86 %

// Complexity
// let 'V' be the number of nodes
// 'E' - nubmer of edges 
// 'W' - number of distinct edge costs
// Time :  O(E * log(E) + (V + E) * log(W))
// Space : O(V + E)

// import std;

class Solution final {
public:
    using llLim = std::numeric_limits<long long>;

    [[nodiscard]]
    static auto findMaxPathScore(
        std::vector<std::vector<int>> const & edgeAndCostArr_,
        std::vector<bool> const & isNodeOnlineArr_,
        long long const pathCostUpLim_
    ) -> int;
};

auto Solution::findMaxPathScore(
    std::vector<std::vector<int>> const & edgeAndCostArr_,
    std::vector<bool> const & isNodeOnlineArr_,
    long long const pathCostUpLim_
) -> int {
    namespace rs = std::ranges;
    namespace vs = std::views;

    auto const nodesTot{std::ssize(isNodeOnlineArr_)};
    auto const destNode{nodesTot - 1};

    // Terminate early if endpoints are offline or no edges exist
    if(edgeAndCostArr_.empty() || !isNodeOnlineArr_[0] || !isNodeOnlineArr_[destNode]) {
        return -1;
    }

    auto adj{std::vector<std::vector<std::pair<int, int>>>(nodesTot)};
    auto weights{std::vector<int>{}};
    weights.reserve(edgeAndCostArr_.size());
    auto inDegree{std::vector<int>(nodesTot)};

    // Construct graph strictly for online nodes and collect weights
    for(auto const & edgeAndCost: edgeAndCostArr_) {
        auto const u{edgeAndCost[0]};
        auto const v{edgeAndCost[1]};
        auto const w{edgeAndCost[2]};
        if(isNodeOnlineArr_[u] && isNodeOnlineArr_[v]) {
            adj[u].emplace_back(v, w);
            weights.emplace_back(w);
            ++inDegree[v];
        }
    }

    // Sort and erase duplicates to form our binary search space
    rs::sort(weights);
    auto const duplicates{rs::unique(weights)};
    weights.erase(duplicates.begin(), duplicates.end());

    // Kahn's algorithm for topological sorting in-place
    auto topoOrd{std::vector<int>{}};
    topoOrd.reserve(nodesTot);

    // Seed topological sort with nodes having zero dependencies
    for(auto const j: vs::iota(0, nodesTot)) {
        if(inDegree[j] == 0) {
            topoOrd.emplace_back(j);
        }
    }

    for(auto j{0}; j < topoOrd.size(); ++j) {
        auto const u{topoOrd[j]};
        for(auto const [v, _]: adj[u]) {
            if(--inDegree[v] == 0) {
                topoOrd.emplace_back(v);
            }
        }
    }

    // Predicate evaluating if destination is reachable under constraints
    auto const canReachWithScore{[&] (auto const minScore_) {
        auto dist{std::vector<long long>(nodesTot, llLim::max())};
        dist[0] = 0;

        // Compute shortest paths relaxing only edges meeting score threshold
        for(auto const u: topoOrd) {
            if(dist[u] == llLim::max()) {
                continue;
            }

            auto validEdges{
                adj[u] |
                vs::filter([=] (auto const & nodeAndWeight_) {
                    return minScore_ <= nodeAndWeight_.second;
                })
            };

            for(auto const [v, w]: validEdges) {
                dist[v] = std::min(dist[v], dist[u] + w);
            }
        }

        return dist[destNode] <= pathCostUpLim_;
    }};

    // Binary search for the maximum bottleneck score
    auto const firstInvalidWeightIt{rs::partition_point(weights, canReachWithScore)};

    return 
        firstInvalidWeightIt == weights.begin() ? -1 : *std::prev(firstInvalidWeightIt);
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
