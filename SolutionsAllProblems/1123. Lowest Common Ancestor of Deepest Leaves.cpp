// problem : https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/description/
// submission : https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/submissions/1596661068
// solution post : https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/solutions/6615294/
//     c-modern-readable-code-optimal-time-comp-iv0m

// #include <queue>
// #include <vector>
// #include <unordered_map>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), 
            right(right) {}
 * };
 */

// let 'n' be a given tree's nodes count
// time complexity O(n)
// space complexity O(n)
// runtime 2 ms, beats 21.54 %
class Solution {
public:
    using NodeP = TreeNode *;
    NodeP lcaDeepestLeaves(NodeP root_) const {
        if(!root_->left && !root_->right) {
            return root_;
        }
        auto childToParent{std::unordered_map<NodeP, NodeP>{}};
        auto nodesQ{std::queue<NodeP>{{root_}}};
        auto deepestLevelNodes{std::vector<NodeP>{}};
        while(!nodesQ.empty()) {
            auto levelSz{nodesQ.size()};
            deepestLevelNodes.clear();
            while(levelSz-- > 0) {
                auto const node{nodesQ.front()};
                deepestLevelNodes.emplace_back(node);
                nodesQ.pop(); 
                if(node->left) {
                    childToParent[node->left] = node;
                    nodesQ.emplace(node->left);
                }
                if(node->right) {
                    childToParent[node->right] = node;
                    nodesQ.emplace(node->right);
                }
            }
        }
        if(deepestLevelNodes.size() == 1) {
            return deepestLevelNodes.front();
        }
        nodesQ = {deepestLevelNodes.begin(), deepestLevelNodes.end()};
        auto lcaNode{childToParent.at(nodesQ.front())};
        while(!nodesQ.empty()) {
            auto node{nodesQ.front()};
            if(lcaNode != childToParent.at(node)) {
                nodesQ.emplace(lcaNode);
                lcaNode = childToParent.at(node);
            }
            nodesQ.pop();
        }
        return lcaNode; 
    }
};
