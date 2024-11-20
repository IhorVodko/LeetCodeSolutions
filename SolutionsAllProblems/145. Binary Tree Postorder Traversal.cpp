// problem : https://leetcode.com/problems/binary-tree-postorder-traversal/description/
// submission : https://leetcode.com/problems/binary-tree-postorder-traversal/submissions/1458573902
// solution post: https://leetcode.com/problems/binary-tree-postorder-traversal/solutions/6066728/c-modern-readable-code-beats-100-runtime

// #include <stack>
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
    // let 'n' be a number of nodes in the tree
    // time complexity O(n)
    // space complexity O(n)
    // Runtime 0 ms, beats 100 %
    // Memory 10.02 mb, beats 79.98 %
    std::vector<int> postorderTraversal(TreeNode const * root) const {
        if(!root){
            return {};
        }
        auto stack{std::stack<TreeNode const *>{}};
        auto postorderVals{std::vector<int>{}};
        auto prevNode{static_cast<TreeNode const * >(nullptr)};
        while(root || !stack.empty()){
            if(root){
                stack.push(root);
                root = root->left;
                continue;
            }
            if(!root){
                root = stack.top();
                if(root->right && root->right != prevNode){
                    root = root->right;
                    continue;
                }
                if(!root->right || root->right == prevNode){
                    postorderVals.emplace_back(root->val);
                    stack.pop();
                    prevNode = root;
                    root = nullptr;
                }
            }
        }
        return postorderVals;
    }
};
