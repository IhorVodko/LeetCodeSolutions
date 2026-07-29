// problem : https://leetcode.com/problems/smallest-palindromic-rearrangement-ii/description/
// submission : https://leetcode.com/problems/smallest-palindromic-rearrangement-ii/submissions/2086464965
// solution post : https://leetcode.com/problems/smallest-palindromic-rearrangement-ii/solutions/8428852/
//    simplanation-simple-explanation-on-time-99y1q

// Approach : Combinatorial Prefix-Suffix Splitting
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the string length
// Time :  O(n)
// Space : O(1), auxiliary space

// import std;

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

// Defines alphabetical bounds for frequency tracking.
constexpr auto kChrSetSz{26uz};
constexpr auto kChrSetFirst{'a'};

// Maps a character to its 0-indexed alphabetical position.
constexpr auto toIdx{[] (char const chr_) {
    return static_cast<size_t>(chr_ - kChrSetFirst);
}};

// Maps a 0-indexed position back to its ASCII character.
constexpr auto toChr{[] (size_t const idx_) {
    return static_cast<char>(idx_ + kChrSetFirst);
}};

// Safely calculates (base * multiplier) / divisor without overflow.
// Uses GCD to reduce factors prior to multiplication.
constexpr auto calcNextPermCnt{
    [] (size_t const base_, size_t const mult_, size_t const div_) {
        auto const gcd{std::gcd(base_, div_)};
        auto const reducedBase{base_ / gcd};
        auto const reducedDiv{div_ / gcd};
        
        return reducedBase * (mult_ / reducedDiv);
    }
};

// Initializer to configure fast I/O before main() runs
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
    static auto smallestPalindrome(
        std::string & str_, 
        long long targetRank_
    ) -> std::string;
};

auto Solution::smallestPalindrome(
    std::string & str_, 
    long long targetRank_
) -> std::string {
    auto const len{str_.size()};

    // Handle trivial lengths directly without further processing.
    if(len <= 3) {
        return targetRank_ > 1 ? ""s : str_;
    }
    
    auto const halfLen{len / 2};

    // Count character frequencies for the first half of the string.
    auto chrPairCnts{std::array<size_t, kChrSetSz>{}};
    for(auto const chr: str_ | vs::take(halfLen)) {
        ++chrPairCnts[toIdx(chr)];
    }

    auto trgtRnk{static_cast<size_t>(targetRank_)};
    auto curPermCnt{1uz};
    auto sufLen{0uz};
    auto splitChrPrefCnt{0uz};
    auto splitIdx{kChrSetSz};

    // 1. Find the shortest suffix needed to reach at least 'targetRank' permutations
    for(auto chrIdx: vs::iota(0uz, kChrSetSz) | vs::reverse) {
        auto isThresholdReached{false};

        for(auto const step: vs::iota(1uz, chrPairCnts[chrIdx] + 1)) {
            ++sufLen;

            // Updates permutations dynamically as the variable suffix expands in O(1).
            curPermCnt = calcNextPermCnt(curPermCnt, sufLen, step);

            // Handles cases (like targetRank == 1) where permutations are already met.
            if(curPermCnt >= trgtRnk) {
                splitChrPrefCnt = chrPairCnts[chrIdx] - step;
                splitIdx = chrIdx;
                isThresholdReached = true;
                break;
            } 
        }

        if(isThresholdReached) {
            break;
        }
    }

    // Target rank exceeds total possible permutations.
    if(curPermCnt < trgtRnk) {
        return "";
    }

    auto outIdx{0uz};

    // 2. Build the unchanged lexicographically sorted prefix in place
    for(auto chrIdx: vs::iota(0uz, splitIdx + 1)) {
        auto const chrCntToPlace{chrIdx == splitIdx ?
            splitChrPrefCnt : chrPairCnts[chrIdx]
        };

        rs::fill_n(str_.begin() + outIdx, chrCntToPlace, toChr(chrIdx));
        outIdx += chrCntToPlace;
        chrPairCnts[chrIdx] -= chrCntToPlace;
    }

    // 3. Construct the remaining suffix by finding the correct character for each
    //      position.
    while(sufLen > 0) {
        for(auto chrIdx: vs::iota(splitIdx, kChrSetSz)) {
            if(chrPairCnts[chrIdx] == 0) {
                continue;
            }

            // Evaluates the number of valid permutations remaining if this character is
            // chosen in O(1).
            auto const permsWithChr{calcNextPermCnt(
                curPermCnt, chrPairCnts[chrIdx], sufLen
            )};

            if(permsWithChr < trgtRnk) {
                trgtRnk -= permsWithChr;
                // Skip to next lexicographical character
                continue;
            }

            // Lock in this character
            curPermCnt = permsWithChr;
            --chrPairCnts[chrIdx];
            --sufLen;
            str_[outIdx++] = toChr(chrIdx);
            break;
        }
    }

    // Note: The middle character is bypassed and remains untouched exactly at
    // str_[halfLen]

    // Mirror the constructed first half to form the complete palindrome.
    rs::copy(str_ | vs::take(halfLen) | vs::reverse, str_.end() - halfLen);
    
    return str_;
}
