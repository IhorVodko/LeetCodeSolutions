// problem : https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-ii/description
// submission : https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-ii/submissions/2088830111
// solution post : https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-ii/solutions/8432802/
//    simplanation-simple-explanation-by-cyber-kps4

// Approach : Greedy Frequency Assignment
// Runtime : 1 ms, beats 96.43 %

// Complexity analysis
// let 'n' be the string length
// Time :  O(n)
// Space : O(1)

// import std;

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

auto constexpr kChrSetSz{26uz};
auto constexpr kChrSetFirst{'a'};
// Standard telephone keypad has 8 assignable buttons (2-9).
auto constexpr kTotKeys{8uz};

auto constexpr toIdx{[] (char const chr_) {
    return static_cast<size_t>(chr_ - kChrSetFirst);
}};

} // namespace 

class Solution final {
public:
    [[nodiscard]]
    static auto minimumPushes(std::string_view const word_) -> int;
};

auto Solution::minimumPushes(std::string_view const word_) -> int {
    auto freqPerChr{std::array<size_t, kChrSetSz>{}};
    for(auto const chr: word_) {
        ++freqPerChr[toIdx(chr)];
    }

    // Greedy strategy: most frequent characters get the smallest push counts.
    rs::sort(freqPerChr, std::greater{});

    auto keyPressCosts{
        freqPerChr |
        vs::take_while([] (auto const freq_) { return freq_ > 0; }) |
        vs::enumerate |
        vs::transform([] (auto const & idxAndFreq_) {
            auto const [idx, freq]{idxAndFreq_};
            // Maps index (frequency rank) to push count (1-8 -> 1, 9-16 -> 2, etc.).
            auto const pressMult{idx / kTotKeys + 1};
            
            return freq * pressMult;
        })
    };

    return static_cast<int>(rs::fold_left(keyPressCosts, 0uz, std::plus{}));
}
