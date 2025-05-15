// problem : https://leetcode.com/problems/bomb-enemy/description/
// submission : https://leetcode.com/problems/bomb-enemy/submissions/1634672202
// solution post : https://leetcode.com/problems/bomb-enemy/solutions/6747183/
//    c-modern-readable-code-beats-100-by-cybe-fpsb

// #include <algorithm>
// #include <vector>

namespace Utility {
    auto constexpr kWall{'W'};
    auto constexpr kEnemy{'E'};
    auto constexpr kEmpty{'0'};
}

class Solution {
public:
    using Arr2dT = std::vector<std::vector<char>>;
// let 'r' by 'c'  be a size of the given grid
// time complexity O(r * c)
// space complexity O(c)
// runtime 0 ms, beats 100.00 %
    int maxKilledEnemies(Arr2dT & grid_) const;
};

int Solution::maxKilledEnemies(Arr2dT & grid_) const {
    using namespace Utility;
    if(grid_.empty() || grid_.at(0).empty()) {
        return 0;
    }
    auto const rowsCount{grid_.size()};
    auto const colsCount{grid_.at(0).size()};
    auto killsCountMax{0};
    auto killsRowCount{0};
    auto killsColCount{std::vector<int>(colsCount, 0)};
    for(auto r{0}; r < rowsCount; ++r) {
        for(auto c{0}; c < colsCount; ++c) {
            if(c == 0 || grid_[r][c - 1] == kWall) {
                killsRowCount = 0;
                for(auto k{c}; k < colsCount; ++k) {
                    if(grid_[r][k] == kWall) {
                        break;        
                    } else if(grid_[r][k] == kEnemy) {
                        ++killsRowCount;
                    }
                }
            }
            if(r == 0 || grid_[r - 1][c] == kWall) {
                killsColCount[c] = 0;
                for(auto k{r}; k < rowsCount; ++k) {
                    if(grid_[k][c] == kWall) {
                        break;
                    } else if(grid_[k][c] == kEnemy) {
                        ++killsColCount[c];
                    }
                }
            }
            if(grid_[r][c] == kEmpty) {
                killsCountMax = std::max(killsCountMax,
                    killsRowCount + killsColCount[c]);
            }
        }
    }
    return killsCountMax;
}
