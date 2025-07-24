// problem : https://leetcode.com/problems/maximum-score-from-removing-substrings/description
// submission : https://leetcode.com/problems/maximum-score-from-removing-substrings/submissions/1709953380
// solution post : https://leetcode.com/problems/maximum-score-from-removing-substrings/solutions/6999795
//    /c-modern-readable-code-beats-99-runtime-5wuh9

// #include <algorithm>
// #include <string>

namespace Util {
    inline auto constexpr kChrA{'a'};
    inline auto constexpr kChrB{'b'};
}

class Solution {
public:
// let 'n' be a length of the given string
// time complexity O(n)
// space complexity O(1)
// runtime 4 ms, beats 99.36 %
    [[nodiscard]]
    int maximumGain(
        std::string & str_,
        int const xPoints_,
        int const yPoints_
    ) const;
};

int Solution::maximumGain(
    std::string & str_,
    int xPoints_,
    int yPoints_
) const {
    namespace ranges = std::ranges;
    using namespace Util;
    if(xPoints_ < yPoints_) {
        std::swap(xPoints_, yPoints_);
        ranges::reverse(str_);
    }
    auto chrACount{0};
    auto chrBCount{0};
    auto score{0};
    for(auto const chr: str_) {
        if(chr == kChrA) {
            ++chrACount;
        } else if(chr == kChrB) {
            if(chrACount > 0) {
                --chrACount;
                score += xPoints_;
            } else {
                ++chrBCount;
            }
        } else {
            score += std::min(chrACount, chrBCount) * yPoints_;
            chrACount = chrBCount = 0;
        }
    } 
    score += std::min(chrACount, chrBCount) * yPoints_;
    return score;
}
