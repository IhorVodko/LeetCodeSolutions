// problem : https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/description/
// submission : https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/submissions/
//    1681572584
// solution post : https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/solutions/
//    6903304/c-modern-readable-code-beats-100-runtime-80y3

// #include <array>
// #include <ranges>
// #include <vector>

namespace Util {
    inline auto constexpr kMod{static_cast<int>(1e9) + 7};
    inline auto constexpr kNumsMaxSz{static_cast<size_t>(1e5)};
    inline constexpr auto PrecomputePowersOf2() {
        auto powers{std::array<int, kNumsMaxSz>{}};
        powers.at(0) = 1;
        for(auto idx{1u}; idx < kNumsMaxSz; ++idx) {
            powers.at(idx) = (powers.at(idx - 1) * 2) %kMod;
        }
        return powers;
    }
    inline auto constexpr kPowersOf2{PrecomputePowersOf2()};
}

class Solution {
public:
    using numsT = std::vector<int>;
// let 'n' be a count of the given numbers
// time complexity O(n * log2(n))
// space complexity O(n)
// runtime 27 ms, beats 84.83 %
    int numSubseq(
        numsT & nums_,
        int const sumMax_
    ) const;
};

int Solution::numSubseq(
    numsT & nums_,
    int const sumMax_
) const {
    using namespace Util;
    namespace ranges = std::ranges;
    auto numsSz{nums_.size()};
    ranges::sort(nums_);
    auto subseqsCount{0};
    for(auto leftNumIdx{0}, rightNumIdx{static_cast<int>(numsSz) - 1};
        leftNumIdx <= rightNumIdx;
    ) {
        if(nums_.at(leftNumIdx) + nums_.at(rightNumIdx) <= sumMax_) {
            subseqsCount += kPowersOf2.at(rightNumIdx - leftNumIdx);
            subseqsCount %= kMod;
            ++leftNumIdx;
        } else {
            --rightNumIdx;
        }
    }
    return subseqsCount;
}
