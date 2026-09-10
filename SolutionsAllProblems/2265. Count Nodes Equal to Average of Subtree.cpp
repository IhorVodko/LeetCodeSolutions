// problem : https://leetcode.com/problems/count-nodes-equal-to-average-of-subtree/description
// submission : https://leetcode.com/problems/count-nodes-equal-to-average-of-subtree/submissions/2137386412
// solution post : https://leetcode.com/problems/count-nodes-equal-to-average-of-subtree/solutions/8513628/
//  simplanation-simple-explanation-by-cyber-4jzv

// Approach : Iterative Post-Order Traversal with Graph Mutation
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the number of nodes
// Time :  O(n)
// Space : O(n)

// import std;

// #include <ios>
// #include <iostream>
// #include <stack>

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
 
namespace {

// Constant pointer alias preventing accidental root mutation
using nodeP = TreeNode * const;

constexpr auto const kInitialSubtreeSz{1}; 

// Initializer to configure fast I/O before main() runs
[[maybe_unused]]
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// State representation aggregating bottom-up subproblem data
struct Subtree {
    nodeP root{};
    int sum{};
    int sz{};
};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    static auto averageOfSubtree(nodeP root_) -> int;
};

auto Solution::averageOfSubtree(nodeP root_) -> int {
    if(!root_) {
        return 0;
    }

    auto validSubtreeCnt{0};

    // 1. Initialize iterative post-order traversal stack
    auto subtrees{std::stack<Subtree>{}};
    subtrees.emplace(root_, root_->val, kInitialSubtreeSz);

    while(!subtrees.empty()) {
        auto const [currSubtreeRoot, currSubtreeSum, currSubtreeSz]{subtrees.top()};

        // 2. Traverse left subtree and sever link to mark as visited
        if( auto const leftSubtreeRoot{currSubtreeRoot->left};
            leftSubtreeRoot
        ) {
            subtrees.emplace(leftSubtreeRoot, leftSubtreeRoot->val, kInitialSubtreeSz);
            currSubtreeRoot->left = nullptr;
        // 3. Traverse right subtree and sever link to mark as visited
        } else if(
            auto const rightSubtreeRoot{currSubtreeRoot->right};
            rightSubtreeRoot
        ) {
            subtrees.emplace(rightSubtreeRoot, rightSubtreeRoot->val, kInitialSubtreeSz);
            currSubtreeRoot->right = nullptr;
        // 4. Evaluate average condition for the fully processed subtree
        } else {
            if(currSubtreeSum / currSubtreeSz == currSubtreeRoot->val) {
                ++validSubtreeCnt;
            }

            subtrees.pop();

            // Safely deallocate the isolated node since its parent's link is already null
            delete currSubtreeRoot;

            if(subtrees.empty()) {
                continue;
            }
            
            // 5. Propagate current subtree aggregate data to parent node
            [[maybe_unused]]
            auto & [nextSubtreeRoot, nextSubtreeSum, nextSubtreeSz]{subtrees.top()};

            nextSubtreeSum += currSubtreeSum;
            nextSubtreeSz += currSubtreeSz;
        }
    }

    return validSubtreeCnt;
}
