// problem : https://leetcode.com/problems/new-21-game/description/?envType=daily-question&envId=2025-08-17
// submission : https://leetcode.com/problems/new-21-game/submissions/1738619851
// solution post : https://leetcode.com/problems/new-21-game/solutions/7092589
//    /c-modern-readable-code-optimal-time-comp-2agt

// #include <numeric>
// #include <ranges>
// #include <vector>

class Solution {
public:
// let 'n' be a given upper limit score
// time complexity O(n)
// space complexity O(n)
// runtime 3 ms, beats 61.18 %
    [[nodiscard]]
    double new21Game(
        int const upperLimitScore_,
        int const targetScore_,
        int const maxPoints_
    ) const;
};

double Solution::new21Game(
    int const upperLimitScore_,
    int const targetScore_,
    int const maxPoints_
) const {
    namespace views = std::views;
    auto probabilitiesOfScores{std::vector<double>(upperLimitScore_ + 1, 0)};
    probabilitiesOfScores.at(0) = 1;
    auto sumProbability{targetScore_ > 0 ? 1.0 : 0.0};
    for(auto const score: views::iota(1, upperLimitScore_ + 1)) {
        probabilitiesOfScores.at(score) = sumProbability / maxPoints_;
        if(score < targetScore_) {
            sumProbability += probabilitiesOfScores.at(score);
        }
        auto const pointsLeft{score - maxPoints_};
        if(0 <= pointsLeft && pointsLeft < targetScore_) {
            sumProbability -= probabilitiesOfScores.at(pointsLeft);
        }
    }
    auto const upperLimitScoreProbability{std::accumulate(
        probabilitiesOfScores.cbegin() + targetScore_,
        probabilitiesOfScores.cend(),
        0.0)};
    return upperLimitScoreProbability;
}
