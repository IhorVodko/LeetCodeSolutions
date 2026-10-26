// problem : https://leetcode.com/problems/count-islands-with-total-value-divisible-by-k/description
// submission : https://leetcode.com/problems/count-islands-with-total-value-divisible-by-k/submissions/2182404916
// solution post : https://leetcode.com/problems/count-islands-with-total-value-divisible-by-k/solutions/8590107/
//    simplanation-simple-explanation-by-cyber-5odw

// Approach : DFS with In-Place Sinking
// Runtime : 37 ms, beats 58.89 %

// Complexity analysis
// let 'n' by 'm' be the size of the given grid
// Time :  O(n * m)
// Space : O(n * m)

// import std;

// #include <array>
// #include <cstddef>
// #include <ios>
// #include <iostream>
// #include <ranges>
// #include <utility>
// #include <vector>

namespace rs = std::ranges;
namespace vs = std::views;

using std::ptrdiff_t;
using cell = std::pair<ptrdiff_t, ptrdiff_t>;
using vector2d = std::vector<std::vector<int>>;

namespace {

auto constexpr kWaterCell{0};
auto constexpr kDirsTot{4uz};
// Offsets to traverse adjacent top, right, bottom, and left cells
auto constexpr kDirs{std::array<std::pair<ptrdiff_t, ptrdiff_t>, kDirsTot>{{
    {-1z, 0z}, {0z, 1z}, {1z, 0z}, {0z, -1z}
}}};

// Optimize standard I/O stream operations performance.
[[maybe_unused]]
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
    static auto countIslands(
        vector2d & grid_,
        int const k_
    ) -> int;
};

auto Solution::countIslands(
    vector2d & grid_,
    int const k_
) -> int {
    // 1. Handle edge case of an empty grid structure
    if(grid_.empty() || grid_.front().empty()) {
        return 0;
    }

    auto const rowsTot{std::ssize(grid_)};
    auto rowIdx{vs::iota(0z, rowsTot)};
    auto const colsTot{std::ssize(grid_.front())};
    auto colIdxs{vs::iota(0z, colsTot)};
    // 2. Form lazy evaluation of all grid coordinate pairs
    auto allCells{vs::cartesian_product(rowIdx, colIdxs)};

    auto const isWithinBounds{[rowsTot, colsTot] (auto const r_, auto const c_) {
        return 0 <= r_ && r_ < rowsTot && 0 <= c_ && c_ < colsTot; 
    }};

    auto const isLand{[&grid_] (auto const cell_) {
        auto const [r, c]{cell_};
        return grid_[r][c] != kWaterCell;
    }};

    // 3. Define depth-first traversal to sum island value and sink visited land
    auto const calcIslandSum{[&grid_, &isWithinBounds, &isLand] (
        this auto && self_,
        auto const cell_
    ) -> long long {
        auto const [currR, currC]{cell_};
        auto sum{static_cast<long long>(grid_[currR][currC])};
        // Overwrite land with water to avoid cyclic traversal
        grid_[currR][currC] = kWaterCell;

        for(auto const [offsetR, offsetC]: kDirs) {
            auto const nextR{currR + offsetR};
            auto const nextC{currC + offsetC};

            if(isWithinBounds(nextR, nextC) && isLand(cell{nextR, nextC})) {
                sum += self_(cell{nextR, nextC});
            }
        } 

        return sum;
    }};

    // 4. Create lazy filter restricted to unvisited land elements
    auto landCells{allCells | vs::filter(isLand)}; 
    auto islandCnt{0};

    // 5. Evaluate unvisited components for divisibility condition
    for(auto const landCell: landCells) {
        if(calcIslandSum(landCell) % k_ == 0) {
            ++islandCnt;
        }
    }

    return islandCnt;
}
