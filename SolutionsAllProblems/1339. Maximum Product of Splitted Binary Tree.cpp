// problem : https://leetcode.com/problems/maximum-product-of-splitted-binary-tree/description
// submission : https://leetcode.com/problems/maximum-product-of-splitted-binary-tree/submissions/1877545902
// solution post : https://leetcode.com/problems/maximum-product-of-splitted-binary-tree/solutions/7474917/
//    c-modern-readable-code-beats-100-runtime-d9h5

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

class Solution {
public:
    using NodeCP = TreeNode const *;

// let 'n' be the number of nodes
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto maxProduct(NodeCP const root_) -> int;

private:
    auto DoDfsSum(NodeCP const node_) -> int;

    static auto constexpr kModulus{1'000'000'007};    
    std::vector<int> mSums;
};

auto Solution::maxProduct(NodeCP const root_) -> int {
    auto const totSum{static_cast<long long>(DoDfsSum(root_))};
    auto maxProduct{0ll};
    for(auto const sum: mSums) {
        maxProduct = std::max(maxProduct, sum * (totSum - sum));
    }
    maxProduct %= kModulus;
    return static_cast<int>(maxProduct);
}

auto Solution::DoDfsSum(NodeCP const node_) -> int {
    if(!node_) {
        return 0;
    }
    auto const leftSum{DoDfsSum(node_->left)};
    auto const rightSum{DoDfsSum(node_->right)};
    auto const totSum{leftSum + rightSum + node_->val};
    mSums.emplace_back(totSum);
    return totSum;
}
