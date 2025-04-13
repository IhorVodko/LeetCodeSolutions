// problem : https://leetcode.com/problems/find-the-count-of-good-integers/description/
// submission : https://leetcode.com/problems/find-the-count-of-good-integers/submissions/1605765378
// solution post : https://leetcode.com/problems/find-the-count-of-good-integers/solutions/6647244/
//     c-modern-readable-code-optimal-time-comp-w0gx

// #include <algorithm>
// #include <array>
// #include <vector>
// #include <unordered_set>

// let 'n' be a given count of digits
// time complexity O(n * log(n) * 10^((n + 1) / 2))
// space complexity O(n * 10^((n + 1) / 2))
// runtime 651 ms, beats 24.64 %
class Solution {
public:
    long long countGoodIntegers(
        int const digitsCount_,
        int const divisor_
    ) const;
};
 
long long Solution::countGoodIntegers(
    int const digitsCount_,
    int const divisor_
) const {
    auto dictGoodNumStrs{std::unordered_set<std::string>{}};
    auto const base{static_cast<int>(std::pow(10, (digitsCount_ - 1)/ 2))};
    auto const skip{digitsCount_ & 1};
    for(auto num{base}; num < base * 10; ++num) {
        auto numStr{std::to_string(num)};
        numStr = std::to_string(num);
        numStr += std::string{numStr.rbegin() + skip, numStr.rend()};
        auto const palindromicInteger{std::stoll(numStr)};
        if(palindromicInteger % divisor_ == 0) {
            std::sort(numStr.begin(), numStr.end());
            dictGoodNumStrs.emplace(numStr);
        }
    }
    auto factorials{std::vector<long long>(digitsCount_ + 1, 1)};
    auto goodNumsCount{0LL};
    for(auto digitCount{1}; digitCount <= digitsCount_; ++digitCount) {
        factorials[digitCount] = factorials[digitCount - 1] * digitCount;
    }
    auto digitsCount{std::array<int, 10>()};
    for(auto const & goodNumStr: dictGoodNumStrs) {
        digitsCount.fill(0);
        for(auto const digitChr: goodNumStr) {
            ++digitsCount.at(digitChr - '0');
        }
        auto goodNumsCountCurr{(digitsCount_ - digitsCount[0]) *
            factorials[digitsCount_ - 1]}; 
        for(auto const digitCount: digitsCount) {
            goodNumsCountCurr /= factorials.at(digitCount);
        }
        goodNumsCount += goodNumsCountCurr;
    }
    return goodNumsCount;
}
