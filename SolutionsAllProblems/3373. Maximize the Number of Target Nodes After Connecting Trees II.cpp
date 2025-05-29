// problem : https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-ii/description/
// submission : https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-ii/submissions/
//    1648212825
// solution post : https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-ii/solutions/
//    6793642/c-modern-readable-code-optimal-time-comp-qxix

// #include <algorithm>
// #include <vector>
// #include <utility>

class Solution {
public:
    using Arr2T = std::vector<std::vector<int>>;
// let 'e1' be a length of the first given array of edges
// 'e2' - second given array of edges
// time complexity O(e1 + e2)
// space complexity O(e1 + e2)
// runtime 285 ms, beats 87.76 %
    std::vector<int> maxTargetNodes(
        Arr2T const & edges1_,
        Arr2T const & edges2_
    ) const;
private:
    int DoDfs(
        int const nodeCurr_,
        int const nodeParent_,
        int const distance_,
        Arr2T const & children,
        std::vector<int> & colors_
    ) const;
    std::pair<int, int> ComputeNodesColors(
        Arr2T const & edges_,
        std::vector<int> & colors_
    ) const;
};

std::vector<int> Solution::maxTargetNodes(
    Arr2T const & edges1_,
    Arr2T const & edges2_
) const {
    auto const nodesCoun1{edges1_.size() + 1};
    auto const nodesCoun2{edges2_.size() + 2};
    auto nodesColors1{std::vector<int>(nodesCoun1, 0)};
    auto nodesColors2{std::vector<int>(nodesCoun2, 0)};
    auto evenAndUnevenDistancesCounts1{
        ComputeNodesColors(edges1_, nodesColors1)};
    auto evenAndUnevenDistancesCounts2{
        ComputeNodesColors(edges2_, nodesColors2)};
    auto targetNodesCounts{std::vector<int>(nodesCoun1, 0)};
    for(auto i{0}; i < nodesCoun1; ++i) {
        if(nodesColors1.at(i) == 0) {
            targetNodesCounts.at(i) += evenAndUnevenDistancesCounts1.first;
        } else {
            targetNodesCounts.at(i) += evenAndUnevenDistancesCounts1.second;
        }
        targetNodesCounts.at(i) +=
            std::max(evenAndUnevenDistancesCounts2.first,
                evenAndUnevenDistancesCounts2.second);
    }
    return targetNodesCounts;
}

std::pair<int, int> Solution::ComputeNodesColors(
    Arr2T const & edges_,
    std::vector<int> & colors_
) const {
    auto const nodesCount{edges_.size() + 1};
    auto adjMx{Arr2T(nodesCount, std::vector<int>{})};
    for(auto const & edge: edges_) {
        adjMx.at(edge.at(0)).emplace_back(edge.at(1));
        adjMx.at(edge.at(1)).emplace_back(edge.at(0));
    }
    auto const evenDistancesCount{DoDfs(0, -1, 0, adjMx, colors_)};
    auto const unevenDistancesCount{nodesCount - evenDistancesCount};
    return {evenDistancesCount, static_cast<int>(unevenDistancesCount)};
}

int Solution::DoDfs(
        int const nodeCurr_,
        int const nodeParent_,
        int const distance_,
        Arr2T const & adjMx_,
        std::vector<int> & colors_
) const {
    auto distancesCount{1 - distance_ % 2};
    colors_.at(nodeCurr_) = distance_ % 2;
    for(auto const nodeChild: adjMx_.at(nodeCurr_)) {
        if(nodeChild == nodeParent_) {
            continue;
        }
        distancesCount +=
            DoDfs(nodeChild, nodeCurr_, distance_ + 1, adjMx_, colors_);
    }
    return distancesCount;
}
