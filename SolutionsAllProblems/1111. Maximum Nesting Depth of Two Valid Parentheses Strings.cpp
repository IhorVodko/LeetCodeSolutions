// problem : https://leetcode.com/problems/maximum-nesting-depth-of-two-valid-parentheses-strings/description
// submission : https://leetcode.com/problems/maximum-nesting-depth-of-two-valid-parentheses-strings/submissions/2158118435
// solution post : https://leetcode.com/problems/maximum-nesting-depth-of-two-valid-parentheses-strings/solutions/8548538/
//  simplanation-simple-explanation-by-cyber-7tbp

// Approach : Index Parity Depth Distribution
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the string length
// Time :  O(n)
// Space : O(1), auxiliary space

// import std;

// #include <ios>
// #include <iostream>
// #include <ranges>
// #include <string_view>
// #include <vector>

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

constexpr auto kOpenParenthesis{'('};
constexpr auto kGroupA{0};
constexpr auto kGroupB{1};

// Optimize standard I/O stream operations performance.
[[maybe_unused]]
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// Evaluates if the character signifies an increase in nesting depth.
constexpr auto isOpen{[] [[nodiscard]] (auto const paren_) {
    return paren_ == kOpenParenthesis;
}};

// Checks parity to uniformly distribute adjacent nested depths across groups.
constexpr auto isEven{[] [[nodiscard]] (auto const idx_) {
    return idx_ % 2 == 0;
}};

// 1. Assign parenthesis to a target sequence based on its index parity and type.
constexpr auto group{[] [[nodiscard]] (auto const idxAndParen_) {
    auto const [idx, paren]{idxAndParen_};

    return isOpen(paren) == isEven(idx) ? kGroupA : kGroupB;
}};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    static auto maxDepthAfterSplit(
        std::string_view const parentheses_
    ) -> std::vector<int>;
};

auto Solution::maxDepthAfterSplit(
    std::string_view const parentheses_
) -> std::vector<int> {
    // 2. Pair each parenthesis with its index and map to a target subsequence.
    auto groupedParens{parentheses_ | vs::enumerate | vs::transform(group)};

    return rs::to<std::vector>(groupedParens);
}
