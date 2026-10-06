// problem : https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/description/
// submission : https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/submissions/2164045500
// solution post : https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/solutions/8558825/
//  simplanation-simple-explanation-by-cyber-jgpy

// Approach : Greedy State Accumulation
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
// #include <string>
// #include <string_view>

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

constexpr auto kOpenParen{'('};

// 1. Define state variables to track unmatched opens and required closing additions.
struct ParenState final {
    int unmatchedOpenCnt{};
    int additionCnt{};
};

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
    auto minAddToMakeValid(std::string_view parens_) -> int;
};

auto Solution::minAddToMakeValid(std::string_view parens_) -> int {
    // 2. Define state transition function to evaluate moves for each parenthesis.
    auto const cntMinAddtions{[] (auto const accumState, auto const paren_) -> ParenState
        {
            auto const [unmatchedOpenCnt, additionCnt]{accumState};

            // 3. Register a new opening parenthesis that needs a future match.
            if(paren_ == kOpenParen) {
                return {unmatchedOpenCnt + 1, additionCnt};
            } 

            // 4. Record a missing opening parenthesis to match the current closing one.
            if(unmatchedOpenCnt == 0) {
                return {0, additionCnt + 1};
            }        

            // 5. Match the current closing parenthesis with an available open one.
            return {unmatchedOpenCnt - 1, additionCnt};
        }
    };

    // 6. Traverse the sequence folding individual character states into the final state.
    auto const [unmatchedOpenCnt, additionCnt]{
        rs::fold_left(parens_, ParenState{}, cntMinAddtions)};

    // 7. Sum the remaining unmatched open parentheses and the recorded missing additions.
    return unmatchedOpenCnt + additionCnt;
}
