// problem : https://leetcode.com/problems/unique-paths-ii/description/
// submission : https://leetcode.com/problems/unique-paths-ii/submissions/1834341752
// solution post : https://leetcode.com/problems/unique-paths-ii/solutions/7360713/
//    c-modern-readable-code-beats-100-runtime-u0k0

// import std;

class Solution {
public:
// let 'n' by 'm' be the size of a given grid
// time complexity O(n * m)
// space complexity O(n * m)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto uniquePathsWithObstacles(
        std::span<std::vector<int>> const grid_
    ) const -> int;

private:
    static int constexpr kIsObstacle{1};
};

auto Solution::uniquePathsWithObstacles(
    std::span<std::vector<int>> const grid_
) const -> int {
    namespace vs = std::views;

    if(grid_[0][0] == 1) {
        return 0;
    }
    auto const rCnt{std::ssize(grid_)};
    auto const cCnt{std::ssize(grid_[0])};
    for(auto const r: vs::iota(0, rCnt)) {
        for(auto const c: vs::iota(0, cCnt)) {
            if(grid_[r][c] == kIsObstacle) {
                grid_[r][c] = -kIsObstacle;
            }
        }
    }
    grid_[0][0] = 1;
    for(auto const r: vs::iota(0, rCnt)) {
        for(auto const c: vs::iota(0, cCnt)) {
            if(grid_[r][c] == -1) {
                grid_[r][c] = 0;
                continue;
            }
            if(r >= 1) [[likely]] {
                grid_[r][c] += grid_[r - 1][c];
            }
            if(c >= 1) [[likely]] {
                grid_[r][c] += grid_[r][c - 1];
            }
        }
    }
    auto const pathsTotalCnt{grid_.back().back()};
    return pathsTotalCnt;
}
