// problem : https://leetcode.com/problems/smallest-subarrays-with-maximum-bitwise-or/description/
// submission : https://leetcode.com/problems/smallest-subarrays-with-maximum-bitwise-or/submissions/1716127166
// solution post : https://leetcode.com/problems/smallest-subarrays-with-maximum-bitwise-or/solutions/7021005
//    /c-modern-readable-code-beats-97-runtime-lgiun

// #include <algorithm>
// #include <array>
// #include <bit>
// #include <bitset>
// #include <limits>
// #include <vector>

namespace Util {
    inline auto constexpr kMaxNum{static_cast<unsigned>(1e9)};
    inline auto constexpr kMaxNumBitSz{std::bit_width(kMaxNum)};
    inline auto constexpr kPosDummy{std::numeric_limits<unsigned>::max()};
}

class Solution {
public:
// let 'n' be a count of the given numbers
// 'mL' - masimum number of the given numbers
// 'mG' - maximum possible given number
// time complexity O(n * log2(mL)
// space complexity O(log2(mG))
// runtime 9 ms, beats 96.55 %
    [[nodiscard]]
    std::vector<int> smallestSubarrays(std::vector<int> const & nums_) const;
};

std::vector<int> Solution::smallestSubarrays(
    std::vector<int> const & nums_
) const {
    namespace ranges = std::ranges;
    namespace views = std::views;
    using namespace Util;
    auto const numsSz{nums_.size()};
    auto pos{std::array<unsigned, kMaxNumBitSz>{}};
    pos.fill(kPosDummy);
    auto minSubarrSzs{std::vector<int>(numsSz, 0)};
    auto const maxNum{static_cast<unsigned>(*std::ranges::max_element(nums_))};
    auto maxNumBitSz{std::bit_width(maxNum)};
    auto num{std::bitset<kMaxNumBitSz>{}};
    for(auto const numIdx: views::iota(0u, numsSz) | views::reverse) {
        num = static_cast<unsigned>(nums_.at(numIdx));
        auto maxBitIdx{numIdx};
        for(auto const bitIDx: views::iota(0, maxNumBitSz)) {
            if(num.test(bitIDx)) {
                pos.at(bitIDx) = numIdx;
            } else if(pos.at(bitIDx) != kPosDummy) {
                maxBitIdx = std::max(maxBitIdx, pos.at(bitIDx));
            }
        }
        auto const minSubarrSz{maxBitIdx - numIdx + 1};
        minSubarrSzs.at(numIdx) = minSubarrSz;
    }
    return minSubarrSzs;
}
