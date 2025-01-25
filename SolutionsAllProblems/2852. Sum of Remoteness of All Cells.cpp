// problem : https://leetcode.com/problems/sum-of-remoteness-of-all-cells/description/
// submission : https://leetcode.com/problems/sum-of-remoteness-of-all-cells/submissions/1520102523
// solution post : https://leetcode.com/problems/sum-of-remoteness-of-all-cells/solutions/6328220/c-modern-readable-code-optimal-time-comp-72ae

// #include <vector>
// #include <utility>

// let 'n' be a parameter 'grid' length
// time complexity O(n^2)
// space complexity O(n^2)
// runtime 39 ms, beats 76.12 %
class Solution {
public:
    using Mx = std::vector<std::vector<int>>;
    long long sumRemoteness(Mx & grid) const {
        auto const gridSz{grid.size()};
        auto gridSum{0LL};
        for(auto r{0}; r < gridSz; ++r) {
            for(auto c{0}; c < gridSz; ++c) {
                if(grid.at(r).at(c) != -1) {
                    gridSum += grid.at(r).at(c);        
                }
            }
        }
        auto gridRemotness{0LL};
        auto areaSumAndCount{std::pair<long long, size_t>{}};
        for(auto r{0}; r < gridSz; ++r) {
            for(auto c{0}; c < gridSz; ++c) {
                if(grid.at(r).at(c) > 0) {
                    areaSumAndCount = {0, 0};
                    DoDfs(grid, areaSumAndCount, r, c);
                    gridRemotness += (gridSum - areaSumAndCount.first) *
                        areaSumAndCount.second;
                }
            }
        }
        return gridRemotness;
    }
    Solution(): 
        moves{{0, -1}, {0, 1}, {-1, 0}, {1, 0}}
    {}
private: 
    void DoDfs(
        Mx & grid,
        std::pair<long long, size_t> & areaSumAndCount,
        int const r,
        int const c
    ) const {
        areaSumAndCount.first += grid.at(r).at(c);
        ++areaSumAndCount.second;
        grid.at(r).at(c) = -1;
        auto nextR{-1};
        auto nextC{-1};
        for(auto const & move: moves) {
            nextR = r + move.first;
            nextC = c + move.second;
            if(IsValidCell(nextR, nextC, grid)) {
                DoDfs(grid, areaSumAndCount, nextR, nextC);
            }
        }
    }
    bool IsValidCell(
        int const r,
        int const c,
        Mx const & grid
    ) const {
        auto const sz{grid.size()};
        return 0 <= r && r < sz && 0 <= c && c < sz && grid.at(r).at(c) > 0;
    }
    std::vector<std::pair<int, int>> moves;
};
