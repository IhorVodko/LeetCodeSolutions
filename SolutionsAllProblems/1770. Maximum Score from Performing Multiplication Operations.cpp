// problem : https://leetcode.com/problems/maximum-score-from-performing-multiplication-operations/description/
// submission : https://leetcode.com/problems/maximum-score-from-performing-multiplication-operations/submissions/
//    1788258819
// solution post : https://leetcode.com/problems/maximum-score-from-performing-multiplication-operations/solutions/7239698/
//    c-modern-readable-code-beats-100-runtime-1nab

// import std;

class Solution {
public:
// let 'n' be the count of the given numbers
// time complexity O(n^2)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto maximumScore(
        std::vector<int> const & nums_,
        std::vector<int> const & mults_
    ) const -> int;

private:
    inline static bool const kIsFastIO{
        [] () {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return true;
        } ()
    };
};

auto Solution::maximumScore(
    std::vector<int> const & nums_,
    std::vector<int> const & mults_
) const -> int {
    namespace views = std::views;

    assert(nums_.size() >= mults_.size());
    auto const numsSz{std::ssize(nums_)};
    auto const multsSz{std::ssize(mults_)};
    auto dpMaxScores{std::valarray<int>(0, multsSz + 1)};
    for(auto const opIdx: views::iota(0, multsSz) | views::reverse) {
        for(auto const numLeftIdx: views::iota(0, opIdx + 1)) {
            auto const score1{
                mults_[opIdx] * nums_[numLeftIdx] +
                dpMaxScores[numLeftIdx + 1]};
            auto const numRightIdx{numsSz - (opIdx - numLeftIdx) - 1};
            auto const score2{
                mults_[opIdx] * nums_[numRightIdx] +
                dpMaxScores[numLeftIdx]};
            dpMaxScores[numLeftIdx] = std::max(score1, score2);
        }
    }
    auto const maxScore{dpMaxScores[0]};
    return maxScore;
}
