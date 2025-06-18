// problem : https://leetcode.com/problems/equal-tree-partition/description/?envType=weekly-question&envId=2025-06-15
// submission : https://leetcode.com/problems/equal-tree-partition/submissions/1668306984
// solution post : https://leetcode.com/problems/equal-tree-partition/solutions/6858001/
//    c-modern-readable-code-beats-100-runtime-szmu

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
    using NodePT = TreeNode const * const;
// let 'n' be a count of nodes in the given tree
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    bool checkEqualTree(NodePT root_);
private:
    int DoSum(NodePT node_);
    std::vector<int> mSums;
};

bool Solution::checkEqualTree(NodePT root_) {
    namespace ranges = std::ranges;
    mSums.clear();
    auto sumTotal{DoSum(root_)};
    if(sumTotal % 2 == 0) {
        for(auto const sum:
            ranges::subrange(mSums.cbegin(), std::prev(mSums.cend()))
        ) {
            if(sum == sumTotal / 2) {
                return true;
            } 
        }
    }
    return false;
}

int Solution::DoSum(NodePT node_) {
    if(!node_) {
        return 0;
    }
    auto const sum{DoSum(node_->left) + DoSum(node_->right) + node_->val};
    mSums.emplace_back(sum);
    return mSums.at(mSums.size() - 1);
}
