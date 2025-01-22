// problem : https://leetcode.com/problems/symmetric-tree/description/
// submission : https://leetcode.com/problems/symmetric-tree/submissions/1516737205
// solution post : https://leetcode.com/problems/symmetric-tree/solutions/6314718/c-modern-readable-code-beats-100-runtime-s027

// #include <deque>
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

// let 'n' be a total count of tree nodes
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    using NodeCP = TreeNode const *;
    bool isSymmetric(NodeCP const root) const {
        auto levelNodes{std::deque<NodeCP>{}};
        if(root->left) {
            levelNodes.push_back(root->left);
        }
        if(root->right) {
            levelNodes.push_back(root->right);
        }
        auto levelSz{0};
        auto nextLevelNodesLeft{std::vector<NodeCP>{}};
        auto nextLevelNodesRight{std::vector<NodeCP>{}};
        auto nodeLeft{static_cast<NodeCP>(nullptr)};
        auto nodeRight{static_cast<NodeCP>(nullptr)};
        while(!levelNodes.empty()) {
            levelSz = levelNodes.size();
            if(levelSz % 2) {
                return false;
            }
            nextLevelNodesLeft.clear();
            nextLevelNodesRight.clear();
            while((levelSz -= 2) >= 0) {
                nodeLeft = levelNodes.front();
                levelNodes.pop_front();
                nodeRight = levelNodes.back();
                levelNodes.pop_back();
                if(!IsSymmetricNodes(nodeLeft, nodeRight)) {
                    return false;
                }
                if(nodeLeft->left) {
                    nextLevelNodesLeft.emplace_back(nodeLeft->left);
                }
                if(nodeLeft->right) {
                    nextLevelNodesLeft.emplace_back(nodeLeft->right);
                }
                if(nodeRight->right) {
                    nextLevelNodesRight.emplace_back(nodeRight->right);
                }
                if(nodeRight->left) {
                    nextLevelNodesRight.emplace_back(nodeRight->left);
                }
            }
            InsertNextLevelNodes(levelNodes, nextLevelNodesLeft,
                nextLevelNodesRight);
        }
        return true;
    }
private:
    bool IsSymmetricNodes(
        NodeCP const nodeLeft,
        NodeCP const nodeRight 
    ) const {
        return nodeLeft->val == nodeRight->val &&
            (nodeLeft->left == nodeRight->right ||
                (nodeLeft->left && nodeRight->right)) && 
            (nodeLeft->right == nodeRight->left ||
                (nodeLeft->right && nodeRight->left));
    } 
    void InsertNextLevelNodes(
        std::deque<NodeCP> & levelNodes,
        std::vector<NodeCP> const & nextLevelNodesLeft,
        std::vector<NodeCP> const & nextLevelNodesRight
    ) const {
        for(auto const node: nextLevelNodesLeft) {
            levelNodes.push_back(node);
        }
        for(auto node{nextLevelNodesRight.crbegin()},
            end{nextLevelNodesRight.crend()}; node < end; ++node
        ) {
            levelNodes.push_back(*node);    
        } 
    }
};
