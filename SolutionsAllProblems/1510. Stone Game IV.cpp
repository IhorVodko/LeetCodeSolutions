// problem : https://leetcode.com/problems/stone-game-iv/description
// submission : https://leetcode.com/problems/stone-game-iv/submissions/2101963782
// solution post : https://leetcode.com/problems/stone-game-iv/solutions/8453241/simplanation-simple-explanation-by-cyber-fj78

// Approach : Approach : Forward-Push Dynamic Programming (Game Theory)
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the maximum possible number of stones
// Time :  O(n * sqrt(n)), amortized O(1)
// Space : O(n)

// import std;

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

constexpr auto kStoneUpLim{100'000};

// Precompute and cache all game states at startup
const auto kWinningStates{[] [[nodiscard]] {
    auto winningStates{std::array<bool, kStoneUpLim + 1>{}};

    // 1. Precompute all valid square moves up to the limit
    auto validSquareMoves{
        vs::iota(1) |
        vs::transform([] (auto const baseVal_) { return baseVal_ * baseVal_; }) |
        vs::take_while([] (auto const squareVal_) {
            return squareVal_ <= kStoneUpLim;
        }) |
        rs::to<std::vector>() 
    };

    // 2. Iterate through all possible game states
    for(auto const currStones: vs::iota(0, kStoneUpLim + 1)) {
        // 3. Skip if current state is already a winning state
        if(winningStates[currStones]) {
            continue;
        }

        // 4. Mark states reachable from this losing state as winning states
        for(auto const squareMove: validSquareMoves) {
            auto const nextStones{currStones + squareMove};

            // Stop evaluation if the next state exceeds the limit
            if(nextStones > kStoneUpLim) {
                break;
            }
            winningStates[nextStones] = true;
        }
    }

    return winningStates;
}()};

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
    static auto winnerSquareGame(int const totalStones) -> bool;
};

// 5. Look up the precomputed result
auto Solution::winnerSquareGame(int const totalStones) -> bool {
    return kWinningStates[totalStones];
}
