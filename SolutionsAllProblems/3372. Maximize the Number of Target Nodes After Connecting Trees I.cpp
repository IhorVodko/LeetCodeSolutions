// problem : https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-i/description
// submission : https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-i/submissions/
//    1647141036
// solution post : https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-i/solutions/6790251/
//    c-modern-readable-code-beats-100-by-cybe-hmk1

// #include <algorithm>
// #include <vector>

class Solution {
public:
    using Arr2T = std::vector<std::vector<int>>;
// let 'n1' be a nodes count of the first tree
// 'n2' - of the second tree
// time complexity O(n1^2 + n2^2)
// space complexity O(n1 + n2)
// runtime 95 ms, beats 100.00 %
    std::vector<int> maxTargetNodes(
        Arr2T const & edges1_,
        Arr2T const & edges2_,
        int const distanceUpperLimit_
    ) const;
private:
    int DoDfs(
        int const nodeNext_,
        int const nodeCurr_,
        Arr2T const & adj,
        int const distanceUpperLimit_
    ) const;
    std::vector<int> ComputeTargetNodes(
        Arr2T const & edges,
        int const distanceUpperLimit_
    ) const;
};

std::vector<int> Solution::maxTargetNodes(
    Arr2T const & edges1_,
    Arr2T const & edges2_,
    int const distanceUpperLimit_
) const {
    auto const nodesCount1{edges1_.size() + 1};
    auto targetNodesTree1Counts{ComputeTargetNodes(edges1_,
        distanceUpperLimit_)};
    auto targetNodesTree2Counts{ComputeTargetNodes(edges2_,
        distanceUpperLimit_ - 1)};
    auto maxCount2{*std::max_element(targetNodesTree2Counts.begin(),
        targetNodesTree2Counts.end())};
    auto targetNodesTwoTreesCounts{std::vector<int>(nodesCount1, 0)};
    for(auto i{0}; i < nodesCount1; ++i) {
        targetNodesTwoTreesCounts.at(i) = targetNodesTree1Counts.at(i) +
            maxCount2;
    }
    return targetNodesTwoTreesCounts;
}

std::vector<int> Solution::ComputeTargetNodes(
    Arr2T const & edges,
    int const distanceUpperLimit_
) const {
    auto const nodesCount1{edges.size() + 1};
    auto adj{Arr2T(nodesCount1, std::vector<int>{})};
    for(auto const & edge: edges) {
        adj.at(edge.at(0)).emplace_back(edge.at(1));
        adj.at(edge.at(1)).emplace_back(edge.at(0));
    }
    auto targetNodesCounts{std::vector<int>(nodesCount1, 0)};
    for(auto i{0}; i < nodesCount1; ++i) {
        targetNodesCounts.at(i) = DoDfs(i, -1, adj, distanceUpperLimit_);
    }
    return targetNodesCounts;
}

int Solution::DoDfs(
    int const nodeNext_,
    int const nodeCurr_,
    Arr2T const & adj_,
    int const distanceUpperLimit_
) const {
    if(distanceUpperLimit_ < 0) {
        return 0;
    }
    auto distance{1};
    for(auto const node: adj_.at(nodeNext_)) {
        if(node != nodeCurr_) {
            distance += DoDfs(node, nodeNext_, adj_, distanceUpperLimit_ - 1);
        }
    }
    return distance;
}
