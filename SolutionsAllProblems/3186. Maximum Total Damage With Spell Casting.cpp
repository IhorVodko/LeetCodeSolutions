// problem : https://leetcode.com/problems/maximum-total-damage-with-spell-casting/description/
// submission : https://leetcode.com/problems/maximum-total-damage-with-spell-casting/submissions/1798611986
// solution post : https://leetcode.com/problems/maximum-total-damage-with-spell-casting/solutions/7267573/
//    c-modern-readable-code-optimal-time-comp-66wr

// import std;

class Solution {
public:
// let 'n' be the number of the given powers
// time complexity O(n * log(n))
// space complexity O(n)
// runtime 80 ms, beats 93.41 %
    [[nodiscard]]
    auto maximumTotalDamage(
        std::vector<int> & powers_
    ) const -> long long;

private:
    inline static int constexpr kMinDiff{2};
    inline static bool const kIsFastIO{
        [] () {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return true;
        } ()
    };
};

auto Solution::maximumTotalDamage(
    std::vector<int> & powers_
) const -> long long {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    assert(!powers_.empty());

    auto const powersSz{std::ssize(powers_)};
    rngs::sort(powers_);
    auto prevIdxs{std::vector<int>(powersSz, -1)};
    for(auto prevPowerIdx{0};
        auto const currPowerIdx: vs::iota(1, powersSz)
    ) {
        auto const currPower{powers_.at(currPowerIdx)};
        auto prevPower{powers_.at(prevPowerIdx)};
        while(currPower - prevPower > kMinDiff) {
            prevPower = powers_.at(++prevPowerIdx);
        }
        prevIdxs.at(currPowerIdx) = prevPowerIdx - 1;
    }
    auto dpMaxDmgs{std::vector<long long>(powersSz)};
    for(auto currPowerIdx{0}; currPowerIdx < powersSz;) {
        auto samePowerCnt{1ll};
        auto currPowerIdxCopy{currPowerIdx};
        while(
            currPowerIdx < powersSz - 1 &&
            powers_.at(currPowerIdx) == powers_.at(currPowerIdx + 1)
        ) {
            ++samePowerCnt;
            ++currPowerIdx;
        }
        auto & currMaxDmg{dpMaxDmgs.at(currPowerIdx)};
        auto const prevIdx{prevIdxs.at(currPowerIdx)};
        auto const currPower{powers_.at(currPowerIdx)};
        auto currDmg1{currPower * samePowerCnt};
        if(prevIdx > -1) {
            auto const prevMaxDmg{dpMaxDmgs.at(prevIdx)};
            currDmg1 += prevMaxDmg;
        }
        auto currDmg2{0ll};
        if(currPowerIdxCopy >= 1) {
            auto const prevMaxDmg{dpMaxDmgs.at(currPowerIdxCopy - 1)};
            currDmg2 += prevMaxDmg;
        }
        currMaxDmg = std::max(currDmg1, currDmg2);         
        ++currPowerIdx;
    }
    auto const maxDmg{dpMaxDmgs.at(powersSz - 1)};
    return maxDmg;
}
