// problem : https://leetcode.com/problems/valid-parentheses/description
// submission : https://leetcode.com/problems/valid-parentheses/submissions/2159404321
// solution post : https://leetcode.com/problems/valid-parentheses/solutions/8550721/simplanation-simple-explanation-by-cyber-mcl7

// Approach : LIFO Scope Resolution
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the expression length
// Time :  O(n)
// Space : O(n)

// import std;

// #include <ios>
// #include <iostream>
// #include <iostream>
// #include <stack>
// #include <string_view>
// #include <utility>
// #include <vector>

namespace {

// Map bracket identities and maximum pair composition block size.
constexpr auto kOpenBracketsType1   {'('};
constexpr auto kCloseBracketsType1  {')'};
constexpr auto kOpenBracketsType2   {'{'};
constexpr auto kCloseBracketsType2  {'}'};
constexpr auto kOpenBracketsType3   {'['};
constexpr auto kCloseBracketsType3  {']'};
constexpr auto kBracketPairSize     {2uz};

// Evaluate if character represents the start of a nested block.
constexpr auto isOpenBracket([] (auto const bracket_) {
    return 
        bracket_ == kOpenBracketsType1 ||
        bracket_ == kOpenBracketsType2 ||
        bracket_ == kOpenBracketsType3;
});

// Verify structural type consistency between two bracket boundaries.
constexpr auto isDifferentTypeBrackets([] (
    auto const bracket1_,
    auto const bracket2_
) {
    return !(
        (bracket1_ == kOpenBracketsType1 && bracket2_ == kCloseBracketsType1) ||
        (bracket1_ == kOpenBracketsType2 && bracket2_ == kCloseBracketsType2) ||
        (bracket1_ == kOpenBracketsType3 && bracket2_ == kCloseBracketsType3)
    );
});

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
    static auto isValid(std::string_view const brackets_) -> bool;
};

auto Solution::isValid(std::string_view const brackets_) -> bool {
    // 1. Resolve empty sequence base case immediately.
    if(brackets_.empty()) {
        return true;
    }

    // Restrict expected stack depth since valid expressions require character pairs.
    auto const maxValidDepth{brackets_.size() / kBracketPairSize};

    // Preallocate contiguous memory to prevent dynamic resizing overhead.
    auto buff{std::vector<char>{}};
    buff.reserve(maxValidDepth);

    // 2. Instantiate LIFO queue to maintain pending unresolved boundaries.
    auto bracketStk{std::stack<char, std::vector<char>>{std::move(buff)}};

    // 3. Traverse expression characters to sequentially resolve context scopes.
    for(auto const currBracket: brackets_) {
        if(isOpenBracket(currBracket)) {
            // 4. Record new block initiation for deferred resolution.
            bracketStk.emplace(currBracket);
            
            // Terminate early if pending blocks surpass possible closing pairs.
            if(bracketStk.size() > maxValidDepth) {
                return false;
            }

            continue;
        }

        // 5. Reject closure attempt when no structural block is currently open.
        if(bracketStk.empty()) {
            return false;
        }

        // 6. Extract the most recently established block for verification.
        auto const prevBracket{bracketStk.top()};
        bracketStk.pop();

        // 7. Fail validation if the closing boundary type mismatches the block type.
        if(isDifferentTypeBrackets(prevBracket, currBracket)) {  
            return false;
        }
    }

    // 8. Confirm all opened blocks have been properly terminated.
    return bracketStk.empty();
}
