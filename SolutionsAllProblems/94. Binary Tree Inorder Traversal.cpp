// problem :  https://leetcode.com/problems/binary-tree-inorder-traversal/description/
// submission : https://leetcode.com/problems/binary-tree-inorder-traversal/submissions/1457601032
// solution post: https://leetcode.com/problems/binary-tree-inorder-traversal/solutions/6063548/c-modern-readable-code-beats-100-runtime

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
    // let 'n' be a number of tree nodes
    // time complexity O(n)
    // space complexity O(n)
    // runtime 0 ms, beats 100 %
    // memory 10.01 mb, beats 74.39 %
    std::vector<int> inorderTraversal(TreeNode const * root) const {
        if(!root){
            return {};
        }
        auto inorderNodes{std::vector<int>{}};
        auto stack{std::stack<TreeNode const *>{}};
        auto temp{root}; 
        while(temp || !stack.empty()){
            while(temp){
                stack.push(temp);
                temp = temp->left;        
            }
            temp = stack.top();
            stack.pop();
            inorderNodes.emplace_back(temp->val);
            temp = temp->right;
        }
        return inorderNodes;
    }
};
