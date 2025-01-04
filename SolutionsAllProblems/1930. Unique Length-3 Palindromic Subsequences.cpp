// problem : https://leetcode.com/problems/unique-length-3-palindromic-subsequences/description/
// submission : https://leetcode.com/problems/unique-length-3-palindromic-subsequences/submissions/1497802675
// solution post : https://leetcode.com/problems/unique-length-3-palindromic-subsequences/solutions/6231314/c-modern-readable-code-optimal-time-comp-h407

// #include <string>
// #include <vector>
// #include <unordered_map>
// #include <unordered_set>
// #include <utility>

// let 'n' be a parameter 'str' length
// time complexity O(n)
// space complexity O(1)
// runtime 141 ms, beats 85.76 %
class Solution {
public:
    using ItT = std::string::const_iterator;
    int countPalindromicSubsequence(std::string const & str) const {
        auto charsToFirsLast{std::unordered_map<char, std::pair<ItT, ItT>>{}};
        for(auto chr{str.cbegin()}, end{str.cend()}; chr < end; ++chr) {
            if(charsToFirsLast.contains(*chr)) {
                charsToFirsLast.at(*chr).second = chr;
            } else {
                charsToFirsLast.emplace(*chr, std::pair{chr, str.cend()});
            }
        }
        auto palindromesCount{0};
        auto middleChars{std::unordered_set<char>{}};
        for(auto const & [_, firstLast]: charsToFirsLast) {
            if(firstLast.second == str.cend()) {
                continue;
            }
            middleChars.clear();
            middleChars.insert(firstLast.first + 1, firstLast.second);
            palindromesCount += middleChars.size();
        } 
        return palindromesCount;
    }
};
