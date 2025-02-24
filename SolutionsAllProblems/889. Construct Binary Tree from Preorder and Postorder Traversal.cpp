// problem : https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal/description/
// submission : https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal/submissions/
//     1554010206
// solution post : https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal/solutions/
//     6463253/c-modern-readable-code-beats-100-runtime-b0hq

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

// let 'n' be a length of each of the given arrays
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    using Node = TreeNode;
    using NodeP = Node *;
    NodeP constructFromPrePost(
        std::vector<int> const & preorder,
        std::vector<int> const & postorder
    ) const {
        auto preIndex{size_t{0}};
        auto postIndex{size_t{0}};
        return ConstructTree(preIndex, postIndex, preorder, postorder);
    }
private:
    NodeP ConstructTree(
        size_t & preIndex,
        size_t & postIndex,
        std::vector<int> const & preorder, 
        std::vector<int> const & postorder
    ) const {
        auto const root{new Node{preorder.at(preIndex++)}};
        if(root->val != postorder.at(postIndex)) {
            root->left = ConstructTree(preIndex, postIndex, preorder,
                postorder);
        } 
        if(root->val != postorder.at(postIndex)) {
            root->right = ConstructTree(preIndex, postIndex, preorder,
                postorder);
        }
        ++postIndex;
        return root;
    }
};
