// problem : https://leetcode.com/problems/sum-game/description
// submission : 
// solution post : https://leetcode.com/problems/sum-game/solutions/8478383/simplanation-simple-explanation-by-cyber-120m

// Approach : https://leetcode.com/problems/sum-game/submissions/2117418805/?envType=daily-question&envId=2026-08-23
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the string length
// Time :  O(n)
// Space : O(1)

// import std;

// #include <string_view>
// #include <ranges>
// #include <algorithm>

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

// Tracks differences between left and right string halves
struct GameState {
    int netSum{};
    int netSymbolCnt{};
    int totSymbolCnt{};
};

constexpr auto kSymbol{'?'};
constexpr auto kChrZero{'0'};
constexpr auto kLeftHalfWeight{-1};
constexpr auto kRightHalfWeight{1};
constexpr auto kMaxDigit{9};

constexpr auto toDigit{[] (char const chr_) { return chr_ - kChrZero; }};

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
    static auto sumGame(std::string_view const num_) -> bool;
};

auto Solution::sumGame(std::string_view const num_) -> bool {
    auto const halfLen{std::ssize(num_) / 2};
    
    // 1. Fold string characters to calculate aggregate state differences
    auto const accumState{[=] (
        GameState stats_,
        auto const & idxAndChr_
    ) {
        auto const [idx, chr]{idxAndChr_};
        
        // Positive weight for left half, negative for right half
        if( auto const weight{idx < halfLen ? kLeftHalfWeight : kRightHalfWeight};
            chr == kSymbol
        ) {
            ++stats_.totSymbolCnt;
            stats_.netSymbolCnt += weight;
        } else {
            stats_.netSum += toDigit(chr) * weight;
        }

        return stats_;
    }};

    auto const finalState{rs::fold_left(num_ | vs::enumerate, GameState{}, accumState)};
    
    // 2. Odd total empty spots give Alice the last turn, ensuring her victory
    if (finalState.totSymbolCnt % 2 != 0) {
        return true;
    }

    // 3. Bob wins only if initial sum diff is perfectly balanced by remaining spots
    return 2 * finalState.netSum + kMaxDigit * finalState.netSymbolCnt != 0;
}
