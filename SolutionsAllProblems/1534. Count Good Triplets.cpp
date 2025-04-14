// problem : https://leetcode.com/problems/count-good-triplets/description/
// submission : https://leetcode.com/problems/count-good-triplets/submissions/1606935931
// solution post : https://leetcode.com/problems/count-good-triplets/solutions/6651418/
//     c-modern-readable-code-beats-100-runtime-zlbz

// #include <algorithm>
// #include <vector>

// let 'n' be a count of given numbers
// 'u' - upper limit of the numbers
// time complexity O(n^2 + n * u)
// space complexity O(u)
// runtime 0 ms, beats 100.00 %
namespace Utility {
    auto constexpr kNumsLowerLimit{0};
    auto constexpr kNumsUpperLimit{1000};
}
class Solution {
public:
    int countGoodTriplets(
        std::vector<int> const & nums_,
        int const a_,
        int const b_,
        int const c_
    ) const;
};

int Solution::countGoodTriplets(
    std::vector<int> const & nums_,
    int const a_,
    int const b_,
    int const c_
) const {
    using namespace Utility;
    auto goodTripletsCount{0};
    auto const numsCount{nums_.size()};
    auto prefixSumsOfValidNum1Count{std::vector<int>(kNumsUpperLimit + 1, 0)};
    auto const numsEnd{nums_.end()};
    for(auto num2It{nums_.begin()}; num2It < numsEnd; ++num2It) {
        for(auto num3It{num2It + 1}; num3It < numsEnd; ++num3It) {
            if(std::abs(*num2It - *num3It) > b_) {
                continue;
            }
            auto const num1LowerBoundA{*num2It - a_};
            auto const num1UpperBoundA{*num2It + a_};
            auto const num1LowerBoundC{*num3It - c_};
            auto const num1UpperBoundC{*num3It + c_};
            auto const num1LowerBound{std::max(kNumsLowerLimit,
                std::max(num1LowerBoundA, num1LowerBoundC))};
            auto const num1UpperBound{std::min(kNumsUpperLimit,
                std::min(num1UpperBoundA, num1UpperBoundC))};
            if(num1LowerBound > num1UpperBound) {
                continue;
            }
            goodTripletsCount += prefixSumsOfValidNum1Count.at(num1UpperBound);
            if(num1LowerBound != kNumsLowerLimit) {
                goodTripletsCount -=
                    prefixSumsOfValidNum1Count.at(num1LowerBound - 1);
            }
        }
        std::for_each(prefixSumsOfValidNum1Count.begin() + *num2It,
            prefixSumsOfValidNum1Count.end(), [] (auto & sum) {++sum;});
    }
    return goodTripletsCount;
}
