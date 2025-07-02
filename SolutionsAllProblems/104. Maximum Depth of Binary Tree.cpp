// problem : https://leetcode.com/problems/maximum-depth-of-binary-tree/description/
// submission : https://leetcode.com/problems/maximum-depth-of-binary-tree/submissions/1683883509
// solution post : https://leetcode.com/problems/maximum-depth-of-binary-tree/solutions/6911303/
//    c-modern-readable-code-beats-100-runtime-nnkp

// #include <algorithm>

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
    using NodeCPT = TreeNode const *;
// let 'n' be a size of the given tree
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    int maxDepth(NodeCPT const root_);
};

int Solution::maxDepth(NodeCPT const root_) {
    if(!root_) {
        return 0;
    }
    auto const depthMaxLeft{1 + maxDepth(root_->left)};
    auto const depthMaxRight{1 + maxDepth(root_->right)};
    auto const depthMax{std::max(depthMaxLeft, depthMaxRight)};
    return depthMax;
}
