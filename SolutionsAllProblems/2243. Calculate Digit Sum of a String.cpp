// problem : https://leetcode.com/problems/calculate-digit-sum-of-a-string/description
// submission : https://leetcode.com/problems/calculate-digit-sum-of-a-string/submissions/2197481627
// solution post : https://leetcode.com/problems/calculate-digit-sum-of-a-string/solutions/8615072/
//    simplanation-simple-explanation-by-cyber-t4je

// Approach : Iterative Chunk-and-Sum Reduction
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the string length
// Time :  O(n)
// Space : O(n)

// import std;

// #include <algorithm>
// #include <charconv>
// #include <functional>
// #include <ios>
// #include <iostream>
// #include <iterator>
// #include <ranges>
// #include <string>

namespace rs = std::ranges;
namespace vs = std::views;

namespace {

// Max group digit sum is 9 * 100 = 900 (at most 3 digits).
constexpr auto kMaxSumLen{3};
constexpr auto kChrDigitZero{'0'};
constexpr auto kChrDefault{'\0'};

constexpr auto toDigit{[] [[nodiscard]] (char const chrDigit_) noexcept -> int {
    return chrDigit_ - kChrDigitZero;
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
    static auto digitSum(
        std::string numStr_,
        int const lenLimit_
    ) -> std::string; 
};

auto Solution::digitSum(
    std::string numStr_,
    int const lenLimit_
) -> std::string {
    // Reduces one digit group to its decimal sum string.
    const auto calcSum{[] (auto && numStr_) {
        auto const sum{rs::fold_left(numStr_ | vs::transform(toDigit), 0, std::plus{})};

        // Pre-sized buffer holds any group sum up to 900 without reallocation.
        auto buff{std::string(kMaxSumLen, kChrDefault)};
        auto const buffBegin{buff.data()};
        auto const buffEnd{buff.data() + buff.size()};
        
        auto const res{std::to_chars(buffBegin, buffEnd, sum)};
        auto const writtenBuffLen{res.ptr - buffBegin};

        buff.resize(writtenBuffLen);

        return buff;
    }};

    // 1. Repeat rounds while the digit string exceeds the target length limit.
    while(std::ssize(numStr_) > lenLimit_) {
        numStr_ = 
            numStr_ |
            // 2. Partition the string into consecutive groups of up to lenLimit_.
            vs::chunk(lenLimit_) |
            // 3. Replace each digit group with its decimal digit sum string.
            vs::transform(calcSum) |
            // 4. Concatenate all group sum strings into the next round's string.
            vs::join |
            rs::to<std::string>()
        ;
    }

    // 5. Return the final string once its length is within lenLimit_.
    return numStr_;
}
