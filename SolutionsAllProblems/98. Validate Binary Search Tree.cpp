// problem : https://leetcode.com/problems/validate-binary-search-tree/description
// submission : https://leetcode.com/problems/validate-binary-search-tree/submissions/1697594287
// solution post : https://leetcode.com/problems/validate-binary-search-tree/solutions/6957911/
//    c-modern-readable-code-beats-100-runtime-jnmo

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
    using NodeT = TreeNode const *;
// let 'n' be a nodes' count of the given tree
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    bool isValidBST(NodeT const root_);
private:
    [[nodiscard]]
    bool IsInorderTraversalValid(NodeT const nodeCurr_);
    NodeT mPrevNode{nullptr};
};

bool Solution::isValidBST(NodeT const root_) {
    auto const isValidBSTree{IsInorderTraversalValid(root_)};
    return isValidBSTree;
}

bool Solution::IsInorderTraversalValid(NodeT const nodeCurr_) {
    if(!nodeCurr_) {
        return true;
    }
    if(     !IsInorderTraversalValid(nodeCurr_->left)
        ||  (mPrevNode && nodeCurr_->val <= mPrevNode->val)
    ) {
        return false;
    }
    mPrevNode = nodeCurr_;
    return IsInorderTraversalValid(nodeCurr_->right);
}
