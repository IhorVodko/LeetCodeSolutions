// problem : https://leetcode.com/problems/find-x-value-of-array-ii/description
// submission : https://leetcode.com/problems/find-x-value-of-array-ii/submissions/2149759366
// solution post : https://leetcode.com/problems/find-x-value-of-array-ii/solutions/8534594/simplanation-simple-explanation-by-cyber-svuf

// Approach : Segment Tree with range state merging for prefix properties
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'N' be the count of numbers
// 'Q' - count of queries
// 'M' - the maximum modulo value
// Time :  O(N * M + Q * log(N) * M)
// Space : O(N * M)

// import std;

// #include <array>
// #include <bit>
// #include <ios>
// #include <iostream>
// #include <numeric>
// #include <ranges>
// #include <tuple>
// #include <vector>

// #include <cstddef>

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

// Configuration constants for segment tree layout and modulus constraints.
constexpr auto kMaxModVal{5};
constexpr auto kChildMult{2};
constexpr auto kRChildOffset{1};
constexpr auto kIdxOffset{1};
constexpr auto kRootIdx{1};

// Optimize standard I/O stream operations performance.
[[maybe_unused]]
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// Node maintains remainder frequencies and subarray product.
struct SegTreeNode final {
    std::array<int, kMaxModVal> mCntPerRem;
    int mProd{1};
};

// Tree coordinates array segments to resolve prefix combinations.
class SegTree final {
public:
    explicit SegTree(
        std::vector<int> const & nums_,
        int const modVal_
    ):
        mNumTot{static_cast<int>(nums_.size())},
        mModVal{modVal_},
        mNodes(mNumTot == 0 ?
            0 : std::bit_ceil(static_cast<unsigned int>(mNumTot)) * kChildMult
        )
    {
        if(mNumTot <= 0) {
           return;
        }

        ConstructTree(nums_, kRootIdx, 0, mNumTot - kIdxOffset);
    }

    auto UpdateTree(
        int const targetNodeIdx_,
        int const newVal_
    ) -> void {
        if(mNumTot <= 0) {
            return;
        }

        DoUpdateTree(kRootIdx, 0, mNumTot - kIdxOffset, targetNodeIdx_, newVal_);
    }

    [[nodiscard]]
    auto Query(
        int const queryLIdx_,
        int const queryRIdx_
    ) const -> SegTreeNode {
        if(mNumTot <= 0 || queryLIdx_ > queryRIdx_) {
            return {};
        }

        return DoQuery(kRootIdx, 0, mNumTot - kIdxOffset, queryLIdx_, queryRIdx_);
    }

private:
    // Initialize leaf node with a specific value modulo constraint.
    auto AddNode(
        int const idx_, 
        int val_
    ) -> void {
        val_ %= mModVal;

        mNodes[idx_].mCntPerRem.fill(0);
        mNodes[idx_].mCntPerRem[val_] = 1;
        mNodes[idx_].mProd = val_;
    }

    // Combine left and right subtrees into a single aggregated node.
    auto MergeNodes(
        SegTreeNode const & lNode_,
        SegTreeNode const & rNode_,
        SegTreeNode & mergedNode_,
        int const modVal_
    ) const -> void {
        auto & [mergedCntPerRem, mergedProd]{mergedNode_};
        auto const & [lCntPerRem, lProd]{lNode_};
        auto const & [rCntPerRem, rProd]{rNode_};

        mergedCntPerRem.fill(0);
        mergedProd = (lProd * rProd) % modVal_;
        
        for(auto const remIdx: vs::iota(0, modVal_)) {
            mergedCntPerRem[remIdx] = lCntPerRem[remIdx];
        }
        
        for(auto const remIdx: vs::iota(0, modVal_)) {
            auto const shiftedRem{(lProd * remIdx) % modVal_};
            mergedCntPerRem[shiftedRem] += rCntPerRem[remIdx];
        }
    }

    // Propagate updated states up through the tree structure.
    auto UpdateNode(int const updateIdx_) -> void {
        auto const lChildIdx{updateIdx_ * kChildMult};
        auto const rChildIdx{updateIdx_ * kChildMult + kRChildOffset};
        
        MergeNodes(
            mNodes[lChildIdx], mNodes[rChildIdx], mNodes[updateIdx_], mModVal
        );
    }

    // Recursively build segment tree by dividing array range.
    auto ConstructTree(
        std::vector<int> const & nums_,
        int const nodeIdx_,
        int const rngLIdx,
        int const rngRIdx
    ) -> void {
        if(rngLIdx == rngRIdx) {
            AddNode(nodeIdx_, nums_[rngLIdx]);

            return;
        }
        
        auto const rngMidIdx{std::midpoint(rngLIdx, rngRIdx)};
        auto const lChildIdx{nodeIdx_ * kChildMult};
        auto const rChildIdx{(nodeIdx_ * kChildMult) + kRChildOffset};
        
        ConstructTree(nums_, lChildIdx, rngLIdx, rngMidIdx);
        ConstructTree(nums_, rChildIdx, rngMidIdx + kIdxOffset, rngRIdx);
        UpdateNode(nodeIdx_);
    }

    // Traverse tree to update target leaf and recalculate ancestors.
    auto DoUpdateTree(
        int const currNodeIdx_,
        int const rngLIdx_,
        int const rngRIdx_,
        int const targetNodeIdx_,
        int const newVal_
    ) -> void {
        if(rngLIdx_ == rngRIdx_) {
            AddNode(currNodeIdx_, newVal_);
            
            return;
        }
        
        auto const rngMidIdx{std::midpoint(rngLIdx_, rngRIdx_)};
        auto const lChildIdx{currNodeIdx_ * kChildMult};
        auto const rChildIdx{(currNodeIdx_ * kChildMult) + kRChildOffset};

        if(targetNodeIdx_ <= rngMidIdx) {
            DoUpdateTree(lChildIdx, rngLIdx_, rngMidIdx, targetNodeIdx_, newVal_);
        } else {
            DoUpdateTree(
                rChildIdx, rngMidIdx + kIdxOffset, rngRIdx_, targetNodeIdx_, newVal_
            );
        }
        
        UpdateNode(currNodeIdx_);
    }

    // Retrieve merged node representing the queried subarray range.
    [[nodiscard]]
    auto DoQuery(
        int const currNodeIdx_,
        int const rngLIdx_,
        int const rngRIdx_,
        int const queryLIdx_,
        int const queryRIdx_
    ) const -> SegTreeNode {
        if(queryLIdx_ <= rngLIdx_ && rngRIdx_ <= queryRIdx_) {
            return mNodes[currNodeIdx_];
        }
        
        auto const rngMidIdx{std::midpoint(rngLIdx_, rngRIdx_)};
        auto const lChildIdx{currNodeIdx_ * kChildMult};
        auto const rChildIdx{(currNodeIdx_ * kChildMult) + kRChildOffset};

        if(queryRIdx_ <= rngMidIdx) {
            return DoQuery(lChildIdx, rngLIdx_, rngMidIdx, queryLIdx_, queryRIdx_);
        }

        if(queryLIdx_ > rngMidIdx) {
            return DoQuery(
                rChildIdx, rngMidIdx + kIdxOffset, rngRIdx_, queryLIdx_, queryRIdx_)
            ;
        }
        
        auto const lSubtreeRes{DoQuery(
            lChildIdx, rngLIdx_, rngMidIdx, queryLIdx_, queryRIdx_
        )};
        auto const rSubtreeRes{DoQuery(
            rChildIdx, rngMidIdx + kIdxOffset, rngRIdx_, queryLIdx_, queryRIdx_
        )};
        
        auto mergedNode{SegTreeNode{}};
        MergeNodes(lSubtreeRes, rSubtreeRes, mergedNode, mModVal);
        
        return mergedNode;
    }

    int mNumTot{};
    int mModVal{};
    std::vector<SegTreeNode> mNodes;
};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    static auto resultArray(
        std::vector<int> const & nums_,
        int const modVal_,
        std::vector<std::vector<int>> const & queries_
    ) -> std::vector<int>;
};

auto Solution::resultArray(
    std::vector<int> const & nums_,
    int const modVal_,
    std::vector<std::vector<int>> const & queries_
) -> std::vector<int> {
    // 1. Initialize result vector to track remainder counts for each query.
    auto cntPerRem{std::vector<int>{}};
    cntPerRem.reserve(queries_.size());
    
    // 2. Construct segment tree to manage prefix products and remainders.
    auto tree{SegTree{nums_, modVal_}};
    auto const numTot{static_cast<int>(nums_.size())};

    // 3. Process each query sequentially to apply updates and retrieve counts.
    for(auto const & query : queries_) {
        auto const updateIdx{query[0]};
        auto const newVal{query[1]};
        auto const numsStartIdx_{query[2]};
        auto const rem{query[3]};

        // 4. Update the segment tree node at the given index with the new value.
        tree.UpdateTree(updateIdx, newVal);
        
        // 5. Query the tree to find count of the target remainder and append.
        cntPerRem.emplace_back(
            tree.Query(numsStartIdx_, numTot - kIdxOffset).mCntPerRem[rem]
        );
    }

    return cntPerRem;
}
