// problem : https://leetcode.com/problems/minimum-distance-to-type-a-word-using-two-fingers/description
// submission : https://leetcode.com/problems/minimum-distance-to-type-a-word-using-two-fingers/submissions/1977229112
// solution post : https://leetcode.com/problems/minimum-distance-to-type-a-word-using-two-fingers/solutions/7890297/
//    c-modern-readable-code-beats-100-runtime-cypx

// Approach : 2D Dynamic Programming (State Optimization)
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the word length
// 'M' - character set size
// complexity :  O(n * M)
// complexity : O(n * M)

// import std;

namespace {

// Compile-time initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    auto minimumDistance(std::string_view const word_) const  -> int;

private:
    // Calculates Manhattan distance between two keys on a 6-column grid
    [[nodiscard]]
    inline auto CalcDist(
        int const idx1_,
        int const idx2_
    ) const noexcept -> int;

    // Converts a character to its 0-indexed integer equivalent
    [[nodiscard]]
    inline auto ChrToIdx(char const chr_) const noexcept -> int;

    static auto constexpr kChrSetSz{26};
    static auto constexpr kChrSetFirst{'A'};
    static auto constexpr kColsCnt{6};
};

auto Solution::minimumDistance(std::string_view const word_) const  -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    using intLim = std::numeric_limits<int>;

    auto const wordSz{std::ssize(word_)};
    auto minDist{intLim::max()};
    // dp[i1][i2] tracks min distance up to char i1 with the non-typing finger resting
    // on char i2
    auto dp{std::vector<std::vector<int>>(
        wordSz, std::vector<int>(kChrSetSz, intLim::max() / 2))};

    rngs::fill(dp.front(), 0);

    for(auto const i1: vs::iota(1, wordSz)) {
        auto const prevIdx{ChrToIdx(word_[i1 - 1])};
        auto const currIdx{ChrToIdx(word_[i1])};
        auto const currDist1{CalcDist(prevIdx, currIdx)};

        for(auto const i2: vs::iota(0, kChrSetSz)) {
            // Keep the resting finger at i2 and move the typing finger from prevIdx to currIdx
            dp[i1][i2] = std::min(dp[i1][i2], dp[i1 - 1][i2] + currDist1);

            // Move the resting finger to currIdx; previous typing finger becomes the
            // new resting finger (i2)
            if(prevIdx == i2) {
                for(auto const i3: vs::iota(0, kChrSetSz)) {
                    auto const currDist2{CalcDist(i3, currIdx)};

                    dp[i1][i2] = std::min(dp[i1][i2], dp[i1 - 1][i3] + currDist2);
                }
            }

            if(i1 + 1 == wordSz) {
                minDist = std::min(minDist, dp[i1][i2]);
            }
        }
    }

    return minDist;
}

// Calculates Manhattan distance between two keys on a 6-column grid
auto Solution::CalcDist(
    int const idx1_,
    int const idx2_
) const noexcept -> int {
    auto const x1{idx1_ / kColsCnt};
    auto const y1{idx1_ % kColsCnt};
    auto const x2{idx2_ / kColsCnt};
    auto const y2{idx2_ % kColsCnt};
    auto const dist{std::abs(x1 - x2) + std::abs(y1 - y2)};
    return dist;
}

// Converts a character to its 0-indexed integer equivalent
auto Solution::ChrToIdx(char const chr_) const noexcept -> int {
    auto const idx{chr_ - kChrSetFirst};
    return idx;
}
