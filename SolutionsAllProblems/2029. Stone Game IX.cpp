// problem : https://leetcode.com/problems/stone-game-ix/description
// submission : https://leetcode.com/problems/stone-game-ix/submissions/2109431627
// solution post : https://leetcode.com/problems/stone-game-ix/solutions/8465264/
//   simplanation-simple-explanation-by-cyber-zm4u

// Approach : Game Theory with Modulo Arithmetic
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the number of stones
// Time :  O(n)
// Space : O(1)

// import std;

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

// Game rules and math constants
auto constexpr kModBase{3};
auto constexpr kParityDiv{2};
auto constexpr kRequiredSurplus{2};

// Array indices mapped to remainders
auto constexpr kRemZero{0};
auto constexpr kRemOne{1};
auto constexpr kRemTwo{2};

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
    static auto stoneGameIX(std::vector<int> const & stones_) -> bool;
};

auto Solution::stoneGameIX(std::vector<int> const & stones_) -> bool {
    auto cntPerMod{std::array<int, kModBase>{}};

    // 1. Group stones by modulo 3 remainders to track sum progression
    rs::fold_left(
        stones_ | vs::transform([] (auto const stone_) { return stone_ % kModBase; }),
        std::ref(cntPerMod),
        [] (auto runningCnts, auto const rem_) {
            ++runningCnts.get()[rem_];

            return runningCnts;
        }
    );

    auto const remZeroCnt{cntPerMod[kRemZero]};
    auto const remOneCnt{cntPerMod[kRemOne]};
    auto const remTwoCnt{cntPerMod[kRemTwo]};

    // 2. Handle even 0-remainders where Bob maintains turn parity
    if(remZeroCnt % kParityDiv == 0) {
        return remOneCnt > 0 && remTwoCnt > 0;
    }

    auto const remDiff{std::abs(remOneCnt - remTwoCnt)};

    // 3. Handle odd 0-remainders where Bob forces parity shift requiring a surplus
    return remDiff > kRequiredSurplus; 
}
