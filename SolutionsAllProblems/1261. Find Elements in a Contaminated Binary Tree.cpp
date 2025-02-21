// problem : https://leetcode.com/problems/find-elements-in-a-contaminated-binary-tree/description/
// submission : https://leetcode.com/problems/find-elements-in-a-contaminated-binary-tree/submissions/1550866126
// solution post : https://leetcode.com/problems/find-elements-in-a-contaminated-binary-tree/solutions/6451655/
//     c-modern-readable-code-beats-100-runtime-fgwh

// #include <unordered_set>

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

// let 'n' be nodes count in the given tree
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class FindElements {
public:
    using NodeP = TreeNode *;
    // time complexity O(1)
    // space complexity O(1)
    bool find(int const target) const {
        return vals.contains(target);
    }
    // time complexity O(n)
    // space complexity O(n)
    FindElements(NodeP const root) {
       RecoverTree(root); 
    }
private:
    // time complexity O(n)
    // space complexity O(n)
    void RecoverTree(NodeP const root) {
        root->val = 0;
        auto nodes{std::queue<NodeP>{}};
        nodes.push(root);
        while(!nodes.empty()) {
            auto const nodeCurr{nodes.front()};
            nodes.pop();
            vals.emplace(nodeCurr->val);
            if(nodeCurr->left) {
                nodeCurr->left->val = 2 * nodeCurr->val + 1;
                nodes.push(nodeCurr->left);
            }
            if(nodeCurr->right) {
                nodeCurr->right->val = 2 * nodeCurr->val + 2;
                nodes.push(nodeCurr->right);
            }
        }
    }
    std::unordered_set<int> vals;
};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */
