// problem : https://leetcode.com/problems/reverse-odd-levels-of-binary-tree/description/
// submission : https://leetcode.com/problems/reverse-odd-levels-of-binary-tree/submissions/1484022938
// solution post : https://leetcode.com/problems/reverse-odd-levels-of-binary-tree/solutions/6168809/c-modern-readable-code-beats-100-runtime-4aez

// #include <algorithm>
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
// let 'n' be number of nodes in a tree
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    TreeNode * reverseOddLevels(TreeNode * root) {
        if(!root->left) {
            return root;
        }
        size_t level{0};
        clear(levelNodes);
        levelNodes.push(root);  
        while(!levelNodes.empty()) {
            processLevel();
            if(level++ % 2 == 1) {
                reverse(thisLevelNodes.begin(), thisLevelNodes.end()); 
            }
        }
        return root;
    }
private:
    void reverse(
        std::vector<TreeNode *>::iterator  first,
        std::vector<TreeNode *>::iterator last
    ) {
        while(first < --last) {
            std::swap((*first++)->val, (*last)->val);
        }
    }
    void clear(std::queue<TreeNode *> & nodes) {
        auto emptyNodes{std::queue<TreeNode * >{}};
        nodes.swap(emptyNodes);
    }
    void processLevel() {
        thisLevelNodes.clear();
        while(!levelNodes.empty()) {
            thisLevelNodes.emplace_back(levelNodes.front());
            levelNodes.pop();
        }
        for(auto node: thisLevelNodes) {
            if(!node->left) {
                return;
            }
            levelNodes.push(node->left);
            levelNodes.push(node->right); 
        }
    }
    std::vector<TreeNode *> thisLevelNodes;
    std::queue<TreeNode *> levelNodes;
};
