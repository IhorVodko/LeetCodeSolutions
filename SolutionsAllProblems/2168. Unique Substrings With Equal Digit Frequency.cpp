// problem : https://leetcode.com/problems/unique-substrings-with-equal-digit-frequency/description/
// submission : https://leetcode.com/problems/unique-substrings-with-equal-digit-frequency/submissions/1509522227
// solution post : https://leetcode.com/problems/unique-substrings-with-equal-digit-frequency/solutions/6284830/c-modern-readable-code-optimal-time-comp-1sga

// #include <algorithm>
// #include <string>
// #include <vector>
// #include <unordered_set>

namespace Utility {
    auto constexpr prime{31};
    auto constexpr mod{static_cast<size_t>(10e9)};
    auto constexpr radix{10};
    auto constexpr firstDigit{'0'};
    auto constexpr minSizeT{std::numeric_limits<size_t>::min()};
}

// let 'n' be a parameter 'str' length
// time complexity O(n^2)
// space complexity O(n^2)
// runtime 175 ms, beats 67.3 %

class Solution {
public:
    int equalDigitFrequency(std::string const & str) const {
        using namespace Utility;
        auto uniqueValidSubStrHashes{std::unordered_set<size_t>{}};
        auto digitCounts{std::vector<size_t>(radix, 0)};
        auto uniqueDigitsCount{size_t{0}};
        auto maxDigitCount{minSizeT};
        auto digit{minSizeT};
        auto subStrRollingHash{minSizeT};
        for(auto first{str.begin()}, end{str.end()}; first < end; ++first) {
            std::fill(digitCounts.begin(), digitCounts.end(), 0);
            uniqueDigitsCount = 0;
            maxDigitCount = minSizeT;
            subStrRollingHash = minSizeT;
            for(auto last{first}; last < end; ++last) {
                digit = *last - firstDigit;
                uniqueDigitsCount += digitCounts.at(digit) == 0 ? 1 : 0;
                ++digitCounts.at(digit);
                maxDigitCount = std::max(maxDigitCount, digitCounts.at(digit));
                subStrRollingHash =
                    (prime * subStrRollingHash + digit + 1) % mod;
                if(maxDigitCount * uniqueDigitsCount == last - first + 1) {
                    uniqueValidSubStrHashes.emplace(subStrRollingHash);
                } 
            }
        }
        return uniqueValidSubStrHashes.size();
    }
};
