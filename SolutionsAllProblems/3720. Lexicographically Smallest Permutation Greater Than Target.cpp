// problem : https://leetcode.com/problems/lexicographically-smallest-permutation-greater-than-target/description
// submission : https://leetcode.com/problems/lexicographically-smallest-permutation-greater-than-target/submissions/2122333810
// solution post : https://leetcode.com/problems/lexicographically-smallest-permutation-greater-than-target/solutions/8486706/
//    simplanation-simple-explanation-by-cyber-6kbn

// Approach : Greedy Prefix Matching with Backtracking
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the string length
// Time :  O(n)
// Space : O(1), auxiliary

// import std;

// #include <algorithm>
// #include <array>
// #include <ios>
// #include <iostream>
// #include <ranges>
// #include <string>

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

using namespace std::string_literals;

constexpr auto kChrSetSz{26};
constexpr auto kChrSetFirst{'a'};

// Convert an alphabet character to its corresponding zero-based index.
constexpr auto toChr{[] (auto const idx_) { 
    return static_cast<char>(idx_ + kChrSetFirst); 
}};

// Convert a zero-based index back to its corresponding alphabet character.
constexpr auto toIdx{[] (auto const chr_) { 
    return chr_ - kChrSetFirst; 
}};

// Calculate the frequency distribution of characters in the provided string.
constexpr auto calcFreqs{[] (auto const & str_) {
    auto freqPerChr{std::array<int, kChrSetSz>{}};
    for(auto const chr: str_) {
        ++freqPerChr[toIdx(chr)];
    }

    return freqPerChr;
}};

// Check if the target string can be formed from the source frequency pool.
constexpr auto isAnagram{[] (auto const & str_, auto freqPerChr_) {
    auto isAnagramMatch{true};
    for(auto freqPerChrCopy{freqPerChr_};
        auto const idx: str_ | vs::transform(toIdx)
    ) {
        if(freqPerChrCopy[idx]-- == 0) {
            isAnagramMatch = false;
            break;
        }
    }

    return isAnagramMatch;
}};

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
    auto lexGreaterPermutation(
        std::string const & srcStr_,
        std::string trgtStr_
    ) -> std::string;

private:
    auto CalcMatchPrefLen(std::string const & str_) -> int;

    std::array<int, kChrSetSz> mFreqPerChr;
};

auto Solution::lexGreaterPermutation(
    std::string const & srcStr_,
    std::string trgtStr_
) -> std::string {
    // 1. Calculate the available characters pool from the source string.
    mFreqPerChr = calcFreqs(srcStr_);

    // 2. If target is an anagram, return its immediate next permutation.
    if(isAnagram(trgtStr_, mFreqPerChr)) {
        return rs::next_permutation(trgtStr_).found ? trgtStr_ : ""s;
    }

    // 3. Find the maximum prefix length of target that can be built.
    auto matchPrefLen{CalcMatchPrefLen(trgtStr_)};

    // 4. Backtrack from the longest matching prefix to find a divergence point.
    for(auto const prefLen: vs::iota(0, matchPrefLen + 1) | vs::reverse) {
        // Find the smallest available character strictly greater than the target's.
        auto searchRng{vs::iota(toIdx(trgtStr_[prefLen]) + 1, kChrSetSz)};
        auto smallestGreaterChrIt{rs::find_if(searchRng, [&] (auto const idx_) {
            return mFreqPerChr[idx_] > 0;
        })};

        // 5. Construct the final string if a valid greater character is found.
        if(smallestGreaterChrIt != rs::end(searchRng)) {
            auto const smallestGreaterChrIdx{*smallestGreaterChrIt};

            trgtStr_[prefLen] = toChr(smallestGreaterChrIdx);
            trgtStr_.resize(prefLen + 1);

            --mFreqPerChr[smallestGreaterChrIdx];

            // Append remaining characters in ascending lexicographical order.
            for(auto const idx: vs::iota(0, kChrSetSz)) {
                trgtStr_.append(
                    mFreqPerChr[idx],
                    toChr(idx)
                );
            }

            return trgtStr_;
        }

        // 6. Restore frequency of the preceding character for further backtracking.
        if(prefLen > 0) {
            ++mFreqPerChr[toIdx(trgtStr_[prefLen - 1])];
        }
    }

    // Return empty string if no valid lexicographically greater permutation exists.
    return {};
}

auto Solution::CalcMatchPrefLen(std::string const & str_) -> int {
    auto matchPrefLen{0};
    for(auto const idx: str_ | vs::transform(toIdx)) {
        auto & freq{mFreqPerChr[idx]};
        // Stop matching if the required character is no longer available.
        if(freq == 0) {
            break;
        }

        --freq;
        ++matchPrefLen;
    }
    
    return matchPrefLen;
}
