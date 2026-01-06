// problem : https://leetcode.com/problems/maximum-matrix-sum/description
// submission : https://leetcode.com/problems/maximum-matrix-sum/submissions/1876609994
// solution post : https://leetcode.com/problems/maximum-matrix-sum/solutions/7472424/
//    c-modern-readable-code-beats-100-runtime-qifr

// import std;

// let 'n' by 'n' be the matrix size
// time complexity O(n^2)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto maxMatrixSum(std::vector<std::vector<int>> const & mx_) const -> long long;
};

auto Solution::maxMatrixSum(std::vector<std::vector<int>> const & mx_) const -> long long {
    auto sum{0ll};
    auto minAbsNum{std::numeric_limits<int>::max()};
    auto negCnt{0};
    for(auto const & row: mx_) {
        for(auto const num: row) {
            negCnt += num < 0 ? 1 : 0;
            auto const absNum{std::abs(num)};
            sum += absNum;
            minAbsNum = std::min(minAbsNum, absNum);
        }
    }
    sum -= negCnt % 2 == 0 ? 0 : 2 * minAbsNum;
    return sum;
}
