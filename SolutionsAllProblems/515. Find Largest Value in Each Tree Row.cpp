// problem : https://leetcode.com/problems/find-largest-value-in-each-tree-row/description/
// submission : https://leetcode.com/problems/find-largest-value-in-each-tree-row/submissions/1488163459
// solution post : https://leetcode.com/problems/find-largest-value-in-each-tree-row/solutions/6612615/
//     c-modern-readable-code-beats-100-runtime-xbby

// #include <algorithm>
// #include <vector>

// let 'n' be a number of node in the Tree
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    std::vector<int> largestValues(TreeNode const * const root) {
        maxValsInEachRow.clear();
        DoDfs(startDepth, root); 
        return maxValsInEachRow;
    }
private:
    void DoDfs(
        size_t depth,
        TreeNode const * const node
    ) {
        if(!node) {
            return;
        }
        if(depth >= maxValsInEachRow.size()) {
            maxValsInEachRow.emplace_back(node->val);
        } else {
            maxValsInEachRow.at(depth) = std::max(
                maxValsInEachRow.at(depth), node->val);
        }
        DoDfs(++depth, node->left);
        DoDfs(depth, node->right);
    }
    auto static constexpr startDepth{size_t{0}};
    std::vector<int> maxValsInEachRow;
};
