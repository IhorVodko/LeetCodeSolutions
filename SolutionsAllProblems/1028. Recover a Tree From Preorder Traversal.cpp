// problem : https://leetcode.com/problems/recover-a-tree-from-preorder-traversal/description/
// submission : https://leetcode.com/problems/recover-a-tree-from-preorder-traversal/submissions/1553171233
// solution post : https://leetcode.com/problems/recover-a-tree-from-preorder-traversal/solutions/6460489/
//     c-modern-readable-code-beats-100-runtime-qxqw

// #include <stack>
// #include <string>

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

// let 'n' be a length of the given string
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    using Node = TreeNode;
    using NodeP = Node *;
    TreeNode * recoverFromPreorder(std::string const & traversal) const {
        auto digitsCount{size_t{0}};
        auto const head{new Node{stoi(traversal, &digitsCount)}};
        auto nodes{std::stack<NodeP>{}}; 
        nodes.emplace(head);
        auto level{size_t{0}};
        for(auto chrIt{traversal.begin() + digitsCount},
            chrEnd{traversal.end()}; chrIt < chrEnd;
        ) {
            if(*chrIt == '-') {
                ++level;
                ++chrIt;
            } else {
                while(nodes.size() > level) {
                    nodes.pop();
                }
                auto const nodeCurr{nodes.top()};
                auto const [num, numSize]{ChrToInt(chrIt, chrEnd)};
                auto const nodeNext{new Node{num}};
                if(!nodeCurr->left) {
                    nodeCurr->left = nodeNext;
                } else {
                    nodeCurr->right = nodeNext;
                }
                nodes.emplace(nodeNext);
                level = 0;
                chrIt += numSize;
            }
        }
        return head;
    }
private:
    std::pair<int, size_t> ChrToInt(
        std::string::const_iterator first,
        std::string::const_iterator const last
    ) const {
        auto num{0};
        auto numSize{size_t{0}};
        while(first < last && std::isdigit(*first)) {
            num = num * 10 + *first++ - '0';
            ++numSize;
        }
        return {num, numSize};
    }
};
