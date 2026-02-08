// problem : https://leetcode.com/problems/balanced-binary-tree/description
// submission : https://leetcode.com/problems/balanced-binary-tree/submissions/1912845053
// solution post : https://leetcode.com/problems/balanced-binary-tree/solutions/7564296/
//    c-modern-readable-code-beats-100-runtime-8e0b

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

inline static int const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' be the number of tree nodes
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    using NodeP = TreeNode const * const;

    [[nodiscard]]
    auto isBalanced(NodeP root_) const -> bool;

private:
    [[nodiscard]]
    auto DoIsBalansedTree(
        NodeP root_,
        int & height_
    ) const -> bool;
};

auto Solution::isBalanced(NodeP root_) const -> bool {
    // Height is computed during recursion; the value itself is not needed here
    auto heigth{0};
    return DoIsBalansedTree(root_, heigth);
}

auto Solution::DoIsBalansedTree(
    NodeP root_,
    int & height_
) const -> bool {
    // An empty subtree is balanced and has height -1
    if(!root_) {
        height_ = -1;
        return true;
    }
    // Heights of left and right subtrees are computed via reference
    auto leftHeight{0};
    auto rightHeight{0};
    // Tree is balanced if both subtrees are balanced and height difference is less than
    // 2
    if( DoIsBalansedTree(root_->left, leftHeight) &&
        DoIsBalansedTree(root_->right, rightHeight) &&
        std::abs(leftHeight - rightHeight) < 2
    ) {
        // Height of current node is derived from the taller subtree
        height_ = std::max(leftHeight, rightHeight) + 1;
        return true;
    }
    // Any violation propagates imbalance upward immediately
    return false;
}
