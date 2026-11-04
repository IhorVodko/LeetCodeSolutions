// problem : https://leetcode.com/problems/minimum-operations-to-make-elements-within-k-subarrays-equal/description
// submission : https://leetcode.com/problems/minimum-operations-to-make-elements-within-k-subarrays-equal/submissions/2189532761
// solution post : https://leetcode.com/problems/minimum-operations-to-make-elements-within-k-subarrays-equal/solutions/8601835/
//    simplanation-simple-explanation-by-cyber-fb65

// Approach : Coordinate-Compressed Dual Fenwick Trees + Space-Optimized Dynamic Programming
// Runtime : 560 ms, beats 98.44 %

// Complexity analysis
// let 'n' be the count of numbers
// 'm' - required count of disjoint subarrays
// Time :  O(n * log(n) + n * m)
// Space : O(n)

// import std;

// #include <algorithm>
// #include <bit>
// #include <ios>
// #include <iostream>
// #include <iterator>
// #include <limits>
// #include <ranges>
// #include <vector>

// #include <cstddef>

namespace rs = std::ranges;
namespace vs = std::views;

using std::size_t;
using std::ptrdiff_t;

namespace {

// Half of max 64-bit integer prevents addition overflow during DP transitions.
constexpr auto kInfinity{std::numeric_limits<long long>::max() / 2};
constexpr auto kFreqDecr{-1};
constexpr auto kFreqIncr{1};

// Maintains dynamic prefix frequencies and value sums for sliding windows.
class FenwickTree final {
public:
    explicit FenwickTree(size_t const treeSz_):
        mTreeSz{treeSz_},
        mTree(treeSz_ + 1)
    {} 

    // Propagates point frequency or value delta across covering tree intervals.
    auto AddVal(
        size_t idx_,
        long long const num_
    ) -> void {
        for(; idx_ <= mTreeSz; idx_ += idx_ & -idx_) {
            mTree[idx_] += num_;
        }
    }

    // Aggregates cumulative count or sum for compressed ranks up to idx_.
    auto queryPref(size_t idx_) const -> long long {
        auto sum{0ll};

        for(; idx_ > 0; idx_ -= idx_ & -idx_) {
            sum += mTree[idx_];
        }

        return sum;
    }

    // Binary-lifts over tree bit-intervals to locate the k-th order statistic.
    auto findKth(long long const medianIdx_) const -> int {
        auto currIdx{0z};
        auto sum{0ll};

        const auto maxBitIdx{static_cast<size_t>(std::bit_width(mTreeSz) - 1)};

        for(auto step{1 << maxBitIdx}; step > 0; step >>= 1) {
            const auto nextIdx{currIdx + step};

            // Advance rank if cumulative frequency stays strictly below target.
            if(nextIdx <= mTreeSz &&
                sum + mTree[nextIdx] < medianIdx_    
            ) {
                currIdx = nextIdx;
                sum += mTree[nextIdx];
            }
        }

        return currIdx + 1;
    }

private:
    size_t mTreeSz{};
    std::vector<long long> mTree;
};

// Maps an element value to its 1-based rank among sorted unique array values.
const auto calcNumCompressedId{[] [[nodiscard]]  (
    std::vector<int> const & uniqueNums_,
    int const num_
) {
    const auto lbIt{rs::lower_bound(uniqueNums_, num_)};
    const auto idx{std::distance(uniqueNums_.begin(), lbIt)};
    
    return static_cast<size_t>(idx) + 1;
}};

// Optimize standard I/O stream operations performance.
[[maybe_unused]]
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};


} // namespace 

class Solution final {
public:
    [[nodiscard]]
    static auto minOperations(
        std::vector<int> const & nums_,
        int const subarrSz_,
        int const reqSubarrsTot_
    ) -> long long;

private:
    [[nodiscard]]
    static auto CalcWndwCosts(
        std::vector<int> const & nums_,
        int const subarrSz_
    ) -> std::vector<long long>;

    [[nodiscard]]
    static auto CallWndwCost(
        FenwickTree const & wndwValFreqs_,
        FenwickTree const & wndwSums_,
        std::vector<int> const & uniqueNums_,
        int const subarrSz_
    ) -> long long;
};

auto Solution::minOperations(
    std::vector<int> const & nums_,
    int const subarrSz_,
    int const reqSubarrsTot_
) -> long long {
    const auto numsTot{static_cast<int>(nums_.size())};
    // 1. Precompute minimum cost to equalize every contiguous window.
    const auto wndwCosts{CalcWndwCosts(nums_, subarrSz_)};

    // 2. Allocate rolling DP tables for previous and current subarray counts.
    auto currMinCosts{std::vector<long long>(numsTot + 1)};
    auto nextMinCosts{std::vector<long long>(numsTot + 1)};

    // 3. Iterate through the number of disjoint subarrays selected so far.
    for(const auto subarrCnt: vs::iota(1, reqSubarrsTot_ + 1)) {
        rs::fill(nextMinCosts, kInfinity);

        const auto startIdx{subarrCnt * subarrSz_};

        // 4. Transition DP by either skipping or picking the window at dpIdx.
        for(const auto dpIdx: vs::iota(startIdx, numsTot + 1)) {
            const auto costIfSkipped{nextMinCosts[dpIdx - 1]};
            const auto costIfTaken{
                currMinCosts[dpIdx - subarrSz_] +  wndwCosts[dpIdx - 1]
            };

            nextMinCosts[dpIdx] = std::min(costIfSkipped, costIfTaken); 
        } 

        currMinCosts.swap(nextMinCosts);
    }

    const auto minCost{currMinCosts[numsTot]};

    return minCost;
}

auto Solution::CalcWndwCosts(
    std::vector<int> const & nums_,
    int const subarrSz_
) -> std::vector<long long> {
    const auto numsTot{std::ssize(nums_)};
    auto wndwCosts{std::vector<long long>(numsTot)};

    // 1. Coordinate-compress input values into compact 1-based Fenwick ranks.
    auto uniqueNums{nums_};
    rs::sort(uniqueNums);
    const auto [remBegIt, remEndIt]{rs::unique(uniqueNums)};
    uniqueNums.erase(remBegIt, remEndIt);
    const auto uniqueNumsTot{uniqueNums.size()};

    // 2. Create dual Fenwick trees for window element frequencies and sums.
    auto wndwValFreqs{FenwickTree{uniqueNumsTot}};
    auto wndwSums{FenwickTree{uniqueNumsTot}};

    // Updates both frequency and value-sum trees when window elements change.
    const auto addToTrees{[&] [[nodiscard]] (
        int const num_,
        int const freqDelta_
    ) {
        const auto compressedId{calcNumCompressedId(uniqueNums, num_)};
        const auto weightedDelta{static_cast<long long>(num_) * freqDelta_};

        wndwValFreqs.AddVal(compressedId, freqDelta_);
        wndwSums.AddVal(compressedId, weightedDelta);
    }};

    // 3. Populate trees with the first window and record its equalization cost.
    for(const auto idx: vs::iota(0, subarrSz_)) {
        addToTrees(nums_[idx], kFreqIncr);
    }

    wndwCosts[subarrSz_ - 1] =
        CallWndwCost(wndwValFreqs, wndwSums, uniqueNums, subarrSz_);

    // 4. Slide the window across the array, updating trees and window costs.
    for(const auto idx: vs::iota(subarrSz_, numsTot)) {
        addToTrees(nums_[idx - subarrSz_], kFreqDecr);
        addToTrees(nums_[idx], kFreqIncr);

        wndwCosts[idx] = CallWndwCost(wndwValFreqs, wndwSums, uniqueNums, subarrSz_);
    }

    return wndwCosts;
}

auto Solution::CallWndwCost(
    FenwickTree const & wndwValFreqs_,
    FenwickTree const & wndwSums_,
    std::vector<int> const & uniqueNums_,
    int const subarrSz_
) -> long long {
    // 1. Locate the window median via binary lifting on the frequency tree.
    const auto medianIdx{(subarrSz_ + 1) / 2};
    const auto medianId{wndwValFreqs_.findKth(medianIdx)};
    const auto medianValue{static_cast<long long>(uniqueNums_[medianId - 1])};

    // 2. Partition window sums around the median to compute total L1 (Manhattan) distance.
    const auto leftCnt{wndwValFreqs_.queryPref(medianId)};
    const auto leftSum{wndwSums_.queryPref(medianId)};
    const auto totalSum{wndwSums_.queryPref(uniqueNums_.size())};
    const auto rightCnt{static_cast<long long>(subarrSz_) - leftCnt};
    const auto rightSum{totalSum - leftSum};

    return (medianValue * leftCnt - leftSum) + (rightSum - medianValue * rightCnt); 
}
