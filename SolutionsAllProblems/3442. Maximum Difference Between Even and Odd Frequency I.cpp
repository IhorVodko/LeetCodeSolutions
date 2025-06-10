// problem : https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-i/description/
// submission : https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-i/submissions/
//    1659803191
// solution post : https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-i/solutions/
//    6829739/c-modern-readable-code-beats-100-runtime-lol6

// #include <algorithm>
// #include <string>
// #include <vector>

namespace Util {
    auto constexpr kChrSetSz{26};
    auto constexpr kChrSetMin{'a'};
}
class Solution {
public:
// let 'n' be a length of the given string
// 'c' - size of the given charset
// time complexity O(n + c)
// space complexity O(c)
// runtime 0 ms, beats 100.00 %
    int maxDifference(std::string const & str_) const;
};

int Solution::maxDifference(std::string const & str_) const {
    using namespace Util;
    using IntT = std::numeric_limits<int>;
    auto chrCounts{std::vector<int>(kChrSetSz, 0)};
    for(auto const chr: str_) {
        ++chrCounts.at(chr - kChrSetMin);
    }
    auto freqOddMax{IntT::min()};
    auto freqEvenMin{IntT::max()}; 
    for(auto const count: chrCounts) {
        if(count == 0) {
            continue;
        } else if(count % 2 == 1) {
            freqOddMax = std::max(freqOddMax, count);
        } else {
            freqEvenMin = std::min(freqEvenMin, count);
        }
    }
    auto const diff{freqOddMax - freqEvenMin};
    return diff;
};
