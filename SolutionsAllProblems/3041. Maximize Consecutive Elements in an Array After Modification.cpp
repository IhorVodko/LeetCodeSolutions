// problem : https://leetcode.com/problems/maximize-consecutive-elements-in-an-array-after-modification/description
// submission : https://leetcode.com/problems/maximize-consecutive-elements-in-an-array-after-modification/submissions/2200136656
// solution post : https://leetcode.com/problems/maximize-consecutive-elements-in-an-array-after-modification/solutions/8619293/
//  simplanation-simple-explanation-by-cyber-r81g

// Approach : Sorting with Gap-Driven O(1)-State Dynamic Programming
// Runtime : 44 ms, beats 91.26 %

// Complexity analysis
// let 'n' be the count of numbers
// Time :  O(n * log(n))
// Space : O(sort(n))

// import std;

// #include <algorithm>
// #include <functional>
// #include <ios>
// #include <iostream>
// #include <ranges>
// #include <vector>

namespace rs = std::ranges;
namespace vs = std::views;

namespace {

constexpr auto kMinSeqLen{1};
constexpr auto kNoNumsGap{0};
constexpr auto kAdjacentNumsGap{1};
constexpr auto kBridgeableNumsGap{2};

// Tracks overall best chain and chains ending at current x or x + 1.
struct SeqLenData final {
    int maxSeqLen{kMinSeqLen};
    int lenIfNumUnmodified{kMinSeqLen};
    int lenIfNumIncremented{kMinSeqLen};
};

// Advances consecutive chain lengths across one ascending neighbor gap.
constexpr auto calcMaxSeqLen{[] [[nodiscard]] (
    const auto seqLenData_,
    const auto gap_
) -> SeqLenData {
    auto [maxSeqLen, lenIfNumUnmodified, lenIfNumIncremented]{seqLenData_};

    switch(gap_) {
        case kNoNumsGap: {
            // Duplicate x: unmodified stays; incremented x extends x to x + 1.
            lenIfNumIncremented = lenIfNumUnmodified + 1;
            break;
        }
        case kAdjacentNumsGap: {
            // Adjacent values: both unmodified and incremented chains extend.
            ++lenIfNumUnmodified;
            ++lenIfNumIncremented;
            break;
        }
        case kBridgeableNumsGap: {
            // Gap of 2: x bridges prev + 1; incremented x + 1 starts anew.
            lenIfNumUnmodified = lenIfNumIncremented + 1;
            lenIfNumIncremented = kMinSeqLen;
            break;
        }
        default: {
            // Gap > 2 is unbridgeable even with +1; reset both chains.
            lenIfNumUnmodified = lenIfNumIncremented = kMinSeqLen;
        }
    }

    maxSeqLen = std::max(
        maxSeqLen,
        std::max(lenIfNumUnmodified, lenIfNumIncremented)
    );

    return {maxSeqLen, lenIfNumUnmodified, lenIfNumIncremented};
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
    static auto maxSelectedElements(std::vector<int> & nums_) -> int; 
};

auto Solution::maxSelectedElements(std::vector<int> & nums_) -> int {
    if(nums_.empty()) {
        return 0;
    }

    // 1. Sort descending so adjacent subtractions produce non-negative gaps.
    rs::sort(nums_, std::greater{});

    // 2. Reverse descending diffs to stream ascending gaps between neighbors.
    auto gaps{nums_ | vs::pairwise_transform(std::minus{}) | vs::reverse};
    // 3. Fold ascending gaps into DP state to maximize consecutive length.
    const auto seqLenData{rs::fold_left(gaps, SeqLenData{}, calcMaxSeqLen)};

    return seqLenData.maxSeqLen;
}
