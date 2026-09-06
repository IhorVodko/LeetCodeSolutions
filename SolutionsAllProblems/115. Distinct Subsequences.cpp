// problem : https://leetcode.com/problems/distinct-subsequences/description
// submission : https://leetcode.com/problems/distinct-subsequences/submissions/2133047554
// solution post : https://leetcode.com/problems/distinct-subsequences/solutions/8506049/simplanation-simple-explanation-by-cyber-18y9

// Approach : Space-Optimized Dynamic Programming (1D DP)
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the source string length
// 'm' - target string length
// Time :  O(n * m)
// Space : O(m)

// import std;

// #include <algorithm>
// #include <ios>
// #include <iostream>
// #include <ranges>
// #include <string>
// #include <vector>

// #include <cstddef>
// #include <cstdint>

namespace {

namespace vs = std::views;

constexpr auto kEmptyPrefIdx{0uz};
constexpr auto kInitialMatchCnt{1uz};
constexpr auto kLenOffset{1uz};

// Initializer to configure fast I/O before main() runs
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
    static auto numDistinct(
        std::string_view srcStr_,
        std::string_view trgtStr_
    ) -> int;
};

auto Solution::numDistinct(
    std::string_view srcStr_,
    std::string_view trgtStr_
) -> int {
    auto const trgtLen_{trgtStr_.size()};

    // 1. Initialize DP table where dp[i] is valid subsequences for target prefix length
    //  i.
    auto dpMatchCnts{std::vector<size_t>(trgtLen_ + kLenOffset)};
    // Empty target prefix is always matched exactly once by any source prefix.
    dpMatchCnts[kEmptyPrefIdx] = kInitialMatchCnt;

    // 2. Process each source character incrementally to build matching subsequences.
    for(auto const [srcIdx, srcChr]: srcStr_ | vs::enumerate) {
        // Bound target search length by available source characters to prevent
        //  over-reach.
        auto const matchLen{std::min(srcIdx + kLenOffset, trgtLen_)};

        // 3. Traverse target prefixes backwards to avoid overwriting current step
        //  results.
        for(auto const [trgtIdx, trgtChr]:
            trgtStr_ | vs::take(matchLen) | vs::enumerate | vs::reverse
        ) {
            // 4. On match, accumulate combinations forming prefix without current
            //  character.
            if(srcChr == trgtChr) {
                dpMatchCnts[trgtIdx + kLenOffset] += dpMatchCnts[trgtIdx];
            }
        }
    }

    // 5. Return accumulated valid combinations matching the entire target string.
    return static_cast<int>(dpMatchCnts[trgtLen_]);
}
