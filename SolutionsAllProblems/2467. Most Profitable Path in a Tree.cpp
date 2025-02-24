// problem : https://leetcode.com/problems/most-profitable-path-in-a-tree/description/
// submission : https://leetcode.com/problems/most-profitable-path-in-a-tree/submissions/1554064317
// solution post : https://leetcode.com/problems/most-profitable-path-in-a-tree/solutions/6463403/
//     c-modern-readable-code-optimal-time-comp-ujij

// #include <algorithm>
// #include <limits>
// #include <vector>

// let 'n' be a nodes count in the given tree
// time complexity O(n)
// space complexity O(n)
// runtime 99 ms, beats 81.80 %
class Solution {
public:
    int mostProfitablePath(
        std::vector<vector<int>> const & edges,
        int const bob,
        std::vector<int> const & amount
    ) {
        nodesCount = amount.size();
        tree.resize(nodesCount, {});
        for(auto const & edge: edges) {
            tree.at(edge.at(0)).emplace_back(edge.at(1));
            tree.at(edge.at(1)).emplace_back(edge.at(0));
        }
        distancesFromBob.resize(nodesCount);
        return FindPathes(0, 0, 0, bob, amount);
    }
    Solution():
        nodesCount{0}
    {}
private:
    int FindPathes(
        int const sourceNode,
        int const parentNode,
        int const time,
        int const bob,
        std::vector<int> const & amount
    ) {
        auto maxIncome{0};
        auto maxChild{std::numeric_limits<int>::min()};
        distancesFromBob.at(sourceNode) = sourceNode == bob ? 0 : nodesCount;

        for(auto const adjacentNode: tree.at(sourceNode)) {
            if(adjacentNode != parentNode) {
                maxChild = std::max(maxChild, FindPathes(adjacentNode,
                    sourceNode, time + 1, bob, amount));
                distancesFromBob.at(sourceNode) = std::min(
                    distancesFromBob.at(sourceNode),
                    distancesFromBob.at(adjacentNode) + 1);
            }
        }
        if(distancesFromBob.at(sourceNode) > time) {
            maxIncome += amount.at(sourceNode);
        } else if(distancesFromBob.at(sourceNode) == time) {
            maxIncome += amount.at(sourceNode) / 2;
        }
        return maxIncome += maxChild == std::numeric_limits<int>::min() ? 0 :
            maxChild; 

    }
    size_t nodesCount;
    std::vector<std::vector<int>> tree;
    std::vector<int> distancesFromBob;
};
