// problem : https://leetcode.com/problems/jump-game-iv/description
// submission : https://leetcode.com/problems/jump-game-iv/submissions/2006655240
// solution post : https://leetcode.com/problems/jump-game-iv/solutions/8270927/c-modern-readable-code-beats-9953-runtim-f5j7

// Approach : Breadth-First Search (BFS) / Shortest Path in Unweighted Graph
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the count of numbers
// complexity :  O(n)
// complexity : O(n)

// import std;

namespace {

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    auto minJumps(std::vector<int> const & nums_) const -> int;

private:
    // Constants representing the graph node traversal states.
    static auto constexpr kNotVisited{-1};
    static auto constexpr kNotReachable{-1};
};

auto Solution::minJumps(std::vector<int> const & nums_) const -> int {
    namespace vs = std::views;

    auto const numsSz{std::ssize(nums_)};
    // Fast paths for small arrays to avoid graph construction overhead.
    if(numsSz == 1) {
        return 0;
    } else if(numsSz == 2) {
        return 1;
    } else if(numsSz == 3) {
        return nums_.front() == nums_.back() ? 1 : 2;
    }

    // Build an adjacency list mapping values to indices for teleportation jumps.
    auto numToIdxs{std::unordered_map<int, std::vector<int>>{}};
    numToIdxs.reserve(numsSz * 2);
    for(auto const j: vs::iota(0, numsSz)) {
        numToIdxs[nums_[j]].emplace_back(j);
    }

    // BFS initialization: track shortest path to each node to prevent cycles.
    auto distances{std::vector<int>(numsSz, kNotVisited)};
    distances.front() = 0;
    auto qIdxs{std::queue<int>{}};
    qIdxs.emplace(0);
    auto const targetIdx{numsSz - 1};

    // Explore the graph level-by-level to guarantee the shortest path is found.
    while(!qIdxs.empty()) {
        auto const currIdx{qIdxs.front()};
        qIdxs.pop();
        auto const currDist{distances[currIdx]};

        // Evaluate the adjacent right node simulating a forward step.
        auto nextIdx{currIdx + 1};
        if(nextIdx < numsSz && distances[nextIdx] == kNotVisited) {
            if(nextIdx == targetIdx) {
                return currDist + 1;
            }
            distances[nextIdx] = currDist + 1;
            qIdxs.emplace(nextIdx);
        }

        // Evaluate the adjacent left node simulating a backward step.
        auto const prevIdx{currIdx - 1};
        if(prevIdx >= 0 && distances[prevIdx] == kNotVisited) {
            if(prevIdx == targetIdx) {
                return currDist + 1;
            }
            distances[prevIdx] = currDist + 1;
            qIdxs.emplace(prevIdx);
        }

        // Evaluate all teleportation nodes sharing the exact same integer value.
        if(auto const numToIdxsIt{numToIdxs.find(nums_[currIdx])};
            numToIdxsIt != numToIdxs.end()
        ) {
            for(auto const nextIdx: numToIdxsIt->second) {
                if(nextIdx != currIdx && distances[nextIdx] == kNotVisited) {
                    if(nextIdx == targetIdx) {
                        return currDist + 1;
                    }
                    distances[nextIdx] = currDist + 1;
                    qIdxs.emplace(nextIdx);
                } 
            }
            // Prune the value group to prevent redundant evaluations and maintain O(N).
            numToIdxs.erase(numToIdxsIt);
        }
    }

    // Fallback if the target index is completely disconnected from the start.
    return kNotReachable;
}
