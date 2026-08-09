// problem : https://leetcode.com/problems/stone-game-ii/description
// submission : https://leetcode.com/problems/stone-game-ii/submissions/2100835639
// solution post : https://leetcode.com/problems/stone-game-ii/solutions/8451609/simplanation-simple-explanation-by-cyber-witj

// Approach : Minimax Algorithm with Memoization (Dynamic Programming)
// Runtime : 7 ms, beats 77.22 %

// Complexity analysis
// let 'n' be the number of stone piles
// Time :  O(n^3)
// Space : O(n^2)

// import std;

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace 

class Solution final {
public:
    [[nodiscard]]
    static auto stoneGameII(std::vector<int> const & stonePiles_) -> int;
};

auto Solution::stoneGameII(std::vector<int> const & stonePiles_) -> int {
    auto const totPiles_{static_cast<int>(stonePiles_.size())};

    // Allow O(1) retrieval of the total stones left on the board.
    auto suffSumPiles{std::vector<int>(totPiles_)};
    std::inclusive_scan(stonePiles_.rbegin(), stonePiles_.rend(), suffSumPiles.rbegin());

    // Cache overlapping subproblems mapped by current game state dimensions:
    // currPileIdx_ (current pile index) and currLimM_ (current move limit).
    // Values represent the max stones the current player can secure from here.
    auto maxStonesMemo{std::vector<std::vector<int>>(
        totPiles_, std::vector<int>(totPiles_ + 1, -1)
    )};

    auto calcMaxStones{[&] (
        this auto const & self_,
        int const currPileIdx_,
        int const currLimM_
    ) -> int {
        auto & currMaxStones{maxStonesMemo[currPileIdx_][currLimM_]};

        // Terminal game states and early exits to prevent redundant calculations.
        if(currPileIdx_ >= totPiles_) {
            return 0;
        } else if(currPileIdx_ + 2 * currLimM_ >= totPiles_) {
            return suffSumPiles[currPileIdx_];
        } else if(currMaxStones != -1) {
            return currMaxStones;
        }

        auto evaluateMove{[&] (int const maxPilesCntToTake_) -> int {
            auto const nextPileIdx{currPileIdx_ + maxPilesCntToTake_};
            auto const nextLimitM{std::max(currLimM_, maxPilesCntToTake_)};

            // Deduct opponent's optimal outcome from total pool to find our yield.
            return suffSumPiles[currPileIdx_] - self_(nextPileIdx, nextLimitM);
        }};

        auto possiblePilesCntToTake{vs::iota(1, 2 * currLimM_ + 1)};

        // Identify and memoize the optimal strategy path for this state.
        return  currMaxStones =
            rs::max(possiblePilesCntToTake | vs::transform(evaluateMove))
        ;
    }};

    return calcMaxStones(0, 1);
}
