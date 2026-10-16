// problem : https://leetcode.com/problems/subarrays-distinct-element-sum-of-squares-ii/description
// submission : https://leetcode.com/problems/subarrays-distinct-element-sum-of-squares-ii/submissions/2174022919
// solution post : https://leetcode.com/problems/subarrays-distinct-element-sum-of-squares-ii/solutions/8575488/
//    simplanation-simple-explanation-by-cyber-54a7

// Approach : Dynamic Range Updates & Mathematical Square Expansion
// Runtime : 139 ms, beats 98.70 %

// Complexity analysis
// let 'n' be the total number of elements in the given array
// Time :  O(n * log(n))
// Space : O(n)

// import std;

// #include <algorithm>
// #include <cstddef>
// #include <ios>
// #include <iostream>
// #include <iterator>
// #include <ranges>
// #include <unordered_map>
// #include <vector>

namespace vs = std::views;

using std::ptrdiff_t;

namespace {

constexpr auto kMod{1'000'000'007z};

// Optimize standard I/O stream operations performance.
[[maybe_unused]]
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// Maintains dynamic range sums and applies range updates via difference arrays.
class FenwickTree final {
public:
    // Setup dual difference arrays for tracking dynamic subarray counts.
    explicit FenwickTree(ptrdiff_t const sz_):
        mTreeSz{sz_},
        mDiffTree(sz_ + 1),
        mIdxDiffTree(sz_ + 1)
    {}

    // Increment distinct counts across the subarray range newly covering the element.
    auto UpdateRng(
        ptrdiff_t const leftIdx_,
        ptrdiff_t const rightIdx_,
        ptrdiff_t const delta_
    ) -> void {
        DoUpdateRng(leftIdx_, delta_);
        DoUpdateRng(rightIdx_ + 1, -delta_);
    }

    // Retrieve the sum of distinct counts for subarrays ending at the current index.
    [[nodiscard]]
    auto QueryRng(
        ptrdiff_t const leftIdx_,
        ptrdiff_t const rightIdx_
    ) const -> ptrdiff_t {
        return QueryPref(rightIdx_) - QueryPref(leftIdx_ - 1);
    }

private:
    // Extract the lowest set bit to dynamically navigate the tree interval hierarchy.
    [[nodiscard]]
    auto GetLSB(ptrdiff_t const idx_) const -> ptrdiff_t {
        return idx_ & -idx_;
    }

    // Propagate difference array changes up the tree to reflect boundary updates.
    auto DoUpdateRng(
        ptrdiff_t idx_,
        ptrdiff_t const delta_
    ) -> void {
        ++idx_;

        auto const rawIdx{idx_};

        while(idx_ <= mTreeSz) {
            mDiffTree[idx_] += delta_;
            mIdxDiffTree[idx_] += rawIdx * delta_;
            idx_ += GetLSB(idx_);
        }
    }

    // Aggregate prefix distinct counts utilizing linear difference array properties.
    [[nodiscard]]
    auto QueryPref(ptrdiff_t idx_) const -> ptrdiff_t {
        idx_ = std::min(++idx_, mTreeSz);

        auto const rawIdx{idx_ + 1};
        auto prefSum{0uz};

        while(idx_ > 0) {
            prefSum += rawIdx * mDiffTree[idx_] - mIdxDiffTree[idx_];
            idx_ -= GetLSB(idx_);
        }

        return prefSum;
    }

    ptrdiff_t mTreeSz{};
    // Base difference array tracking raw range distinct count increments.
    std::vector<ptrdiff_t> mDiffTree;
    // Weighted difference array for precise prefix sum reconstruction.
    std::vector<ptrdiff_t> mIdxDiffTree; 
};

} // namespace 

class Solution final {
public:
    [[nodiscard]]
    static auto sumCounts(std::vector<int> const & nums_) -> int;
};

auto Solution::sumCounts(std::vector<int> const & nums_) -> int {
    auto const numsTot{std::ssize(nums_)};
    auto distinctSumSq{0z};
    auto currEndingSumSq{0z};
    auto tree{FenwickTree{numsTot}};
    auto numToLastSeenPos{std::unordered_map<int, ptrdiff_t>{}};
    
    // 1. Iterate through elements treating each as the end of valid subarrays.
    for(auto const [currIdx, num]: nums_ | vs::enumerate) {
        // 2. Identify the index bound where the current element contributes newly.
        auto const startIdx{
            (numToLastSeenPos.contains(num) ? numToLastSeenPos[num] : -1) + 1
        };
        // 3. Query the sum of distinct counts for the relevant subarrays ending here.
        auto const rngSum{tree.QueryRng(startIdx, currIdx)};
        // 4. Determine the number of subarrays receiving a +1 distinct increment.
        auto const rangeLength{currIdx - startIdx + 1};
        
        // 5. Expand the square mathematically to update the dynamically rolling sum:
        // Using (x + 1)^2 = x^2 + 2x + 1, the new sum adds 2 * rngSum + rangeLength.
        currEndingSumSq = (currEndingSumSq + rngSum * 2 + rangeLength) % kMod;
        // 6. Accumulate the total square sums across all valid subsegments.
        distinctSumSq = (distinctSumSq + currEndingSumSq) % kMod;
        
        // 7. Increment distinct counts in the tree for the affected boundary range.
        tree.UpdateRng(startIdx, currIdx, 1);
        // 8. Track the element's position for future duplicate resolution boundary.
        numToLastSeenPos[num] = currIdx;
    }

    return static_cast<int>(distinctSumSq);
}
