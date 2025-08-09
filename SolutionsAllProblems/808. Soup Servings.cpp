// problem : https://leetcode.com/problems/soup-servings/description
// submission : https://leetcode.com/problems/soup-servings/submissions/1729107183
// solution post : https://leetcode.com/problems/soup-servings/solutions/7061526/
//    c-modern-readable-code-optimal-time-comp-envb

// #include <cmath>
// #include <ranges>
// #include <vector>
// #include <unordered_map>

namespace Util {
    inline auto constexpr kError{1e-5};
    inline auto constexpr kLowerBound{1.0 - kError};
    inline auto constexpr kLimit{1.0};
    inline auto constexpr kServingSz{25.0};
}

class Solution {
public:
// let 'n' be a given volume
// time complexity O(1)
// space complexity O(1)
// runtime 146 ms, beats 8.08 %
    [[nodiscard]]
    double soupServings(int const startVolume_) const;
private:

};

double Solution::soupServings(int const startVolume_) const {
    namespace views = std::views;
    using namespace Util;
    auto const totalServingsCount{static_cast<int>(std::ceil(
        startVolume_ / kServingSz))};
    auto mxProbability{std::unordered_map<int, unordered_map<int, double>>{}};
    std::function<double(int const, int const)> const calculateProbability{
        [&] (
            int const servingsA_,
            int const servingsB_
        ) {
            if(servingsA_ <= 0 && servingsB_ <= 0) {
                return 0.5;
            }else if(servingsA_ <= 0) {
                return 1.0;
            }else if(servingsB_ <= 0) {
                return 0.0;
            }
            if( mxProbability.contains(servingsA_) &&
                mxProbability.at(servingsA_).contains(servingsB_)
            ) {
                return mxProbability.at(servingsA_).at(servingsB_);
            }
            return mxProbability[servingsA_][servingsB_] = (
                calculateProbability(servingsA_ - 4, servingsB_) +
                calculateProbability(servingsA_ - 3, servingsB_ - 1) +
                calculateProbability(servingsA_ - 2, servingsB_ - 2) +
                calculateProbability(servingsA_ - 1, servingsB_ - 3)) /
                4;
        }
    };
    for(auto const currServingsCount: views::iota(0, totalServingsCount)) {
        auto const currProbability(calculateProbability(
            currServingsCount,
            currServingsCount));
        if(currProbability > kLowerBound) {
            return kLimit;
        }
    }
    auto const resultProbability{calculateProbability(
        totalServingsCount,
        totalServingsCount)};
    return resultProbability;   
}
