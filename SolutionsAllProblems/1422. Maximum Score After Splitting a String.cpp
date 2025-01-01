// problem : https://leetcode.com/problems/maximum-score-after-splitting-a-string/description/
// submission : https://leetcode.com/problems/maximum-score-after-splitting-a-string/submissions/1494489818
// solution post : https://leetcode.com/problems/maximum-score-after-splitting-a-string/solutions/6215183/c-modern-readable-code-beats-100-runtime-9xzv

// #include <algorithm>
// #include <string>

// let 'n' be a parameter 'str' length
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    auto maxScore(std::string const & str) const {
        auto onesCount{static_cast<int>(std::count_if(str.cbegin(), str.cend(),
            [] (auto const chr) { return chr == '1'; }))};
        auto zeroesCount{0};
        auto maxScore{onesCount - 1};
        for(auto chr{str.cbegin()}, end{str.cend()}; chr < end; ++chr) {
            if(*chr == '0' && chr < end - 1) {
                maxScore = std::max(maxScore, ++zeroesCount + onesCount);
            } else if(*chr == '1') {
                --onesCount;
            } 
        }
        return maxScore;
    }
};
