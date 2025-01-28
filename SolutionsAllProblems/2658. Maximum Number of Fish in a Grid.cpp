// problem : https://leetcode.com/problems/maximum-number-of-fish-in-a-grid/description/
// submission : https://leetcode.com/problems/maximum-number-of-fish-in-a-grid/submissions/1523574080
// solution post : https://leetcode.com/problems/maximum-number-of-fish-in-a-grid/solutions/6341202/c-modern-readable-code-optimal-time-comp-ckso

// #include <algorithm>
// #include <limit>
// #include <queue>
// #include <vector>

// let 'r' a number of rows of the given matrix 
// 'c' - columns of the given matrix
// time complexity O(n * m)
// space complexity O(1)
// runtime 50 ms, beats 9.28 %
class Solution {
public:
    using Mx = std::vector<std::vector<int>>;
    int findMaxFish(Mx & grid) const {
        auto rs{grid.size()};
        auto cs{grid.at(0).size()};
        auto maxFishCount{0};
        for(auto r{size_t{0}}; r < rs; ++r) {
            for(auto c{size_t{0}}; c < cs; ++c) {
                if(grid.at(r).at(c) == 0) {
                    continue;
                }
                maxFishCount = std::max(maxFishCount, CountFish(grid, r, c));
            }
        }
        return maxFishCount; 
    }
    Solution():
        moves{{-1, 0}, {0, -1}, {0, 1}, {1, 0}}
    {}
private:
    int CountFish(
        Mx & grid,
        int const r,
        int const c
    ) const {
        auto cells{std::queue<std::pair<int, int>>{}};
        cells.push({r, c});
        auto fishCount{0};
        auto rCurr{std::numeric_limits<int>::min()};
        auto cCurr{std::numeric_limits<int>::min()};
        auto rNext{std::numeric_limits<int>::min()};
        auto cNext{std::numeric_limits<int>::min()};
        while(!cells.empty()) {
            rCurr = cells.front().first;
            cCurr = cells.front().second;
            cells.pop();
            fishCount += grid.at(rCurr).at(cCurr);
            grid.at(rCurr).at(cCurr) = 0;
            for(auto const & move: moves) {
                rNext = rCurr + move.first;
                cNext = cCurr + move.second;
                if(IsValidCell(rNext, cNext, grid)) {
                    cells.push({rNext, cNext, });
                }
            }
        }
        return fishCount;
    }
    bool IsValidCell(
        int const r,
        int const c,
        Mx const & grid
    ) const {
        return 0 <= r && r < grid.size() && 0 <= c && c < grid.at(0).size() &&
            grid.at(r).at(c) != 0;
    }
    std::vector<std::pair<int, int>> moves;
};
