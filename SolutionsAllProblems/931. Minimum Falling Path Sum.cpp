// problem : https://leetcode.com/problems/minimum-falling-path-sum/description/
// submission : https://leetcode.com/problems/minimum-falling-path-sum/submissions/1838616395
// solution post : https://leetcode.com/problems/minimum-falling-path-sum/solutions/7371782/
//    c-modern-readable-code-beats-100-runtime-y7sd

// import std;

class Solution {
public:
// let 'n'by 'n' be the size of a given matrix
// time complexity O(n^2)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto minFallingPathSum(
        std::span<std::vector<int>> const mx_
    ) const -> int;
};

auto Solution::minFallingPathSum(
    std::span<std::vector<int>> const mx_
) const -> int {
    namespace vs = std::views;

    auto const rcCnt{std::ssize(mx_)};
    if(rcCnt == 1) {
        return mx_[0][0];
    }
    auto minSum{std::numeric_limits<int>::max()};
    for(auto const r: vs::iota(1, rcCnt)) {
        for(auto const c: vs::iota(0, rcCnt)) {
            auto minNum{mx_[r - 1][c]};
            if(c >= 1) {
                minNum = std::min(minNum, mx_[r - 1][c - 1]);
            }
            if(c + 1 < rcCnt) {
                minNum = std::min(minNum, mx_[r - 1][c + 1]);
            }
            mx_[r][c] += minNum;
            if(r + 1 == rcCnt) {
                minSum = std::min(minSum, mx_[r][c]);
            }
        }
    }
    return minSum;
}
