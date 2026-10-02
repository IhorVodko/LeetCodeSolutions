// problem : https://leetcode.com/problems/generate-parentheses/description
// submission : https://leetcode.com/problems/generate-parentheses/submissions/2160193381
// solution post : https://leetcode.com/problems/generate-parentheses/solutions/8552084/simplanation-simple-explanation-by-cyber-bwwx

// Approach : Iterative Depth-First Search (DFS) via Explicit Stack
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the nput integer representing the total number of allowed bracket pairs
// 'm' - n-th Catalan number, calculating the total number of mathematically valid combinations C(n)
// Time :  O(n * m)
// Space : O(n)

// import std;

// #include <ios>
// #include <iostream>
// #include <ranges>
// #include <stack>
// #include <string>
// #include <vector>

namespace {

using Comb  = std::string;
using Combs = std::vector<Comb>;

constexpr auto kOpenBracket {'('};
constexpr auto kCloseBracket{')'};
constexpr auto kPlaceholder {'\0'};

// Represents the DFS traversal state at a specific depth
struct CombState final {
    short   openBracketAvailableCnt;
    short   closeBracketAvailableCnt;
    short   combLen;
    char    bracket;
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
    static auto generateParenthesis(int const bracketPairTot_) -> Combs;
};

auto Solution::generateParenthesis(int const bracketPairTot_) -> Combs {
    // Return empty result for invalid pair counts
    if(bracketPairTot_ <= 0) {
        return {};
    }

    auto const  validCombLen{bracketPairTot_ * 2};
    auto        validCombs  {Combs{}};
    // 1. Allocate fixed-size combination string to prevent allocations during traversal
    auto        comb        {Comb(bracketPairTot_ * 2, ' ')};

    // 2. Initialize DFS stack containing the starting simulation state
    auto combStates{std::stack<CombState, std::vector<CombState>>{}};
    combStates.emplace(bracketPairTot_, bracketPairTot_, 0, kPlaceholder);

    // 3. Traverse the state space until all valid branches are exhausted
    while(!combStates.empty()) {
        auto const [openBracketAvailableCnt, closeBracketAvailableCnt, combLen, bracket]{
            combStates.top()};
        combStates.pop();

        // Record the bracket choice at the current depth
        if(bracket != kPlaceholder) {
            comb[combLen - 1] = bracket;
        }

        // 4. Capture combination when the target sequence length is achieved
        if(combLen == validCombLen) {
            validCombs.emplace_back(comb);
            continue;
        }

        // 5. Branch into adding a close bracket if it maintains sequence validity
        if(closeBracketAvailableCnt > openBracketAvailableCnt) {
            combStates.emplace( openBracketAvailableCnt, closeBracketAvailableCnt - 1,
                                combLen + 1, kCloseBracket);
        }

        // 6. Branch into adding an open bracket if quota allows
        if(openBracketAvailableCnt > 0) {
            combStates.emplace( openBracketAvailableCnt - 1, closeBracketAvailableCnt,
                                combLen + 1, kOpenBracket);
        }
    } 
    
    return validCombs;
}
