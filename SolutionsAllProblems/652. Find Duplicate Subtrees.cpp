// problem : https://leetcode.com/problems/find-duplicate-subtrees/description/ 
// submission : https://leetcode.com/problems/find-duplicate-subtrees/submissions/1502197223
// solution post : https://leetcode.com/problems/find-duplicate-subtrees/solutions/6251191/c-modern-readable-code-beats-98-runtime-4fb1n

// #include <string>
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
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

// let 'n' be a number of nodes in the tree
// time complexity O(n)
// space complexity O(n)
// runtime 8 ms, beats 97.87 %
/**
class Solution {
public:
    using NodePT = TreeNode *;
    using NodePsT = std::vector<NodePT>;
    NodePsT findDuplicateSubtrees(NodePT const root) {
        Reset();
        DoPostOrder(root);
        return rootsOfDupSubTrees; 
    }
private:
    size_t DoPostOrder(NodePT const node) {
        if(!node) {
            return 0;
        }
        auto triplet{std::to_string(DoPostOrder(node->left)) + "," +
            std::to_string(node->val) + "," +
            std::to_string(DoPostOrder(node->right))};
        auto const & [tripletToId, isInserted]{tripletsToIds.
            try_emplace(std::move(triplet), tripletsToIds.size() + 1)};
        if(++IdsToCounts[tripletToId->second] == 2) {
            rootsOfDupSubTrees.emplace_back(node);
        }
        return tripletToId->second;
    }
    void Reset() {
        tripletsToIds.clear();
        IdsToCounts.clear();
        rootsOfDupSubTrees.clear();
    }
    std::unordered_map<std::string, size_t> tripletsToIds;
    std::unordered_map<size_t, size_t> IdsToCounts;
    NodePsT rootsOfDupSubTrees;
};
