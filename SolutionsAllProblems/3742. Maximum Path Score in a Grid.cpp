// problem : https://leetcode.com/problems/maximum-path-score-in-a-grid/description
// submission : https://leetcode.com/problems/maximum-path-score-in-a-grid/submissions/1992044821
// solution post : https://leetcode.com/problems/maximum-path-score-in-a-grid/solutions/8119977/
//    c-modern-readable-code-beats-100-runtime-928s

// Approach : Space-Optimized 2D Dynamic Programming (Knapsack-like Grid Traversal)
// Runtime : 131 ms, beats 100.00 %

// Complexity
// let 'n' by 'm' be the grid dimension
// 'k' - total cost limit
// complexity :  O(n * m * k)
// complexity : O(m * k)

// import std;

namespace {

// Compile-time initializer to configure fast I/O before main() runs
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
    using arr2dT = std::vector<std::vector<int>>;
    using intLim = std::numeric_limits<int>;

    [[nodiscard]]
    auto maxPathScore(
        arr2dT const& grid_,
        int costUpLim_
    ) const -> int;

private:
    // Helper to calculate the cost associated with a given cell's score
    [[nodiscard]]
    inline auto CalcCost(int const score_) const noexcept -> int;

    // Calculates the absolute minimum cost path from top-left to bottom-right
    [[nodiscard]]
    auto CalcMinPathCost(arr2dT const& grid_) const -> int;
};

auto Solution::maxPathScore(
    arr2dT const& grid_,
    int costUpLim_
) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    if (CalcMinPathCost(grid_) > costUpLim_) {
        return -1;
    }

    auto const rSz{static_cast<int>(grid_.size())};
    auto const cSz{static_cast<int>(grid_.front().size())};
    auto const costUpLimFeasible{rSz + cSz - 1};

    costUpLim_ = std::min(costUpLim_, costUpLimFeasible);

    // DP table tracking max score per column index and accumulated cost
    auto maxScorePerColAndAccumCost{
        arr2dT(cSz + 1, std::vector<int>(costUpLim_ + 1, intLim::min()))
    };

    auto & baseCaseMaxScore{maxScorePerColAndAccumCost[1][0]};

    baseCaseMaxScore = 0;

    for (auto const r: vs::iota(0, rSz)) {
        for (auto const c: vs::iota(0, cSz)) {
            auto const currScore{grid_[r][c]};
            auto const currCost{CalcCost(currScore)};
            auto const currCostUpLim{std::min(costUpLim_, r + c + 1)};

            // Iterate through costs in reverse to update DP table in place
            for (auto const cost: vs::iota(0, currCostUpLim + 1) | vs::reverse) {
                // Calculate the required cost before arriving at this cell
                auto const prevCost{cost - currCost};
                auto prevMaxScore{intLim::min()};

                // Check if the required previous cost is valid (non-negative)
                if (prevCost >= 0) {
                    auto const prevMaxScoreTop{
                        maxScorePerColAndAccumCost[c + 1][prevCost]
                    };
                    auto const prevMaxScoreLeft{maxScorePerColAndAccumCost[c][prevCost]};

                    prevMaxScore = std::max(prevMaxScoreTop, prevMaxScoreLeft);
                }
                
                auto & oldMaxScore{maxScorePerColAndAccumCost[c + 1][cost]};
                auto const newMaxScore{prevMaxScore + currScore};
                // Update state: if unreachable, stay min; else add current score
                oldMaxScore = 
                    prevMaxScore == intLim::min() ? intLim::min() : newMaxScore;
            }
        }
    }
  
    // Find the maximum score achieved at the last column across all valid costs
    auto const maxScore{rngs::max(maxScorePerColAndAccumCost[cSz])};

    return maxScore;
}

auto Solution::CalcCost(int const score_) const noexcept -> int {
    return score_ == 0 ? 0 : 1;
}

auto Solution::CalcMinPathCost(arr2dT const& grid_) const -> int {
    namespace vs = std::views;

    auto const cSz{std::ssize(grid_.front())};
    // Array to track the minimum cost to reach each column in the current row
    auto minCostPerCol{std::vector<int>(cSz + 1, intLim::max())};
    auto & baseCaseMinCost{minCostPerCol[1]};

    baseCaseMinCost = 0;

    for (auto const& row: grid_) {
        for (auto currC{0}; auto const prevC: vs::iota(0, cSz)) {
            currC = prevC + 1;
            auto const currScore{row[prevC]};
            auto const currCost{CalcCost(currScore)};
            auto const minCostLeft{minCostPerCol[prevC]};
            auto const minCostTop{minCostPerCol[currC]};
            auto const prevMinCost{std::min(minCostLeft, minCostTop)};
            
            // Check if the current cell is reachable
            if (prevMinCost != intLim::max()) {
                auto & oldMinCost{minCostPerCol[currC]};
                auto const newMinCost{prevMinCost + currCost};

                oldMinCost = newMinCost;
            }
        }
    }

    auto const minCostBottomRight{minCostPerCol[cSz]};

    return minCostBottomRight;
}
