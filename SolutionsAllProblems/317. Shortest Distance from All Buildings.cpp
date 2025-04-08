// problem : https://leetcode.com/problems/shortest-distance-from-all-buildings/description/
// submission : https://leetcode.com/problems/shortest-distance-from-all-buildings/submissions/1600765550
// solution post : https://leetcode.com/problems/shortest-distance-from-all-buildings/solutions/6629856/
//     c-modern-readable-code-optimal-time-comp-7hb4

// #include <algorithm>
// #include <limits>
// #include <queue>
// #include <vector>

namespace Utility {
    auto constexpr moves{std::array<std::pair<int, int>, 4>{{
        {-1, 0}, {0, -1}, {0, 1}, {1, 0}}}};
    auto constexpr maxDistance{std::numeric_limits<int>::max()};
    auto constexpr houseVal{1};
}

// let 'r' by 'c' be dimensions of the given grid
// time complexity O(r^2 * c^2)
// space complexity O(r * c)
// runtime 187 ms, beats 82.07 %
class Solution {
public:
    using Arr2T = std::vector<std::vector<int>>;
    using CellT = std::pair<int, int>;
    int shortestDistance(Arr2T & grid_) const;
private:
    bool IsCellWithinGrid(
        Arr2T const & grid_,
        CellT const  & cell_
    ) const;
};

int Solution::shortestDistance(Arr2T & grid_) const {
    using namespace Utility;
    auto const rowsCount{grid_.size()};
    auto const colsCount{grid_.at(0).size()};
    auto distancesFromAllHouses{Arr2T(rowsCount,
        std::vector<int>(colsCount, 0))};
    auto emptyLandVal{0};
    auto minDist{maxDistance};
    for(auto r{0}; r < rowsCount; ++r) {
        for(auto c{0}; c < colsCount; ++c) {
            if(grid_[r][c] != houseVal) {
                continue;
            }
            minDist = maxDistance;
            auto cells{std::queue<CellT>{}};
            cells.emplace(r, c);
            auto distance{0};
            while(!cells.empty()) {
                ++distance;
                for(auto cellsCount{cells.size()}; cellsCount > 0;
                    --cellsCount
                ) {
                    auto const [currR, currC]{cells.front()};
                    cells.pop();
                    for(auto const [moveR, moveC]: moves) {
                        auto const nextR{currR+ moveR};
                        auto const nextC{currC + moveC};
                        if(!(IsCellWithinGrid(grid_, {nextR, nextC}) &&
                            grid_[nextR][nextC] == emptyLandVal)
                        ) {
                            continue;
                        }
                        --grid_[nextR][nextC];
                        distancesFromAllHouses[nextR][nextC] += distance;
                        cells.emplace(nextR, nextC);
                        minDist = std::min(minDist, 
                            distancesFromAllHouses[nextR][nextC]);
                    }
                }
            }
            --emptyLandVal;
        }
    }
    return minDist == maxDistance ? -1 : minDist;
}

bool Solution::IsCellWithinGrid(
    Arr2T const & grid_,
    CellT const  & cell_
) const {
    auto const [r, c]{cell_};
    auto const rowsCount{grid_.size()};
    auto const colsCount{grid_.at(0).size()};
    return 0 <= r && r < rowsCount && 0 <= c && c < colsCount;
}
