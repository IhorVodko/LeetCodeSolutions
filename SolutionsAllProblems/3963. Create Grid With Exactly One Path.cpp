// problem : https://leetcode.com/problems/create-grid-with-exactly-one-path/description
// submission : https://leetcode.com/problems/create-grid-with-exactly-one-path/submissions/2183157549
// solution post : https://leetcode.com/problems/create-grid-with-exactly-one-path/solutions/8591376/
//    simplanation-simple-explanation-by-cyber-jszk

// Approach : The L-Shape Corridor Strategy
// Runtime : 1 ms, beats 57.19 %

// Complexity analysis
// let 'n' by 'm' be given grid size
// Time :  O(n * m)
// Space : O(m)

// import std;

// #include <ios>
// #include <iostream>
// #include <ranges>
// #include <string>
// #include <vector>

namespace rs = std::ranges;
namespace vs = std::views;

using gridT = std::vector<string>;

namespace {

constexpr auto kFreeCell{'.'};
constexpr auto kObstacleCell{'#'};

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
    [[nodiscard]]
    static auto  createGrid(
        int const rowsTot_,
        int const colsTot_
    ) -> gridT;
};

auto  Solution::createGrid(
    int const rowsTot_,
    int const colsTot_
) -> gridT {
    // 1. Create a fully traversable top boundary to force horizontal movement.
    auto const topRow{std::string(colsTot_, kFreeCell)};
    // 2. Create blocked rows with only the rightmost cell open for vertical descent.
    auto const bottomRow{[colsTot_] {
        auto row{std::string(colsTot_, kObstacleCell)};
        row.back() = kFreeCell;

        return row;
    }()};

    // Select row patterns to form the only valid single-path L-shape corridor.
    const auto generateRow{[&topRow, &bottomRow] (auto const rowIdx_) {
        return rowIdx_ == 0 ? topRow : bottomRow;
    }};

    // 3. Assemble the full grid by mapping indices to the corresponding row patterns.
    auto const grid{
        vs::iota(0, rowsTot_) |
        vs::transform(generateRow) |
        rs::to<gridT>()
    };

    return grid;
}
