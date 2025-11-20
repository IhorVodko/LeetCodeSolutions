// problem : https://leetcode.com/problems/minimum-path-sum/description/
// submission : https://leetcode.com/problems/minimum-path-sum/submissions/1835266016
// solution post : https://leetcode.com/problems/minimum-path-sum/solutions/7362940/
//    c-modern-readable-code-beats-100-runtime-4nib

// import std;

class Solution {
public:
// let 'n' by 'm' be the size of a given grid
// time complexity O(n + m)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto minPathSum(
        std::span<vector<int>> const grid_
    ) const -> int;

private:
    static int constexpr kMaxInt{std::numeric_limits<int>::max()};
};

auto Solution::minPathSum(
    std::span<vector<int>> const grid_
) const -> int {
    namespace vs = std::views;

    auto const rCnt{std::ssize(grid_)};
    auto const cCnt{std::ssize(grid_[0])};
    for (auto const r: vs::iota(0, rCnt)) {
        for (auto const c: vs::iota(0, cCnt)) {
            if(r == 0 && c == 0) [[unlikely]] {
                continue;
            }
            grid_[r][c] += std::min(
                r >= 1 ? grid_[r - 1][c] : kMaxInt,
                c >= 1 ? grid_[r][c - 1] : kMaxInt 
            );
        }
    }
    auto const minSum{grid_.back().back()};
    return minSum;
}
