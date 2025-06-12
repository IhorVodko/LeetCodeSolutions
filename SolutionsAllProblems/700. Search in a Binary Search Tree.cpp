// problem : https://leetcode.com/problems/search-in-a-binary-search-tree/description/
// submission : https://leetcode.com/problems/search-in-a-binary-search-tree/submissions/1662061508
// solution post : https://leetcode.com/problems/search-in-a-binary-search-tree/solutions/6836866/
//    c-modern-readable-code-beats-100-runtime-mvlx

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
    using NodeCPC = TreeNode const * const;
// let 'n' be a count of the tree nodes given
// time complexity O(log2(n))
// space complexity O(log2(n)
// runtime 0 ms, beats 100.00 %

    TreeNode * searchBST(
        NodeCPC root_,
        int const valTarget_
    ) const;
};

TreeNode * Solution::searchBST(
    NodeCPC root_,
    int const valTarget_
) const {
    if(!root_ || valTarget_ == root_->val) {
        return const_cast<TreeNode *>(root_);
    }
    auto const nodeNext{valTarget_ < root_->val ? root_->left : root_->right};
    return searchBST(nodeNext, valTarget_);
}
