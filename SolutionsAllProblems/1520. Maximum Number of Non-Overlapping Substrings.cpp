// problem : https://leetcode.com/problems/maximum-number-of-non-overlapping-substrings/description
// submission : https://leetcode.com/problems/maximum-number-of-non-overlapping-substrings/submissions/2145798666
// solution post : https://leetcode.com/problems/maximum-number-of-non-overlapping-substrings/solutions/8528069/
//  simplanation-simple-explanation-by-cyber-siyw

// Approach : Minimum Bounding Intervals and Greedy Scheduling
// Runtime : 5 ms, beats 88.69 %

// Complexity analysis
// let 'n' be the string length
// Time :  O(n)
// Space : O(1)

// import std;

// #include <algorithm>
// #include <array>
// #include <ios>
// #include <iostream>
// #include <optional>
// #include <ranges>
// #include <string>
// #include <string_view>
// #include <vector>

// #include <cstddef>

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

using std::size_t;

// Total lowercase English letters limit.
constexpr auto kChrSetSz{26uz};
constexpr auto kChrSetFirst{'a'};
constexpr auto kInvalidIdx{-1};

// Map a lowercase character to its alphabetical index.
constexpr auto toChrSetIdx{[] [[nodiscard]] (auto const chr_) {
    return static_cast<size_t>(chr_ - kChrSetFirst);
}};

// Compare intervals: sort by end ascending, then start descending for shorter span.
constexpr auto endAscendingStartDescending{[] [[nodiscard]] (
    auto const & lhs_,
    auto const & rhs_
) {
    auto const [lStartIdx, lEndIdx]{lhs_};
    auto const [rStartIdx, rEndIdx]{rhs_};

    if(lEndIdx == rEndIdx) {
        return lStartIdx > rStartIdx;
    }

    return lEndIdx < rEndIdx;
}};

// Optimize standard I/O stream operations performance.
[[maybe_unused]]
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

struct ChrBounds final {
    int firstIdx{};
    int lastIdx{};
};

struct SubstrRng final {
    int startIdx{};
    int endIdx{};
};

} // namespace

class Solution final {
public:
    auto maxNumOfSubstrings(std::string_view strIn_) -> std::vector<std::string>;

private:
    auto calcValidSubstrRng(
        size_t const chrSetIdx_,
        std::array<ChrBounds, kChrSetSz> const & boundsPerChr_
    ) const -> std::optional<SubstrRng>;

    std::string_view mStrIn;
};

[[nodiscard]]
auto Solution::maxNumOfSubstrings(std::string_view strIn_) -> std::vector<std::string> {
    mStrIn = strIn_;

    auto const strLen{static_cast<int>(mStrIn.size())};

    auto boundsPerChr{std::array<ChrBounds, kChrSetSz>{}};
    rs::fill(boundsPerChr, ChrBounds{strLen, kInvalidIdx});

    // 1. Calculate the first and last occurrence indices for each character in the string.
    for(auto const [idx, chr]: mStrIn | vs::enumerate) {
        auto & [firstIdx, lastIdx]{boundsPerChr[toChrSetIdx(chr)]};

        if(firstIdx == strLen) {
            firstIdx = static_cast<int>(idx);
        }

        lastIdx = static_cast<int>(idx);
    }

    // 2. Identify all valid isolated substring ranges for each present character.
    auto validSubstrRngs{
        vs::iota(0uz, kChrSetSz) |
        vs::transform([&] (auto const chrSetIdx_) {
            return calcValidSubstrRng(chrSetIdx_, boundsPerChr);
        }) |
        vs::filter(&std::optional<SubstrRng>::has_value) |
        vs::transform([] (auto const substrRng_) { return substrRng_.value(); }) |
        rs::to<std::vector>()
    };

    // 3. Sort the valid ranges to maximize the count of non-overlapping substrings.
    rs::sort(validSubstrRngs, endAscendingStartDescending);

    auto substrsOut{std::vector<std::string>{}};
    substrsOut.reserve(validSubstrRngs.size());

    // 4. Greedily select non-overlapping substrings based on the sorted order.
    for (auto lastIncludedEndIdx{kInvalidIdx};
        const auto substrRng: validSubstrRngs
    ) {
        auto const [startIdx, endIdx]{substrRng};

        if(startIdx <= lastIncludedEndIdx) {
            continue;
        }

        const auto substrLen{endIdx - startIdx + 1};

        substrsOut.emplace_back(mStrIn.substr(startIdx, substrLen));
        lastIncludedEndIdx = endIdx;
    }

    substrsOut.shrink_to_fit();

    return substrsOut; 
}

[[nodiscard]]
auto Solution::calcValidSubstrRng(
    size_t const chrSetIdx_,
    std::array<ChrBounds, kChrSetSz> const & boundsPerChr_
) const -> std::optional<SubstrRng> {
    auto [startIdx, endIdx]{boundsPerChr_[chrSetIdx_]};

    // Skip characters that do not appear in the input string.
    if(startIdx == static_cast<int>(mStrIn.size())) {
        return std::nullopt;
    }

    for(auto idx{startIdx}; idx <= endIdx; ++idx) {
        auto const [firstIdx, lastIdx]{boundsPerChr_[toChrSetIdx(mStrIn[idx])]};

        // If an inner character starts before the current character, range is invalid.
        if(firstIdx < startIdx) {
            return std::nullopt;
        }

        // Extend the end index to cover the inner character's last occurrence.
        endIdx = rs::max(endIdx, lastIdx);
    }

    return SubstrRng{startIdx, endIdx};
}
