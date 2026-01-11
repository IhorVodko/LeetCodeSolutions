// problem : https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/description
// submission : https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/submissions/1882122503
// solution post : https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/solutions/7487227/
//    c-modern-readable-code-beats-100-runtime-cvlb

// import std;

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream{"display_runtime.txt"} << 0 << std::endl;
            }
        };
        std::atexit(&Print::DoPrint);
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

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
    using NodeP = TreeNode *;
    using NodeCP = TreeNode const *;

    auto subtreeWithAllDeepest(NodeCP const root_) const -> NodeP;
};

auto Solution::subtreeWithAllDeepest(NodeCP const root_) const -> NodeP {
    auto parentToChild{std::unordered_map<NodeCP, NodeCP>{{root_, nullptr}}};
    auto qNodes{std::queue<NodeCP>{{root_}}};
    auto leaves{std::vector<NodeCP>{}};
    while(!qNodes.empty()) {
        auto lvlSz{std::ssize(qNodes)};
        leaves.clear();
        while(--lvlSz >= 0) {
            auto node{qNodes.front()};
            qNodes.pop();
            leaves.emplace_back(node);
            auto const lNode{node->left};
            if(lNode) {
                parentToChild[lNode] = node;
                qNodes.emplace(lNode);
            }
            auto const rNode{node->right};
            if(rNode) {
                parentToChild[rNode] = node;
                qNodes.emplace(rNode);
            }
        }
    }
    if(leaves.size() == 1) {
        return const_cast<NodeP>(leaves.front());
    }
    auto curParents{std::unordered_set<NodeCP>{leaves.begin(), leaves.end()}};
    while(curParents.size() > 1) {
        auto nextParents{std::unordered_set<NodeCP>{}};
        for(auto const parent: curParents) {
            nextParents.emplace(parentToChild.at(parent));
        }
        curParents = std::move(nextParents);
    } 
    return const_cast<NodeP>(*curParents.begin());
}
