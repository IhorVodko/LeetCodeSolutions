// problem : https://leetcode.com/problems/minimum-score-triangulation-of-polygon/description
// submission : https://leetcode.com/problems/minimum-score-triangulation-of-polygon/submissions/1786203480
// solution post : https://leetcode.com/problems/minimum-score-triangulation-of-polygon/solutions/7233487/
//    c-modern-readable-code-beats-100-runtime-6jqk

// import std;

class Solution {
public:
// let 'n' be the count of the given values
// time complexity O(n^3)
// space complexity O(n^2)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto minScoreTriangulation(std::vector<int> const & vals_) -> int;

private:
    inline static constexpr int kMaxValsSz{50};
    inline static bool const kIsFastIO{
        [] () {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return true;
        } ()
    };
};

auto Solution::minScoreTriangulation(
    std::vector<int> const & vals_
) -> int {
        namespace views = std::views;
        using intT = std::numeric_limits<int>;
        using dpT =  std::array<std::array<int, kMaxValsSz>, kMaxValsSz>;

        auto const valsSz{std::ssize(vals_)};
        auto lowAndHighToMinScore{dpT{}};
        for(auto const valsSzCurr: views::iota(2, valsSz)) {
            for(auto const low: views::iota(0, valsSz - valsSzCurr)) {
                auto const high{low + valsSzCurr};
                lowAndHighToMinScore.at(low).at(high) = intT::max();
                for(auto const mid: views::iota(low + 1, high)) {
                    auto const scoreIncrement{
                        vals_.at(low) * vals_.at(mid) * vals_.at(high)};
                    auto const minScoreLowMid{
                        lowAndHighToMinScore.at(low).at(mid)};
                    auto const minScoreMidHigh{
                        lowAndHighToMinScore.at(mid).at(high)};
                    auto const currScoreLowHigh{
                        scoreIncrement + minScoreLowMid + minScoreMidHigh};
                    auto & minScoreLowHigh{
                        lowAndHighToMinScore.at(low).at(high)};
                    minScoreLowHigh =
                        std::min(minScoreLowHigh, currScoreLowHigh);
                }
            }
        }
        auto minScore{lowAndHighToMinScore.at(0).at(valsSz - 1)};
        return minScore;
}
