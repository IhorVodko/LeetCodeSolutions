// problem : https://leetcode.com/problems/largest-bst-subtree/description
// submission : https://leetcode.com/problems/largest-bst-subtree/submissions/1682722534
// solution post : https://leetcode.com/problems/largest-bst-subtree/solutions/6907397/
//    c-modern-readable-code-beats-100-runtime-d1jj

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

class BSTData;

class Solution {
public:
    using intT = std::numeric_limits<int>;
    using NodeCPT = TreeNode const *;
// let 'n' be given tree size
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    int largestBSTSubtree(NodeCPT const nodeRoot_) const;
private:
    [[nodiscard]]
    BSTData DoHelper(NodeCPT const nodeRoot_) const;
};

class BSTData {
public:
    BSTData(
        int const valMin_,
        int const valMax_,
        int const treeSzMax_
    );
    [[nodiscard]]
    int ValMin() const {
        return mValMin;
    }
    [[nodiscard]]
    int ValMax() const {
        return mValMax;
    }
    [[nodiscard]]
    int TreeSzMax() const {
        return mTreeSzMax;
    }
private:
    int mValMin{};
    int mValMax{};
    int mTreeSzMax{};
};

int Solution::largestBSTSubtree(NodeCPT const nodeRoot_) const {
    auto const treeSzMax{DoHelper(nodeRoot_).TreeSzMax()};
    return treeSzMax;
}

BSTData Solution::DoHelper(NodeCPT const nodeRoot_) const {
    if(!nodeRoot_) {
        auto const BSTDataCurr{BSTData{intT::max(), intT::min(), 0}};
        return BSTDataCurr;
    }
    auto const BSTDataLeft{DoHelper(nodeRoot_->left)};
    auto const BSTDataRight{DoHelper(nodeRoot_->right)};
    auto const valCurr{nodeRoot_->val};
    if(BSTDataLeft.ValMax() < valCurr && valCurr < BSTDataRight.ValMin()) {
        auto const treeSzMax{BSTDataLeft.TreeSzMax() +
            BSTDataRight.TreeSzMax() + 1};
        auto const valMin{std::min(valCurr, BSTDataLeft.ValMin())};
        auto const valMax{std::max(valCurr, BSTDataRight.ValMax())};
        auto BSTDataCurr{BSTData{valMin, valMax, treeSzMax}};
        return BSTDataCurr;
    }
    auto const treeSzMax{std::max(BSTDataLeft.TreeSzMax(), BSTDataRight.TreeSzMax())};
    auto const BSTDataCurr{BSTData{intT::min(), intT::max(), treeSzMax}};
    return BSTDataCurr;
}

BSTData::BSTData(
    int const valMin_,
    int const valMax_,
    int const treeSzMax_
):
    mValMin{valMin_},
    mValMax{valMax_},
    mTreeSzMax{treeSzMax_}     
{}
