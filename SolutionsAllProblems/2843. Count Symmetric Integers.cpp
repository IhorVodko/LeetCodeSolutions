// problem : https://leetcode.com/problems/count-symmetric-integers/description/
// submission : https://leetcode.com/problems/count-symmetric-integers/submissions/1603720541
// solution post : https://leetcode.com/problems/count-symmetric-integers/solutions/6640152/
//     c-modern-readable-code-beats-95-runtime-dquz4

// #include <algorithm>

namespace Utility {
    auto constexpr kTwoDigitsUpperBound{99};
    auto constexpr kFourDigitsLowerBound{1'000};
    auto constexpr kFourDigitsUpperBound{9'999};
}

// let 'l' be a value of 'lowerBound_'
// 'u' - value of 'upperBound_'
// time complexity O(u - l)
// space complexity O(u - l)
// runtime 3 ms, beats 95.31 %
class Solution {
public:
    int countSymmetricIntegers(
        int const lowerBound_,
        int const upperBound_
    ) const;
};

int Solution::countSymmetricIntegers(
    int const lowerBound_,
    int const upperBound_
) const {
    using namespace Utility;
    auto symmetricNumsCount{0};
    auto const twoDigitsUpperBound{std::min(
        kTwoDigitsUpperBound, upperBound_)};
    for(auto num{lowerBound_}; num <= twoDigitsUpperBound; ++num) {
        symmetricNumsCount += num % 11 == 0 ? 1 : 0; 
    }
    if(upperBound_ < kFourDigitsLowerBound) {
        return symmetricNumsCount;
    }
    auto const fourDigitsLowerBound{std::max(
        kFourDigitsLowerBound, lowerBound_)};
    auto const fourDigitsUpperBound{std::min(
        kFourDigitsUpperBound, upperBound_)};
    for(auto num{fourDigitsLowerBound}; num <= fourDigitsUpperBound; ++num) {
        auto const leftDigitsSum{num / 1'000 + (num % 1'000) / 1'00}; 
        auto rightDigitsSum{(num % 100) / 10 + num % 10};
        symmetricNumsCount += leftDigitsSum == rightDigitsSum ? 1 : 0;
    }
    return symmetricNumsCount;
}
