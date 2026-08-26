// problem : https://leetcode.com/problems/shortest-and-lexicographically-smallest-beautiful-string/description
// submission : https://leetcode.com/problems/shortest-and-lexicographically-smallest-beautiful-string/submissions/2120977911
// solution post : https://leetcode.com/problems/shortest-and-lexicographically-smallest-beautiful-string/solutions/8484536/
//    simplanation-simple-explanation-by-cyber-xuvh

// Approach : Sliding Window with State Folding
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the string length
// 'm' - required number of ones
// Time :  O(n * m)
// Space : O(1), auxiliary

// import std;

// #include <string>
// #include <string_view>
// #include <algorithm>
// #include <ranges>
// #include <utility>
// #include <ios>
// #include <iostream>

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

constexpr auto kChrOne{'1'};
constexpr auto kInclusiveOffset{1uz};

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// Tracks sliding window boundaries and best result found so far
struct WindowState {
    std::string_view optimalSubstr;
    std::size_t leftIdx{};
    int onesCnt{0};
};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    static auto shortestBeautifulSubstring(
        std::string_view const str_,
        int const targetOnesCnt_
    ) -> std::string;
};

auto Solution::shortestBeautifulSubstring(
    std::string_view const str_,
    int const targetOnesCnt_
) -> std::string {

    auto const updateWindowState{[=] (auto state_, auto const idxAndChr_) {
        auto const [rightIdx, chr]{idxAndChr_};
        auto & [optimalSubstr, leftIdx, onesCnt]{state_};

        // 1. Expand window by incorporating current character
        if(chr == kChrOne) {
            ++onesCnt;
        }

        // 2. Shrink window if ones count exceeds target
        if(onesCnt > targetOnesCnt_) {
            // Previous leftIdx always points to '1', skipping it removes one '1'
            ++leftIdx;
            --onesCnt;
        }

        // 3. Attempt to update optimal substring when target is reached
        if(onesCnt == targetOnesCnt_) {
            // Strip leading zeros to ensure shortest possible valid window
            leftIdx = str_.find(kChrOne, leftIdx);

            auto const windowLen{
                static_cast<std::size_t>(rightIdx) - leftIdx + kInclusiveOffset
            };
            auto const currSubstr{str_.substr(leftIdx, windowLen)};

            // 4. Update optimal if current is shorter or lexicographically smaller
            if( optimalSubstr.empty() ||
                std::pair{currSubstr.length(), currSubstr} <
                    std::pair{optimalSubstr.length(), optimalSubstr}
            ) {
                optimalSubstr = currSubstr;
            }
        }

        return state_;
    }};

    // 5. Fold over all characters to process sliding window state transitions
    auto const finalState{rs::fold_left(
        str_ | vs::enumerate,
        WindowState{},
        updateWindowState
    )};

    return std::string{finalState.optimalSubstr};
}
