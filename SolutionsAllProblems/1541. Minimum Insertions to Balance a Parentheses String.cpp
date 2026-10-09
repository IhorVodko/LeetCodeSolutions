// problem : https://leetcode.com/problems/minimum-insertions-to-balance-a-parentheses-string/description
// submission : https://leetcode.com/problems/minimum-insertions-to-balance-a-parentheses-string/submissions/2167469133
// solution post : https://leetcode.com/problems/minimum-insertions-to-balance-a-parentheses-string/solutions/8564626/
//    simplanation-simple-explanation-by-cyber-g4x6

// Approach : Greedy Single-Pass State Folding
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the input string length
// Time :  O(n)
// Space : O(1)

// import std;

// #include <algorithm>
// #include <concepts>
// #include <ios>
// #include <iostream>
// #include <string_view>

namespace rs = std::ranges;

namespace {

// Maps structural constants for parentheses balancing rules.
constexpr auto kOpenParen{'('};
constexpr auto kCloseParensPerOpenParen{2};

// Identifies asymmetrical pending close parenthesis requirements.
constexpr auto isOdd{[] [[nodiscard]] (std::integral auto const num_) {
    return num_ % 2 != 0;
}};

// Tracks running totals of injected characters and expected closures.
struct ParenState final {
    int insertCnt{};
    int neededCloseParenCnt{};
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

}; // namespace

class Solution final {
public:
    [[nodiscard]]
    static auto minInsertions(std::string_view const parens_) -> int;
};

auto Solution::minInsertions(std::string_view const parens_) -> int {
    constexpr auto cntMinInserts{[] [[nodiscard]] (
        ParenState const foldState_,
        char const paren_
    ) -> ParenState {
        auto [insertCnt, neededCloseParenCnt]{foldState_};
        // 1. Evaluate encountered open parenthesis against pending closure state.
        if(paren_ == kOpenParen) {
            // 2. Resolve trailing odd close parenthesis by forcing an insertion.
            if(isOdd(neededCloseParenCnt)) {
                return {insertCnt + 1, neededCloseParenCnt + 1};
            } else {
                // 3. Register the requirement for a new double close parenthesis.
                return {insertCnt, neededCloseParenCnt + kCloseParensPerOpenParen};
            }
        // 4. Fulfill unmatched close parenthesis by inserting a virtual open one.
        } else if(neededCloseParenCnt == 0) {
            return {insertCnt + 1, 1};
        }

        // 5. Consume one pending close parenthesis from the expected quota.
        return {insertCnt, neededCloseParenCnt - 1};
    }}; 

    // 6. Reduce the string sequence into the final insertion and pending state.
    auto const [insertCnt, neededCloseParenCnt]{
        rs::fold_left(parens_, ParenState{}, cntMinInserts)};

    // 7. Combine previous insertions with any remaining unclosed parentheses.
    return insertCnt + neededCloseParenCnt;
}
