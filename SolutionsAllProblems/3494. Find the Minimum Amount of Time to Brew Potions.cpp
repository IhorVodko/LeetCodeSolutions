// problem : https://leetcode.com/problems/find-the-minimum-amount-of-time-to-brew-potions/description/
// submission : https://leetcode.com/problems/find-the-minimum-amount-of-time-to-brew-potions/submissions/1796632568
// solution post : https://leetcode.com/problems/find-the-minimum-amount-of-time-to-brew-potions/solutions/7262396/
//    c-modern-readable-code-optimal-time-comp-sfh8

// import std;

class Solution {
public:
// let 's' be the length of the given skills array
// 'm' - of the mana array
// time complexity O(s * m);
// space complexity O(1)
// runtime 376 ms, beats 68.18 %
    [[nodiscard]]
    auto minTime(
        std::vector<int> & skills_,
        std::vector<int> const & manas_
    ) const -> long long;

private:
    inline static bool const kIsFastIO{
        [] () {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return true;
        } ()
    };
};

auto Solution::minTime(
    std::vector<int> & skills_,
    std::vector<int> const & manas_
) const -> long long {
    namespace vs = std::views;

    auto const skillsSz{std::ssize(skills_)};
    auto const manasSz{std::ssize(manas_)};
    std::partial_sum(skills_.cbegin(), skills_.cend(), skills_.begin());
    auto const skill0{skills_.at(0)};
    auto startTime{0ll};
    for(auto const manaIdx: vs::iota(1, manasSz)) {
        auto const prevMana{static_cast<long long>(manas_.at(manaIdx - 1))};
        auto const currMana{static_cast<long long>(manas_.at(manaIdx))};
        auto maxTime{skill0 * prevMana};
        for(auto const skillIdx: vs::iota(1, skillsSz)) {
            auto const time1{skills_.at(skillIdx) * prevMana};
            auto const time2{skills_.at(skillIdx -1) * currMana};
            auto const currTime{time1 - time2};
            maxTime = std::max(maxTime, currTime);
        }
        startTime += maxTime;
    }
    auto minTime{
        static_cast<long long>(skills_.at(skillsSz - 1)) *
        manas_.at(manasSz - 1)};
    minTime += startTime;
    return minTime;
}
