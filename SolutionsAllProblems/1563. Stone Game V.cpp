// problem : https://leetcode.com/problems/stone-game-v/description/ 
// submission : https://leetcode.com/problems/stone-game-v/submissions/2110563440
// solution post : https://leetcode.com/problems/stone-game-v/solutions/8466884/
//    simplanation-simple-explanation-by-cyber-kgcp

// Approach : Dynamic Programming with Monotonic Pivot Optimization
// Runtime : 14 ms, beats 99.39 %

// Complexity analysis
// let 'n' be the number of stones
// Time :  O(n^2)
// Space : O(n^2)

// import std;

// #include <vector>
// #include <numeric>
// #include <algorithm>
// #include <ranges>

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

// Hardware optimization offsets
constexpr auto kCacheStridePadding{8};
constexpr auto kDpSentinelPadding{2};

// Game state thresholds    
constexpr auto kMaxStonesNoSplit{1};
constexpr auto kStonesTrivialSplit{2};

// Algorithmic multipliers and shifts
constexpr auto kHalfSumMult{2};
constexpr auto kEqualSplitIdxShift{1};
constexpr auto kUnequalSplitIdxShift{0};

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// Flattened 2D array with padding to mitigate cache line contention
class CachePaddedGrid {
public:
    explicit CachePaddedGrid(int const sz_) :
        mStride{sz_ + kCacheStridePadding},
        mGridData((sz_ + kDpSentinelPadding) * mStride)
    {}

    auto operator[](
        int const rowIdx_,
        int const colIdx_
    ) -> int & {
        return mGridData[rowIdx_ * mStride + colIdx_];
    }

private:
    int mStride{};
    std::vector<int> mGridData;
};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    static auto stoneGameV(std::vector<int> const & stones_) -> int;
};

auto Solution::stoneGameV(std::vector<int> const & stones_) -> int {
    auto const totStones{static_cast<int>(stones_.size())};

    // Handle edge cases where splitting is impossible or trivial
    if(totStones <= kMaxStonesNoSplit) [[unlikely]] {
        return 0;
    }
    if(totStones == kStonesTrivialSplit) [[unlikely]] {
        return std::min(stones_[0], stones_[1]);
    }

    // 1. Precompute prefix sums to quickly calculate arbitrary subarray sums
    auto prefSums{std::vector<int>(totStones + 1)};
    std::inclusive_scan(stones_.cbegin(), stones_.cend(), prefSums.begin() + 1);

    // 2. Initialize padded DP grids to memoize max scores for valid splits
    auto maxLeftChoices{CachePaddedGrid{totStones}};
    auto maxRightChoices{CachePaddedGrid{totStones}};

    // Base states setup for single-stone segments
    for(auto const idx: vs::iota(1, totStones + 1)) {
        auto const currStone{stones_[idx - 1]};

        maxLeftChoices[idx, idx] = maxRightChoices[idx, idx] = currStone;
        maxLeftChoices[idx, idx - 1] = maxRightChoices[idx + 1, idx] =  0;
    }

    auto finalMaxScore{0};

    // 3. Evaluate all subsegments bottom-up by expanding segment lengths
    for(auto reversedStarts{vs::iota(1, totStones) | vs::reverse};
        auto startIdx: reversedStarts
    ) {
        // Sliding boundary separating lighter left part from heavier right part
        auto pivotIdx{startIdx};

        for(auto forwardEnds{vs::iota(startIdx + 1, totStones + 1)};
            auto const endIdx: forwardEnds
        ) {
            // 4. Advance pivot to find the median sum boundary of the segment
            auto const targetSum{prefSums[startIdx - 1] + prefSums[endIdx]};
            while((prefSums[pivotIdx] * kHalfSumMult) < targetSum) {
                ++pivotIdx;
            }

            // 5. Detect perfect equal-sum splits to maximize available choices
            auto const isPerfectSplit{(prefSums[pivotIdx] * kHalfSumMult == targetSum) ?
                kEqualSplitIdxShift : kUnequalSplitIdxShift 
            };

            // 6. Find optimal score by fetching the best valid precomputed branch
            auto const currSegmentScore{std::max(
                maxLeftChoices[startIdx, pivotIdx - 1 + isPerfectSplit],
                maxRightChoices[pivotIdx + 1, endIdx]
            )};
            finalMaxScore = currSegmentScore;

            // 7. Accumulate sums to form rolling optimal choices for larger ranges
            auto const totalSegmentSum{prefSums[endIdx] - prefSums[startIdx - 1]};
            auto const cascadingScore{totalSegmentSum + currSegmentScore};

            maxLeftChoices[startIdx, endIdx] = std::max(
                maxLeftChoices[startIdx, endIdx - 1],
                cascadingScore
            );
            maxRightChoices[startIdx, endIdx] = std::max(
                maxRightChoices[startIdx + 1, endIdx],
                cascadingScore
            );
        }
    }

    return finalMaxScore;
}
