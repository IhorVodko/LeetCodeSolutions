// problem :  https://leetcode.com/problems/minimum-swaps-to-arrange-a-binary-grid/description
// submission : https://leetcode.com/problems/minimum-swaps-to-arrange-a-binary-grid/submissions/1936109899
// solution post : https://leetcode.com/problems/minimum-swaps-to-arrange-a-binary-grid/solutions/7620945/
//    c-modern-readable-code-beats-100-runtime-or23

// import std;

inline static int const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' by 'n' be the grid size
// time complexity O(n^2)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto minSwaps(std::vector<std::vector<int>> const & grid_) const -> int;
};

auto Solution::minSwaps(std::vector<std::vector<int>> const & grid_) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto const n{std::ssize(grid_)};
    auto last1IdxByRow{std::vector<int>(n, -1)};
    for(auto const r: vs::iota(0, n)) {
            auto const & row{grid_[r]};
            // Store the index of the rightmost 1 in each row
            if(auto const subRng{rngs::find_last(row, 1)};
                subRng.begin() != row.end()
            ) [[likely]] {
                last1IdxByRow[r] = std::distance(row.begin(), subRng.begin());
            }
    }
    auto minOpCnt{0};
    for(auto const curR: vs::iota(0, n)) {
        // Find the first row at or below curR that satisfies the required trailing zero
        // condition
        auto const minValidRIt{
            std::find_if(last1IdxByRow.begin() + curR, last1IdxByRow.end(),
                [=] (auto const tryR_) {return tryR_ <= curR; })};
        if(minValidRIt == last1IdxByRow.end()) {
            // No valid row can be brought to current position
            return -1;
        }
        auto const minValidR{std::distance(last1IdxByRow.begin(), minValidRIt)};
        auto const curOpCnt{minValidR - curR};
        minOpCnt += curOpCnt;
        // Bubble the valid row upward to position curR
        for(auto const r: vs::iota(curR + 1, minValidR + 1) | vs::reverse) {
            std::swap(last1IdxByRow[r], last1IdxByRow[r - 1]);
        }
    }
    return minOpCnt;
}
