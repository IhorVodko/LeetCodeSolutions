// problem : https://leetcode.com/problems/count-number-of-maximum-bitwise-or-subsets/description/
// submission : https://leetcode.com/problems/count-number-of-maximum-bitwise-or-subsets/submissions/1716022682
// solution post : https://leetcode.com/problems/count-number-of-maximum-bitwise-or-subsets/solutions/7020641/
//    c-modern-readable-code-optimal-time-comp-xvuh

// #include <bit>
// #include <ranges>
// #include <vector>

namespace Util {
    inline auto constexpr kDummySubsetCount{1};
    inline auto constexpr kMaxNum{static_cast<unsigned int>(1e5)};
    inline auto constexpr kMaxNumBitSz{std::bit_ceil(kMaxNum)};
}

class Solution {
public:
// let 'n' be a count of the given numbers
// 's' - OR sum of the all given numbers 
// 'm' - smallest integral power of 2 not less than the masimum possible input number 
// time complexity O(n * s)
// space complexity O(max)
// runtime 83 ms, beats 24.32 %
    [[nodiscard]] 
    int countMaxOrSubsets(std::vector<int> const & nums_) const;
};

int Solution::countMaxOrSubsets(std::vector<int> const & nums_) const {
    namespace views = std::views;
    using namespace Util;
    auto maxOrVal{0};
    auto subsetCountsAtOrVals(std::array<int, kMaxNumBitSz>{});
    subsetCountsAtOrVals.at(0) = kDummySubsetCount;
    for(auto const num: nums_) {
        for(auto const currOrVal: 
                views::iota(0, maxOrVal + 1) |
                views::reverse
        ) {
            auto const nextOrVal{currOrVal | num};
            subsetCountsAtOrVals.at(nextOrVal) +=
                subsetCountsAtOrVals.at(currOrVal);
        }
        maxOrVal |= num;
    }
    return subsetCountsAtOrVals.at(maxOrVal);
}
