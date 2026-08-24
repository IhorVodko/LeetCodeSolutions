// problem : https://leetcode.com/problems/stone-game-viii/description
// submission : https://leetcode.com/problems/stone-game-viii/submissions/2118503117
// solution post : https://leetcode.com/problems/stone-game-viii/solutions/8480110/simplanation-simple-explanation-by-cyber-4zg4

// Approach : Prefix Sums with Backward Dynamic Programming
// Runtime : 43 ms, beats 99.85 %

// Complexity analysis
// let 'n' be the number of stones
// Time :  O(n)
// Space : O(1)

// import std;

// #include <vector>
// #include <numeric>
// #include <algorithm>
// #include <ranges>
// #include <utility>
// #include <ios>
// #include <iostream>

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

// Represents the optimal subproblem solution at a given prefix.
struct GameState {
    int currPrefSum{};
    int maxScoreDiff{};
};

// Cannot choose a single stone from the left, so index 0 is skipped.
constexpr auto const kInvalidSingleStoneMove{1};
// The base case at n-1 is initialized explicitly.
constexpr auto const kAlreadyProcessedLastMove{1};

constexpr auto const processGameState{[] (auto state_, auto const stone_) {
    auto const [prefSum, maxScoreDiff]{state_};
    // 3. Step back the prefix sum by subtracting the trailing stone.
    auto const updatedPrefSum{prefSum - stone_};
    // 4. Maximize score: skip current index, or take it and yield to opponent.
    auto const updatedScoreDiff{std::max(
        maxScoreDiff,
        updatedPrefSum - maxScoreDiff
    )};

    return GameState{updatedPrefSum, updatedScoreDiff};
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
    static auto stoneGameVIII(std::vector<int> const & stones_) -> int;
};

auto Solution::stoneGameVIII(std::vector<int> const & stones_) -> int {
    // 1. Calculate the final prefix sum which acts as the base case dp[n-1].
    auto const totStonesSum{rs::fold_left(stones_, 0, std::plus{})};
    // Determine the number of valid backward transitions to process.
    auto const totPlayableStones{std::ssize(stones_) -
        (kInvalidSingleStoneMove + kAlreadyProcessedLastMove)
    };

    // 2. Fold backwards over the playable stones to propagate optimal score.
    auto const finalGameState{rs::fold_left(
        stones_ | vs::reverse | vs::take(totPlayableStones),
        GameState{totStonesSum, totStonesSum},
        processGameState
    )};

    // 5. The final state contains the optimal score difference for the first player.
    return finalGameState.maxScoreDiff;
}
