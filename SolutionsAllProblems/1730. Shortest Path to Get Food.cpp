// problem : https://leetcode.com/problems/shortest-path-to-get-food/description/
// submission : https://leetcode.com/problems/shortest-path-to-get-food/submissions/1512920901
// solution post : https://leetcode.com/problems/shortest-path-to-get-food/solutions/6300201/c-modern-readable-code-optimal-time-comp-apr0

// #include <vector>
// #include <utility>

namespace Utility {
    auto constexpr you{'*'};
    auto constexpr wall{'X'};
    auto constexpr freeSpace{'0'};
    auto constexpr food{'#'};
}

// let 'r' be a rows count in the given grid
// 'c' - columns count in the given grid
// time complexity O(r * c)
// space complexity O(r * c)
// runtime 7 ms, beats 65.49 %
class Solution {
public:
    using MxT = std::vector<std::vector<char>>;
    int getFood(MxT const & grid) {
        using namespace Utility;
        yourLoc = FindYourLoc(grid);    
        auto const rows{grid.size()};
        auto const cols{grid.at(0).size()};
        auto length{0};
        auto queue{std::queue<std::pair<int, int>>{}};
        visitedCells = std::vector<std::vector<bool>>(rows,
            std::vector<bool>(cols, false));
        queue.push(yourLoc);
        visitedCells.at(yourLoc.first).at(yourLoc.second) = true;
        auto row{-1};
        auto col{-1};
        auto nextRow{-1};
        auto nextCol{-1};
        auto qSz{0};
        while(!queue.empty()) {
            qSz = queue.size();
            ++length;
            while(qSz-- > 0) {
                row = queue.front().first;
                col = queue.front().second;
                queue.pop();
                for(auto const [deltaRow, deltaCol]: moves) {
                    nextRow = row + deltaRow;
                    nextCol = col + deltaCol;
                    if(!IsValidCell(grid, {nextRow, nextCol})) {
                        continue;
                    }
                    if(grid.at(nextRow).at(nextCol) == food) {
                        return length;
                    }
                    queue.push({nextRow, nextCol});
                    visitedCells.at(nextRow).at(nextCol) = true; 
                }
            }
        }
        return -1;
    }
    Solution() :
        moves{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}
    {}
private:
    bool IsValidCell(
        MxT const & grid,
        std::pair<int, int> const cell 
    ) const {
        using namespace Utility;
        auto const row{cell.first};
        auto const col{cell.second};
        return 0 <= row && row < grid.size() &&
            0 <= col && col < grid.at(0).size() &&
            !visitedCells.at(row).at(col) && grid.at(row).at(col) != wall;
    }
    std::pair<int, int> FindYourLoc(MxT const & grid) {
        using namespace Utility;
        for(auto row{0}; row < grid.size(); ++row) {
            for(auto col{0}; col < grid.front().size(); ++col) {
                if(grid.at(row).at(col) == you) {
                    return {row, col};
                }
            }
        }
        return {-1, -1};
    }
    std::pair<int, int> yourLoc;
    std::vector<std::pair<int, int>> moves; 
    std::vector<std::vector<bool>> visitedCells;
};
