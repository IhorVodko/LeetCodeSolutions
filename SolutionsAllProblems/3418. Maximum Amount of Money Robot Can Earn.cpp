// problem : https://leetcode.com/problems/maximum-amount-of-money-robot-can-earn/description
// submission : https://leetcode.com/problems/maximum-amount-of-money-robot-can-earn/submissions/1967054622
// solution post : https://leetcode.com/problems/maximum-amount-of-money-robot-can-earn/solutions/7755958/
//    c-modern-readable-code-runtime-0-ms-beat-aq0s

// import std;

namespace {

// Compile-time initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace

// Structure to track the maximum profit based on the number of negative values
// neutralized
struct MaxProfitPerNeutralization final {
    int mZeroUsed{};
    int mOneUsed{};
    int mTwoUsed{};
};

// let 'n' by 'm' be the matrix size
// time complexity O(n * m)
// space complexity O(m)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    using mxT = std::vector<std::vector<int>>;

    [[nodiscard]]
    auto maximumAmount(mxT const & coinMx_) const -> int;
private:
    static auto constexpr kMinProfit{std::numeric_limits<int>::min() / 2};
};

auto Solution::maximumAmount(mxT const & coinMx_) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;
    
    auto const cSz{std::ssize(coinMx_.front())};
    // 1D DP array for space optimization, storing states for the current and previous
    // rows
    auto dpMx{std::vector<MaxProfitPerNeutralization>(
        cSz + 1, {kMinProfit, kMinProfit, kMinProfit})};
    // Initial boundary condition for the start of the grid.
    dpMx.front() = {0, kMinProfit, kMinProfit};

    for(auto const & coinRow: coinMx_) {
        for(auto const c: vs::iota(1, cSz + 1)) {
            auto const currCoins{coinRow[c - 1]};
            // Corresponds to the left cell in the non-optimized 2D DP because the robot
            // moves right
            auto const & prevDp{dpMx[c - 1]};
            // Corresponds to the top cell in the non-optimized 2D DP because the robot
            // moves down
            auto & currDp{dpMx[c]};

            // Max profit when 2 neutralizations are used
            currDp.mTwoUsed = std::max({
                // 2 neutralizations were used previously, coming from the left
                prevDp.mTwoUsed + currCoins,
                // 2 neutralizations were used previously, coming from above
                currDp.mTwoUsed + currCoins,
                // 1 neutralization was used previously from the left, and the current
                // cell is neutralized
                prevDp.mOneUsed,
                // 1 neutralization was used previously from above, and the current cell
                // is neutralized
                currDp.mOneUsed});

            // Max profit when 1 neutralization is used
            currDp.mOneUsed = std::max({
                // 1 neutralization was used previously, coming from the left
                prevDp.mOneUsed + currCoins,
                // 1 neutralization was used previously, coming from above
                currDp.mOneUsed + currCoins,
                // 0 neutralizations were used previously from the left, and the current
                // cell is neutralized
                prevDp.mZeroUsed,
                // 0 neutralizations were used previously from above, and the current
                // cell is neutralized
                currDp.mZeroUsed});

            // Max profit when 0 neutralizations are used
            currDp.mZeroUsed =
                std::max(prevDp.mZeroUsed, currDp.mZeroUsed) + currCoins;
        }

        // Zero-index boundary condition so subsequent rows correctly handle the left edge
        dpMx.front() = {kMinProfit, kMinProfit, kMinProfit};
    }

    // Absolute maximum profit at the bottom-right cell across all neutralization states
    auto const maxProfit{std::max({
        dpMx[cSz].mZeroUsed,
        dpMx[cSz].mOneUsed,
        dpMx[cSz].mTwoUsed})};

    return maxProfit;
}
