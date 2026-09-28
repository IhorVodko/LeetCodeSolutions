// problem : https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses/description
// submission : https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses/submissions/2155949355
// solution post : https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses/solutions/8544829/
//  simplanation-simple-explanation-by-cyber-3h4z/

// Approach : Sequential State Accumulation
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the expression length
// Time :  O(n)
// Space : O(1)

// import std;

// #include <algorithm>
// #include <ios>
// #include <iostream>
// #include <ranges>
// #include <string_view>

namespace {

namespace vs = std::views;
namespace rs = std::ranges;

// Tokens denoting changes in current nesting depth
constexpr auto kOpenParenthesis{'('};
constexpr auto kCloseParenthesis{')'};

// Optimize standard I/O stream operations performance.
[[maybe_unused]]
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// Tracks running states across the folded string sequence
struct NestingDepth {
    int currDepth{};
    int maxDepth{};
};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    static auto maxDepth(std::string_view const exp_) -> int;
};

auto Solution::maxDepth(std::string_view const exp_) -> int {
    constexpr auto processChr{[] (
        auto const nestingDepth_,
        auto const chr_
    ) static -> NestingDepth {
        auto const [currDepth, maxDepth]{nestingDepth_};

        // 1. Enter a deeper nesting level when an open parenthesis is encountered.
        if(chr_ == kOpenParenthesis) {
            // 2. Register the maximum depth achieved across all valid scopes so far.
            return {currDepth + 1, std::max(currDepth + 1, maxDepth)}; 
        } else if(chr_ == kCloseParenthesis) {
            // 3. Exit the current nesting level when a close parenthesis is encountered.
            return {currDepth - 1, maxDepth};
        }

        // 4. Maintain the current state for non-parenthesis characters.
        return nestingDepth_;
    }};

    // 5. Traverse expression sequentially and extract the peak nesting depth.
    return rs::fold_left(exp_, NestingDepth{}, processChr).maxDepth;
}
