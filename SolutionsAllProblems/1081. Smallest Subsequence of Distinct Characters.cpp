// problem : https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/description
// submission : https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/submissions/2073500058
// solution post : https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/solutions/8407455/
//    modern-readable-code-optimal-time-comple-ser3

// Approach : Monotonic Stack
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the input string length
// 'm' - character set size
// Time :  O(n)
// Space : O(m)

// import std;

namespace {

namespace vs = std::views;

auto constexpr kChrSetFirst{'a'};
auto constexpr kChrSetSz{26uz};

// Maps lowercase letters to a 0-25 numeric index
auto constexpr toNum{[] (char const chr_) {
    return chr_ - kChrSetFirst;
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
    static auto smallestSubsequence(std::string_view const strIn_) -> std::string;
};

auto Solution::smallestSubsequence(std::string_view const strIn_) -> std::string {

    // Store the rightmost index for each character
    auto lastPosPerChr{std::array<int, kChrSetSz>{}};
    for(auto const [idx, chr]: strIn_ | vs::enumerate) {
        lastPosPerChr[toNum(chr)] = idx;
    }

    // Track characters currently in the result to ensure uniqueness
    auto isPresentChr{std::bitset<kChrSetSz>{}};
    // Output string acting as a conditionally monotonic stack
    auto strOut_{""s};

    for(auto const [idx, chr] : strIn_ | vs::enumerate) {
        auto const num{toNum(chr)};

        if(isPresentChr.test(num)) {
            continue;
        }

        // Maintain lexicographical order by removing larger trailing characters if they
        // are guaranteed to appear again later in the string
        while(!strOut_.empty() && strOut_.back() > chr &&
            lastPosPerChr[toNum(strOut_.back())] > idx
        ) {
            isPresentChr.reset(toNum(strOut_.back()));
            strOut_.pop_back();
        }

        strOut_.push_back(chr);
        isPresentChr.set(num);
    }

    return strOut_;
}
