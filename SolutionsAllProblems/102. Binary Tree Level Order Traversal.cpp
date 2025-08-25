// problem : https://leetcode.com/problems/binary-tree-level-order-traversal/description/
// submission : https://leetcode.com/problems/binary-tree-level-order-traversal/submissions/1747748518
// solution post : https://leetcode.com/problems/binary-tree-level-order-traversal/solutions/7120950/
//    c-modern-readable-code-beats-100-runtime-ui9t

// #include <queue>
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
    using nodeValT = int;
    using levelT = std::vector<nodeValT>;
    using levelsT = std::vector<levelT>;
    using nodeCP = TreeNode const *;
// let 'n' be a nodes' count of the given tree
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    levelsT levelOrder(nodeCP const root_) const;
};

Solution::levelsT Solution::levelOrder(nodeCP const root_) const {
    if(!root_) {
        return {};
    }
    auto levels{levelsT{}}; 
    auto nodesQ{std::queue<nodeCP>{}}; 
    nodesQ.emplace(root_);
    while(!nodesQ.empty()) {
        auto levelSz{std::ssize(nodesQ)};
        auto level{levelT{}};
        while(levelSz-- > 0) {
            auto const node{nodesQ.front()};
            nodesQ.pop();
            level.emplace_back(node->val);
            if(node->left) {
                nodesQ.emplace(node->left);
            }
            if(node->right) {
                nodesQ.emplace(node->right);
            }
        }
        levels.emplace_back(std::move(level));
    }
    return levels;
}
