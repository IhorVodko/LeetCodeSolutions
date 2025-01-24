// problem : https://leetcode.com/problems/find-eventual-safe-states/description/
// submission : https://leetcode.com/problems/find-eventual-safe-states/submissions/1519081853
// solution post : https://leetcode.com/problems/find-eventual-safe-states/solutions/6324267/c-modern-readable-code-optimal-time-comp-2fv5

// #include <queue>
// #include <vector>

// let 'n' be a nodes count in the graph
// 'e' - edges count in the graph
// time complexity O(n + e)
// space complexity O(n + e)
// runtime 47 ms, beats 55.61 %
class Solution {
public:
    using D2 = std::vector<std::vector<int>>;
    std::vector<int> eventualSafeNodes(D2 const & graph ) const {
        auto const nodesCount{graph.size()};
        auto indegreeCounts(std::vector<size_t>(nodesCount, 0));
        auto adjMx{D2(nodesCount)};
        for(auto i{size_t{0}}; i < nodesCount; ++i) {
            for(auto const & node: graph.at(i)) {
                adjMx.at(node).emplace_back(i);
                ++indegreeCounts.at(i);
            }
        }
        auto nodesWithZeroIndegree{std::queue<size_t>{}};
        for(auto i{size_t{0}}; i < nodesCount; ++i) {
            if(!indegreeCounts.at(i)) {
                nodesWithZeroIndegree.push(i);
            }
        }
        auto isSafeNodes{std::vector<bool>(nodesCount, false)};
        auto node{-1};
        while(!nodesWithZeroIndegree.empty()) {
            node = nodesWithZeroIndegree.front();
            nodesWithZeroIndegree.pop();
            isSafeNodes.at(node) = true;
            for(auto const & neighbour: adjMx.at(node)) {
                --indegreeCounts.at(neighbour);
                if(!indegreeCounts.at(neighbour)) {
                    nodesWithZeroIndegree.push(neighbour);
                }
            }
        }
        auto safeNodes{std::vector<int>{}};
        for(auto i{size_t{0}}; i < nodesCount; ++i) {
            if(isSafeNodes.at(i)) {
                safeNodes.emplace_back(i);
            }
        }
        return safeNodes;
    }
};
