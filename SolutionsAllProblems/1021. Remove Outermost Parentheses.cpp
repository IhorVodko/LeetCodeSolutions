// problem : https://leetcode.com/problems/remove-outermost-parentheses/description
// submission : https://leetcode.com/problems/remove-outermost-parentheses/submissions/2166541354
// solution post : https://leetcode.com/problems/remove-outermost-parentheses/solutions/8563077/simplanation-simple-explanation-by-cyber-fl9p

// Approach : Counter-based Depth Tracking
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the input string length
// Time :  O(n)
// Space : O(1)

// import std;

// #include <algorithm>
// #include <ios>
// #include <iostream>
// #include <ranges>
// #include <string>
// #include <string_view>
// #include <utility>

namespace rs = std::ranges;
namespace vs = std::views;

namespace {

constexpr auto kOpenParen{'('};
constexpr auto kCloseParen{')'};
constexpr auto kMinValidSize{2uz};

// Optimize standard I/O stream operations performance.
[[maybe_unused]]
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

struct State final {
    std::string parens;
    int depth{};
};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    static auto removeOuterParentheses(std::string_view const parensIn_) -> std::string;
};

auto Solution::removeOuterParentheses(std::string_view const parensIn_) -> std::string {
    // 1. Return empty directly if input lacks enough characters for a primitive.
    if(parensIn_.size() <= kMinValidSize) {
        return {};
    }

    // 2. Define fold operation to accumulate inner primitives based on depth state.
    const auto removeOuterParens{[] (auto foldState_, auto const paren_) -> State {
        auto [parens, depth]{std::move(foldState_)};

        // Adjust outer boundary condition dynamically for closing parenthesis.
        if(paren_ == kCloseParen) {
            --depth;
        }

        // 3. Keep current parenthesis only if nested inside a valid primitive block.
        if(depth > 0) {
            parens += paren_;
        }

        // Adjust outer boundary condition dynamically for opening parenthesis.
        if(paren_ == kOpenParen) {
            ++depth;
        }

        return {std::move(parens), depth}; 
    }}; 

    auto initState{State{}};
    initState.parens.reserve(parensIn_.size());

    // 4. Extract valid primitive components by folding over the original string.
    auto parensOut{
        rs::fold_left(parensIn_, std::move(initState), removeOuterParens).parens};
    parensOut.shrink_to_fit();

    return parensOut;
}
