// problem : https://leetcode.com/problems/same-tree/
// submission : https://leetcode.com/problems/same-tree/submissions/1514477519
// solution post : https://leetcode.com/problems/same-tree/solutions/6306167/c-modern-readable-code-beats-100-runtime-7qq3

// #include <queue>

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

// let 'n' be a nodes count in the deepest given tree
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    bool isSameTree(
        TreeNode const * const treeA,
        TreeNode const * const treeB
    ) const {
        if(!treeA && !treeB) {
            return true;
        }
        if(!treeA || !treeB || treeA->val != treeB->val) { 
            return false;
        }
        auto qA{std::queue<TreeNode const *>{}}; 
        qA.push(treeA);
        auto qB{std::queue<TreeNode const *>{}}; 
        qB.push(treeB);
        auto nodeA{static_cast<TreeNode const *>(nullptr)};
        auto nodeB{static_cast<TreeNode const *>(nullptr)};
        while(!qA.empty()) {
            nodeA = qA.front();
            nodeB = qB.front();
            qA.pop();
            qB.pop();
            if(!isSameNode(qA, qB, nodeA->left, nodeB->left) ||
                !isSameNode(qA, qB, nodeA->right, nodeB->right)
            ) {
                return false;
            }
        }
        return true;
    }
private:
    bool isSameNode(
        std::queue<TreeNode const *> & qA,
        std::queue<TreeNode const *> & qB, 
        TreeNode const * const nodeA,
        TreeNode const * const nodeB
    ) const {
        if(nodeA && nodeB &&
            nodeA->val == nodeB->val
        ) {
            qA.push(nodeA);
            qB.push(nodeB);
        } else if(!nodeA && !nodeB) {
        } else {
            return false;
        }
        return true;
    }
};
