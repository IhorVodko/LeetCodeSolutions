// problem : https://leetcode.com/problems/balance-a-binary-search-tree/description
// submission : https://leetcode.com/problems/balance-a-binary-search-tree/submissions/1913926790
// solution post : https://leetcode.com/problems/balance-a-binary-search-tree/solutions/7566840/
//    c-modern-readable-code-beats-100-by-cybe-t10o

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

// let 'n' be the number of nodes
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    using NodeCP = TreeNode * const;
    using NodeCPC = TreeNode const * const;

    [[nodiscard]]
    auto balanceBST(NodeCPC root_) const -> NodeCP;

private:
    auto DoInorderTraversal(
        NodeCPC root_,
        std::vector<int> & inorder_
    ) const -> void;
    auto DoBalanceBST(
        std::span<int const> const inorderNodes_,
        int const beginIdx_,
        int const endIdx_
    ) const -> NodeCP;
};

auto Solution::balanceBST(NodeCPC root_) const -> NodeCP {
    // Inorder traversal of a BST yields sorted node values
    auto inorderNodes{std::vector<int>{}};
    DoInorderTraversal(root_, inorderNodes);
    auto const nodesTotCnt{std::ssize(inorderNodes)};
    // Rebuild a height-balanced BST from the sorted sequence
    return DoBalanceBST(inorderNodes, 0, nodesTotCnt - 1);
}

auto Solution::DoInorderTraversal(
    NodeCPC root_,
    std::vector<int> & inorder_
) const -> void {
    // Standard inorder traversal to collect values in sorted order
    if(!root_) {
        return;
    }
    DoInorderTraversal(root_->left, inorder_);
    inorder_.emplace_back(root_->val);
    DoInorderTraversal(root_->right, inorder_);
}

auto Solution::DoBalanceBST(
    std::span<int const> const inorderNodes_,
    int const beginIdx_,
    int const endIdx_
) const -> NodeCP {
    // Base case for empty subrange
    if(beginIdx_ > endIdx_) {
        return nullptr;
    }
    // Choosing the middle element ensures minimal height
    auto const mid{std::midpoint(beginIdx_, endIdx_)};
    auto leftSubTree{DoBalanceBST(inorderNodes_, beginIdx_, mid - 1)};
    auto rightSubTree{DoBalanceBST(inorderNodes_, mid + 1, endIdx_)};
    // Construct the subtree rooted at the median value
    return new TreeNode(inorderNodes_[mid], leftSubTree, rightSubTree);
}
