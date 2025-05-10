// problem : https://leetcode.com/problems/closest-binary-search-tree-value/description/ 
// submission : https://leetcode.com/problems/closest-binary-search-tree-value/submissions/1629905038
// solution post : https://leetcode.com/problems/closest-binary-search-tree-value/solutions/6730095/
//    c-modern-readable-code-beats-100-by-cybe-foa5

// #include <algorithm>

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
    using NodePT = TreeNode const *;
// let 'n' be a hight of the given tree
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    int closestValue(
        NodePT const root_,
        double const target_
    ) const;
};

int Solution::closestValue(
    NodePT const root_,
    double const target_
) const {
    auto diffMin{std::numeric_limits<double>::max()};
    auto valMin{std::numeric_limits<int>::max()};
    for(auto node{root_}; node;
        node = target_ < node->val ? node->left : node->right
    ) {
        auto const diff{std::abs(node->val - target_)};
        if(diff < diffMin) {
            diffMin = diff;
            valMin = node->val;
        } else if(diff == diffMin) {
            valMin = std::min(valMin, node->val);
        } else if(diff == 0.) {
            return node->val;
        }
    }
    return valMin;
}
