// problem : https://leetcode.com/problems/number-of-islands/description/
// submission : https://leetcode.com/problems/number-of-islands/submissions/1542817715
// solution post : https://leetcode.com/problems/number-of-islands/solutions/6421528/
//     c-modern-readable-code-optimal-time-comp-ziij

// #include <queue>
// #include <vector>

namespace Constants {
    auto constexpr water{'0'};
    auto constexpr land{'1'};
    auto constexpr moves{std::array<std::pair<int, int>, 4>{{{-1, 0}, {1, 0},
        {0, -1}, {0, 1}}}};
}

// let 'w' by 'l' be dimensions of the given grid
// time complexity O(w * l)
// space complexity O(w * l)
// runtime 29 ms, beats 45.20 %
class Solution {
public:
    using MxT = std::vector<vector<char>>;
    using CellT = std::pair<int, int>;
    int numIslands(std::vector<vector<char>> & grid) const {
       using namespace Constants; 
        auto const rowsCount{grid.size()};
        auto const colsCount{grid.at(0).size()};
        auto islandsCount{0};
        for(auto row{0}; row < rowsCount; ++row) {
            for(auto col{0}; col < colsCount; ++col) {
                if(grid.at(row).at(col) == water) {
                    continue;
                }
                VisitIsland(grid, {row, col});
                ++islandsCount;
            }
        }
        return islandsCount;
    }
private:
    bool IsLand(
        MxT const & grid,
        CellT const & cell
    ) const {
        using namespace Constants;
        auto const rowsCount{grid.size()};
        auto const colsCount{grid.at(0).size()};
        auto const [row, col]{cell};
        return 0 <= row && row < rowsCount && 0 <= col && col < colsCount &&
            grid.at(row).at(col) == land;
    }
    void VisitIsland(
        MxT & grid,
        CellT const & cell
    ) const {
        using namespace Constants;
        auto qCells{std::queue<CellT>{}};
        qCells.emplace(cell);
        grid.at(cell.first).at(cell.second) = water;
        while(!qCells.empty()) {
            auto const [row, col]{qCells.front()};
            qCells.pop();
            for(auto const & move: moves) {
                auto const nextRow{row + move.first};
                auto const nextCol{col + move.second}; 
                if(!IsLand(grid, {nextRow, nextCol})) {
                    continue;
                }
                qCells.emplace(nextRow, nextCol);
                grid.at(nextRow).at(nextCol) = water; 
            }
        }
    }
};
