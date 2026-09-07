// problem : https://leetcode.com/problems/distinct-subsequences-ii/description
// submission : https://leetcode.com/problems/distinct-subsequences-ii/submissions/2133962421
// solution post : https://leetcode.com/problems/distinct-subsequences-ii/solutions/8507606/simplanation-simple-explanation-by-cyber-p5og

// Approach : Dynamic Programming & Duplicates Pruning
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the sting length
// Time :  O(n)
// Space : O(1)

// import std;

// #include <array>
// #include <ios>
// #include <iostream>
// #include <ranges>
// #include <string_view>

// #include <cstddef>

namespace {

namespace vs = std::views;

constexpr auto kMod{1'000'000'007uz};
constexpr auto kEmptySubseqCnt{1uz};
constexpr auto kChrSetSz{26uz};
constexpr auto kChrSetFirst{'a'};

// Maps lowercase letters to zero-indexed array positions
constexpr auto toIdx{[] [[nodiscard]] (auto const chr_) {
    return static_cast<std::size_t>(chr_ - kChrSetFirst);
}};

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
    static auto distinctSubseqII(std::string_view const str_) -> int;
};

auto Solution::distinctSubseqII(std::string_view const str_) -> int {
    // Tracks subsequence counts strictly ending with a specific alphabet character
    auto dpSubseqCnts{std::array<std::size_t, kChrSetSz>{}};
    // Running total of all globally distinct non-empty subsequences formed so far
    auto subseqFinalCnt{0uz};

    // 1. Process string characters sequentially as mapped index values
    for (auto const chrIdx : str_ | vs::transform(toIdx)) {
        // 2. Count new subsequences by appending current character to existing ones
        auto const subseqNextCnt{(subseqFinalCnt + kEmptySubseqCnt) % kMod};

        // 3. Incorporate new combinations and deduct overlaps ending with same character
        subseqFinalCnt =
            (subseqFinalCnt + subseqNextCnt - dpSubseqCnts[chrIdx] + kMod) % kMod;
        // 4. Register newly minted combinations as historical count for this character
        dpSubseqCnts[chrIdx] = subseqNextCnt;
    }

    return static_cast<int>(subseqFinalCnt);
}
