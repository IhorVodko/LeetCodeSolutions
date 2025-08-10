// problem : https://leetcode.com/problems/reordered-power-of-2/description
// submission : https://leetcode.com/problems/reordered-power-of-2/submissions/1730316009
// solution post : https://leetcode.com/problems/reordered-power-of-2/solutions/7065273/
//    c-modern-readable-code-beats-100-runtime-hn1r

// #include <array>
// #include <bit>
// #include <ranges>

namespace Util {
    inline auto constexpr kRadix{10u};
    inline auto constexpr kMaxNum{static_cast<size_t>(1e9)};
    inline auto constexpr kMaxPow{std::bit_width(kMaxNum)};

    using arr1T = std::array<size_t, kRadix>;
    using arr2T = std::array<arr1T, kMaxPow + 1>;

    constexpr void CountDigits(
        arr1T & digitCounts_,
        size_t const num_
    ) {
        auto num{num_};
        while(num > 0) {
            auto const lastDigit{num % kRadix};
            ++digitCounts_.at(lastDigit);
            num /= kRadix;
        }
    }
 
    consteval arr2T PrecomputePowOf2DigitCounts() {
        namespace views = std::views;
        auto powOf2DigitCounts{arr2T{}};
        for(auto const pow: views::iota(0, kMaxPow)) {
            auto & digitCounts{powOf2DigitCounts.at(pow)};
            auto num{1 << pow};
            CountDigits(digitCounts, num);
        }
        return powOf2DigitCounts;
    }

    inline auto constexpr kPowOf2DigitCounts{PrecomputePowOf2DigitCounts()};
}

class Solution {
public:
// let 'n' a max possible given number
// time complexity O(log2(n) * log10(n))
// space complexity O(log2(n) * log10(n))
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    bool reorderedPowerOf2(int const num_) const;
};

bool Solution::reorderedPowerOf2(int const num_) const {
    namespace ranges = std::ranges;
    using namespace Util;
    auto digitCounts{arr1T{}};
    CountDigits(digitCounts, num_);
    for(auto const & powOf2DigitCounts: kPowOf2DigitCounts) {
        if(digitCounts == powOf2DigitCounts) {
            return true;
        }
    }
    return false;
}
