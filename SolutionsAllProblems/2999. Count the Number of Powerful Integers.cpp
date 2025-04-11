// problem : https://leetcode.com/problems/count-the-number-of-powerful-integers/description/
// submission : https://leetcode.com/problems/count-the-number-of-powerful-integers/submissions/1603685160
// solution post : https://leetcode.com/problems/count-the-number-of-powerful-integers/solutions/6640043/
//     c-modern-readable-code-beats-100-runtime-dc8l

// #include <cmath>
// #include <string>
// #include <vector>

// let 'n' be a value of 'finishNum_' parameter
// time complexity O(log10(n))
// space complexity O(log10(n))
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    long long numberOfPowerfulInt(
        long long const startNum_,
        long long const finishNum_,
        int const limitDigit_,
        std::string const & suffixStr_
    ) const {
        auto const startStr{std::to_string(startNum_ - 1)};
        auto const finishStr{std::to_string(finishNum_)};
        return CountPowerfulNums(finishStr, suffixStr_, limitDigit_) -
            CountPowerfulNums(startStr, suffixStr_, limitDigit_);
    }
    long long CountPowerfulNums(
        std::string const & strFinish_,
        std::string const & suffixStr_,
        int const limitDigit_
    ) const {
        if(strFinish_.length() < suffixStr_.length()) {
            return 0;
        }
        if(strFinish_.length() == suffixStr_.length()) {
            return strFinish_ >= suffixStr_ ? 1 : 0;
        }
        auto const suffixStr{strFinish_.substr(
            strFinish_.length() - suffixStr_.length(), suffixStr_.length())};
        auto powerfulNumsCount{0LL};
        auto preLength{strFinish_.length() - suffixStr_.length()};
        for(auto i{0}; i < preLength; ++i) {
            if(limitDigit_ < std::stoi(strFinish_.substr(i, 1))) {
                powerfulNumsCount += static_cast<long long>(std::pow(
                    limitDigit_ + 1, preLength - i));
                return powerfulNumsCount;
            }
            powerfulNumsCount += std::stoll(strFinish_.substr(i, 1)) *
                static_cast<long long>(std::pow(
                    limitDigit_ + 1, preLength -1 - i));
        }
        if(suffixStr >= suffixStr_) {
            ++powerfulNumsCount;
        }
        return powerfulNumsCount;
    }
};
