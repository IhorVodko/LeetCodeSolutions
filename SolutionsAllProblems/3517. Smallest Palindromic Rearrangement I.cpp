// problem : https://leetcode.com/problems/smallest-palindromic-rearrangement-i/description
// submission : https://leetcode.com/problems/smallest-palindromic-rearrangement-i/submissions/2085181214
// solution post : https://leetcode.com/problems/smallest-palindromic-rearrangement-i/solutions/8426954/
//    simplanation-simple-explanation-by-cyber-nmjz

// Approach : Half-Sorting and Mirroring via Frequency Counting
// Runtime : 4 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the string length
// Time :  O(n)
// Space : O(1)

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
    static auto smallestPalindrome(std::string & str_) -> std::string;
};

auto Solution::smallestPalindrome(std::string & str_) -> std::string {
    auto const len{str_.size()};

    // Strings of length 3 or less already have sorted halves.
    if(len <= 3) {
        return str_;
    }

    auto const halfLen{len / 2};
    
    // Count occurrences of each character in the first half.
    auto pairCnts{std::array<size_t, kChrSetSz>{}};
    for(auto const chr: str_ | vs::take(halfLen)) {
        ++pairCnts[toIdx(chr)];
    }
    
    // Reconstruct the first half in lexicographically sorted order.
    for(auto strIdxOffset(0uz);
        auto const [chrIdx, pairCnt]:
            pairCnts |
            vs::enumerate |
            vs::filter([] (auto const & idxAndCnt_) {
                return std::get<1>(idxAndCnt_) > 0;
            })
    ) {
        rs::fill_n(str_.begin() + strIdxOffset, pairCnt, toChr(chrIdx));
        strIdxOffset += pairCnt;
    }

    // Overwrite the second half with the reversed sorted first half.
    rs::copy(str_ | vs::take(halfLen) | vs::reverse, str_.end() - halfLen);

    return str_;
}
