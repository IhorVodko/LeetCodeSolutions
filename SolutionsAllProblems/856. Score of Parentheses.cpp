// problem : https://leetcode.com/problems/score-of-parentheses/description/
// submission : https://leetcode.com/problems/score-of-parentheses/submissions/2163088161
// solution post : https://leetcode.com/problems/score-of-parentheses/solutions/8557023/simplanation-simple-explanation-by-cyber-y7vl

// Approach : Depth-based Accumulation
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
// #include <cstddef>

namespace {

namespace rs = std::ranges;

constexpr auto kOpenParen{'('};
constexpr auto kBaseMult{1u};

// Optimize standard I/O stream operations performance.
[[maybe_unused]]
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// Track string sequence context to calculate parenthesis values.
struct FoldState final {
    unsigned depth{0};
    unsigned score{0};
    char prevChr{'\0'};
};

}; // namespace 

class Solution final {
public:
    [[nodiscard]]
    static auto scoreOfParentheses(std::string_view const brackets_) -> int;
};

auto Solution::scoreOfParentheses(std::string_view const brackets_)-> int {
    const auto calculateScore{[] (
        FoldState const accumState_,
        char const currChr_
    ) -> FoldState {
        auto [depth, score, prevChr]{accumState_};

        if(currChr_ == kOpenParen) {
            // 1. Track increasing nesting depth which doubles the inner pair score.
            ++depth;

        // if currChr_ is a close parenthesis
        } else {
            // 2. Step out of the current nesting level.
            --depth;

            if(prevChr == kOpenParen) {
                // 3. A core pair contributes directly to the total sum based on its depth.
                score += kBaseMult << depth;
            }
        }

        return {depth, score, currChr_};
    }};

    // 4. Process all parentheses sequentially to accumulate the total score.
    auto const finalState{rs::fold_left(brackets_, FoldState{}, calculateScore)};

    return static_cast<int>(finalState.score);
}
