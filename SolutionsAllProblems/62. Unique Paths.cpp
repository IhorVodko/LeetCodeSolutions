// problem : https://leetcode.com/problems/unique-paths/description/  
// submission : https://leetcode.com/problems/unique-paths/submissions/1833319064
// solution post : https://leetcode.com/problems/unique-paths/solutions/7357780/
//    c-modern-readable-code-beats-100-runtime-y9kl

// import std;

class Solution {
public:
// let 'n' by 'm' be the size of a given matrix
// time complexity O(n * m)
// space complexity O(m)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto uniquePaths(
        int const rowsCnt_,
        int const colsCnt_
    ) const -> int;
};

auto Solution::uniquePaths(
    int const rowsCnt_,
    int const colsCnt_
) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto dpPrev{std::vector<int>(colsCnt_, 1)};
    auto dpCurr{std::vector<int>(colsCnt_, 1)};
    for(auto const r: vs::iota(1, rowsCnt_)) {
        for(auto const c: vs::iota(1, colsCnt_)) {
            dpCurr[c] = dpPrev[c] + dpCurr[c - 1];
        }
        dpPrev = dpCurr;
    }
    auto const pathsTotalCnt{dpPrev.back()};
    return pathsTotalCnt;
}
