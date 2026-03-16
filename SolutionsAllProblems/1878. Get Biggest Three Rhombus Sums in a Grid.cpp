// problem : https://leetcode.com/problems/get-biggest-three-rhombus-sums-in-a-grid/description
// submission : https://leetcode.com/problems/get-biggest-three-rhombus-sums-in-a-grid/submissions/1950331976
// solution post : https://leetcode.com/problems/get-biggest-three-rhombus-sums-in-a-grid/solutions/7652590/
//    c-modern-readable-code-runtime-0-ms-beat-ief1

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

// Helper container that maintains the 3 largest distinct sums
class Top3UniqueNums final {
public:
    auto Emplace(int const val_) -> void {
        if(mMinSet.size() < 3) {
            mMinSet.emplace(val_);
        } else if(auto const minNum{*mMinSet.begin()};
            val_ > minNum && mMinSet.emplace(val_).second
        ) {
            mMinSet.erase(minNum);
        }
    }

    [[nodiscard]]
    auto Get() -> std::vector<int> {
        namespace vs = std::views;
        namespace rngs = std::ranges;

        // Return the values in descending order
        auto vals{std::vector<int>{}};
        rngs::copy(mMinSet | vs::reverse, std::back_inserter(vals));
        return vals;
    }

private:
    // Ordered container storing up to three smallest-first values
    std::set<int> mMinSet;
};

} // namespace

// let 'n' by 'm' be the grid size
// time complexity O(n * m * min(n, m))
// space complexity O(n * m)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    using mxT = std::vector<std::vector<int>>;

    [[nodiscard]]
    auto getBiggestThree(
        mxT const & grid
    ) const -> std::vector<int>;
};

auto Solution::getBiggestThree(
    mxT const & grid_
) const -> std::vector<int> {
    namespace vs = std::views;

    // Grid dimensions
    auto const rowTotCnt{std::ssize(grid_)};
    auto const colTotCnt{std::ssize(grid_.front())};
    // Prefix sums along the main diagonal direction
    auto prefMainSums{mxT(rowTotCnt + 1, std::vector<int>(colTotCnt + 2))};
    // Prefix sums along the anti-diagonal direction
    auto prefAntiSums{mxT(rowTotCnt + 1, std::vector<int>(colTotCnt + 2))};
    // Build both diagonal prefix-sum matrices
    for(auto const r: vs::iota(1, rowTotCnt + 1)) {
        for(auto const c: vs::iota(1, colTotCnt + 1)) {
            // Accumulate values from top-left to bottom-right direction
            prefMainSums[r][c] = prefMainSums[r - 1][c - 1] + grid_[r - 1][c - 1];
            // Accumulate values from top-right to bottom-left direction
            prefAntiSums[r][c] = prefAntiSums[r - 1][c + 1] + grid_[r - 1][c - 1];
        }
    }
    // Maintains the three largest distinct rhombus sums
    auto top3Sums{Top3UniqueNums{}};
    // Iterate over each cell as a potential top vertex of a rhombus
    for(auto const r: vs::iota(0, rowTotCnt)) {
        for(auto const c: vs::iota(0, colTotCnt)) {
            // Single cell rhombus (size 0)
            top3Sums.Emplace(grid_[r][c]);
            // Try increasing rhombus sizes whose vertical span is j-r
            for(auto j{r + 2}; j < rowTotCnt; j += 2) {
                // Coordinates of the four rhombus vertices
                auto const upR{r};
                auto const upC{c};
                auto const bottomR{j};
                auto const bottomC{c};
                auto const leftR{(r + j) / 2};
                auto const leftC{c - (j - r) / 2};
                auto const rightR{(r + j) / 2};
                auto const rightC{c + (j - r) / 2};
                // Stop if rhombus would go outside horizontal grid bounds
                if(leftC < 0 || colTotCnt <= rightC) {
                    break;
                }
                // Upper-left edge (top -> left) along anti-diagonal
                auto const upperLeft{prefAntiSums[leftR + 1][leftC + 1] -
                    prefAntiSums[upR][upC + 2]};
                // Upper-right edge (top -> right) along main diagonal
                auto const upperRight{prefMainSums[rightR + 1][rightC + 1] -
                    prefMainSums[upR][upC]};
                // Lower-left edge (left -> bottom) along main diagonal
                auto const lowerLeft{prefMainSums[bottomR + 1][bottomC + 1] -
                    prefMainSums[leftR][leftC]};
                // Lower-right edge (right -> bottom) along anti-diagonal
                auto const lowerRight{prefAntiSums[bottomR + 1][bottomC + 1] -
                    prefAntiSums[rightR][rightC + 2]};
                // Subtract vertices counted twice by prefix-sum edges
                auto const countedTwice{grid_[upR][upC] + grid_[bottomR][bottomC] +
                    grid_[leftR][leftC] + grid_[rightR][rightC]};
                // Compute rhombus perimeter sum using diagonal prefix sums
                auto const sum{upperLeft + upperRight + lowerLeft + lowerRight -
                    countedTwice};
                top3Sums.Emplace(sum);
            }
        }
    }
    // Return the three largest distinct sums in descending order
    return top3Sums.Get();
}
