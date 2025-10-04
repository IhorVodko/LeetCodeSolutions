// problem : https://leetcode.com/problems/maximal-square/description/
// submission : https://leetcode.com/problems/maximal-square/submissions/1790914602
// solution post : https://leetcode.com/problems/maximal-square/solutions/7247576/
//    c-modern-readable-code-beats-100-runtime-158r

// import std;

class Solution {
public:
    using mxT = std::vector<std::vector<char>>;

// let 'n' by 'm' be the size of the given matrix
// time complexity O(n * m)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto maximalSquare(mxT const & mx_) const -> int;

private:
    inline static bool const kIsFastIO{
        [] () {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return true;
        } ()
    };
};

auto Solution::maximalSquare(mxT const & mx_) const -> int {
    namespace vs = std::views;

    auto const rCnt{std::ssize(mx_)};
    auto const cCnt{std::ssize(mx_.at(0))};
    auto dp{std::vector<int>(cCnt + 1)};
    auto currMaxSide{0};
    auto prevMaxSide{0};
    for(auto const r: vs::iota(1, rCnt + 1)) {
        for(auto const c: vs::iota(1, cCnt + 1)) {
            auto & currSide{dp.at(c)};
            auto const tempMaxSide{currSide};
            auto const cellVal{mx_.at(r - 1).at(c - 1)};
            if(cellVal == '1') {
                currSide = std::min(
                    std::min(dp.at(c - 1), prevMaxSide),
                    currSide
                ) + 1;
                currMaxSide = std::max(currMaxSide, currSide);
            } else {
                currSide = 0;
            }
            prevMaxSide = tempMaxSide;
        }
    }
    auto const maxSquareArea{currMaxSide * currMaxSide};
    return maxSquareArea;
}
