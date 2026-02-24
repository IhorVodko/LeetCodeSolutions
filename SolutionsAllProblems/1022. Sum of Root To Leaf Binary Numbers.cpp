// problem : https://leetcode.com/problems/sum-of-root-to-leaf-binary-numbers/description
// submission : https://leetcode.com/problems/sum-of-root-to-leaf-binary-numbers/submissions/1929858669
// solution post : https://leetcode.com/problems/sum-of-root-to-leaf-binary-numbers/solutions/7606017/
//    c-modern-readable-code-beats-100-runtime-51wv

// import std;

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

// let 'n' be the number of nodes
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    using NodeCPC = TreeNode const * const;

    [[nodiscard]]
    auto sumRootToLeaf(NodeCPC root_) const -> int {
        if(!root_) {
            return 0;
        }
        // queue stores node together with the binary value formed along the path to it
        auto q{std::queue<std::pair<NodeCPC, unsigned>>{}};
        q.emplace(root_, 0);
        auto sum{0u};
        while(!q.empty()) {
            auto [curNode, curVal]{q.front()};
            q.pop();
            // extend current binary number with this node's bit
            curVal = (curVal << 1) | curNode->val;
            auto const lNode{curNode->left};
            auto const rNode{curNode->right};
            // if leaf node, accumulated value represents one root-to-leaf number
            if(!lNode && !rNode) {
                sum += curVal;
            } else {
                if(lNode) {
                    q.emplace(lNode, curVal);
                }
                if(rNode) {
                    q.emplace(rNode, curVal);
                }
            }
        }
        return static_cast<int>(sum);
    }
};
