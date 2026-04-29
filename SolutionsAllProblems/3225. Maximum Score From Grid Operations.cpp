// problem : https://leetcode.com/problems/maximum-score-from-grid-operations/description
// submission : https://leetcode.com/problems/maximum-score-from-grid-operations/submissions/1991038897
// solution post : https://leetcode.com/problems/maximum-score-from-grid-operations/solutions/8113486/
//    c-modern-readable-code-beats-100-runtime-v5ac

// Approach : Dynamic Programming with Space Optimization (Rolling Arrays)
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' by 'n' be the grid dimensions
// complexity :  O(n^2)
// complexity : O(n)

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

class Solution final{
public:
    using ll = long long;
    //  The 2D input grid.
    using mxT = std::vector<std::vector<int>>;
    // Rolling 2D array used in prefix sums.
    using rollArr2dT = std::array<std::vector<ll>, 2>;
    // Rolling 3D array used for DP state transitions.
    using rollArr3dT = std::array<std::vector< std::array<ll, 2>>, 2>;

    // Main function to calculate the maximum score from grid operations.
    [[nodiscard]]
    auto maximumScore(mxT const & grid_) const -> ll;
};

auto Solution::maximumScore(mxT const & grid_) const -> ll {
    namespace vs = std::views;

    auto const gridSz{std::ssize( grid_ )};
    // Rolling 2D array to store prefix sums of columns.
    auto colPrefSums{rollArr2dT{
        std::vector<ll>(gridSz + 1),
        std::vector<ll>(gridSz + 1)
    }};

    // Base cases: zero elements sum to zero.
    colPrefSums[0][0] = 0;
    colPrefSums[1][0] = 0;

    // Precompute the column prefix sums for the first column.
    for(auto const rowI: vs::iota(0, gridSz)) {
        colPrefSums[0][rowI + 1] = colPrefSums[0][rowI] + grid_[rowI][0];
    }

    // DP state tables for the previous and current columns.
    auto dpStates{rollArr3dT{
        std::vector<std::array<ll, 2>>(gridSz + 1, std::array<ll, 2>{0, 0}),
        std::vector<std::array<ll, 2>>(gridSz + 1, std::array<ll, 2>{0, 0})
    }};

    // Indices to easily toggle between previous and current states.
    auto prevColI{0};
    auto currColI{1};

    for(auto const colIdx: vs::iota(0, gridSz - 1)) {
        // Calculate the prefix sums for the current column.
        for(auto const rowI: vs::iota(0, gridSz)) {
            colPrefSums[currColI][rowI + 1] =
                colPrefSums[currColI][rowI] + grid_[rowI][colIdx + 1];
        }

        // Running maximum for forward (prefix) transitions.
        auto runPrefMax{dpStates[prevColI][0][1]};

        // Forward pass: calculate max score from top to bottom.
        for(auto const blackCellsCnt: vs::iota(1, gridSz + 1)) {
            // Determine max score factoring in the running prefix max.
            auto const currScoreMax{std::max(
                dpStates[prevColI][blackCellsCnt][0],
                runPrefMax + colPrefSums[prevColI][blackCellsCnt]
            )};

            // Record the highest achievable score in the current state.
            dpStates[currColI][blackCellsCnt][0] = currScoreMax;
            dpStates[currColI][blackCellsCnt][1] = currScoreMax;

            // Update the prefix max to include the newly calculated state.
            runPrefMax = std::max(
                runPrefMax,
                dpStates[prevColI][blackCellsCnt][1] -
                    colPrefSums[prevColI][blackCellsCnt]
            );
        }

        //  The running maximum for backward (suffix) transitions.
        auto runSuffMax{
            dpStates[prevColI][gridSz][0] + colPrefSums[currColI][gridSz]};

        // Backward pass: calculate max score from bottom to top.
        for(auto const blackCellsCnt: vs::iota(1, gridSz) | vs::reverse) {
            auto & currState{dpStates[currColI][blackCellsCnt][0]};

            // Update the current state by comparing with the running suffix max.
            currState = std::max(
                currState,
                runSuffMax - colPrefSums[currColI][blackCellsCnt]
            );
            // Re-evaluate suffix max for the next iteration up the column.
            runSuffMax = std::max(
                runSuffMax,
                dpStates[prevColI][blackCellsCnt][0] +
                    colPrefSums[currColI][blackCellsCnt]
            );
        }

        // Assign the highest suffix score to the zero black cells state.
        dpStates[currColI][0][0] = runSuffMax;
        // Determine the alternative state for zero black cells.
        dpStates[currColI][0][1] =
            std::max(dpStates[prevColI][0][0], dpStates[prevColI][gridSz][0]);
        // Swap rolling array indices to step forward to the next column.
        std::swap(prevColI, currColI);
    }

    auto maxScore{std::numeric_limits<ll>::min()};

    // Iterate through all potential cell counts in the last processed column.
    for(auto const & prevStateRow{dpStates[prevColI]};
        auto const cellCnt: vs::iota(0, gridSz + 1)
    ) {
        // Extract the absolute maximum score across all final states.
        maxScore =
            std::max({maxScore, prevStateRow[cellCnt][0], prevStateRow[cellCnt][1]});
    }

    return maxScore;
}
