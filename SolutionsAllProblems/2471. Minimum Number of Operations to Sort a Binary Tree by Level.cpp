// problem : https://leetcode.com/problems/minimum-number-of-operations-to-sort-a-binary-tree-by-level/description/
// submission : https://leetcode.com/problems/minimum-number-of-operations-to-sort-a-binary-tree-by-level/submissions/1486605681
// solution post : https://leetcode.com/problems/minimum-number-of-operations-to-sort-a-binary-tree-by-level/solutions/6179020/c-modern-readable-code-beats-98-runtime-hcsf6

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
class Solution {
public:
    // let 'n' be a number of nodes of the tree
    // time complexity O(n * log(n))
    // space complexity O(n)
    // runtime 31 ms, beats 97.95 %
    int minimumOperations(TreeNode const * const root) {
        auto queue{std::queue<TreeNode const *>{}};
        queue.push(root);
        auto size{size_t{0}};
        auto vals{std::vector<int>{}};
        auto node{static_cast<TreeNode const *>(nullptr)};
        auto ops{0};
        while(!queue.empty()) {
            size = queue.size();
            vals.clear();
            while(size-- > 0) {
                node = queue.front();
                queue.pop();
                if(node->left) {
                    vals.emplace_back(node->left->val);
                    queue.push(node->left);
                }
                if(node->right) {
                    vals.emplace_back(node->right->val);
                    queue.push(node->right); 
                }
            }
            ops += CountMinOps(vals);
        }
        return ops;
    }
private:
    int CountMinOps(auto & vals) {
            its.clear();
            auto ops{0};
            for(auto val{vals.begin()}, end(vals.end()); val < end; ++val) {
                its.emplace_back(val);
            }
            std::sort(its.begin(), its.end(),
                [] (auto const lhs, auto const rhs) { return *lhs < *rhs; });
            for(auto idx{size_t{0}}; idx < its.size(); ++idx) {
                if(its.at(idx) - vals.begin() == idx) {
                    continue;
                }
                ++ops;
                std::swap(its.at(idx), its.at(its.at(idx) - vals.begin()));
                --idx;
            }
        return ops;
    }
    std::vector<std::vector<int>::iterator> its;
};
