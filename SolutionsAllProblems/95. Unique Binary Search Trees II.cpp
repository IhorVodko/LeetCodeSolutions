// problem : https://leetcode.com/problems/unique-binary-search-trees-ii/description
// submission : https://leetcode.com/problems/unique-binary-search-trees-ii/submissions/1686229782
// solution post : https://leetcode.com/problems/unique-binary-search-trees-ii/solutions/6919750/
//    c-modern-readable-code-beats-100-runtime-gcyn

// #include <map>
// #include <ranges>
// #include <vector>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    using NodeT = TreeNode;
    using NodePT = NodeT *;
// let 'n' be a count of the nodes given
// time complexity O(4^n / n^1.5); this is a catalan number
// space complexity O(4^n / n^0.5)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    std::vector<NodePT> generateTrees(int const treeSz_) const;
private:
    [[nodiscard]]
    std::vector<NodePT> GenerateAllBSTsFromNodeValsRange(
        std::map<pair<int, int>, std::vector<NodePT>> & treeValsRangeToTrees_,
        int const nodeValFirst_,
        int const nodeValLast_
    ) const;
};

std::vector<Solution::NodePT> Solution::generateTrees(
    int const treeSz_
) const {
    auto treeValsRangeToTrees{
        std::map<std::pair<int , int>, std::vector<NodePT>>{}};
    auto const allBSTs{GenerateAllBSTsFromNodeValsRange(treeValsRangeToTrees,
        1, treeSz_)};
    return allBSTs;
}

std::vector<Solution::NodePT> Solution::GenerateAllBSTsFromNodeValsRange(
    std::map<pair<int, int>, std::vector<NodePT>> & treeValsRangeToTrees_,
    int const nodeValFirst_,
    int const nodeValLast_
) const {
    namespace views = std::views;
    auto allBSTs{std::vector<NodePT>{}};
    if(nodeValFirst_ > nodeValLast_) {
        allBSTs.emplace_back(nullptr);
        return allBSTs;
    }
    auto const nodeValsRange(std::pair(nodeValFirst_, nodeValLast_));
    if(auto const treeValsRangeToTreesIt{treeValsRangeToTrees_.find(
        nodeValsRange)};
        treeValsRangeToTreesIt != treeValsRangeToTrees_.end()
    ) {
        return treeValsRangeToTreesIt->second;
    }
    for(auto const nodeValCurr: views::iota(nodeValFirst_, nodeValLast_ + 1)) {
        auto const leftSubTress{GenerateAllBSTsFromNodeValsRange(
            treeValsRangeToTrees_, nodeValFirst_, nodeValCurr - 1)};
        auto const rightSubTrees{GenerateAllBSTsFromNodeValsRange(
            treeValsRangeToTrees_, nodeValCurr + 1, nodeValLast_)};
        for(auto const leftSubtree: leftSubTress) {
            for(auto const rightSubtree: rightSubTrees) {
                auto const root{new TreeNode{nodeValCurr, leftSubtree, rightSubtree}};
                allBSTs.emplace_back(root);
            }
        }
    }
    treeValsRangeToTrees_[nodeValsRange] = allBSTs;
    return treeValsRangeToTrees_.at(nodeValsRange);
 }
