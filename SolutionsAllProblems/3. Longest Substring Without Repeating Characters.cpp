// problem : https://leetcode.com/problems/longest-substring-without-repeating-characters/description/
// submission : https://leetcode.com/problems/longest-substring-without-repeating-characters/submissions/1503316374
// solution post : https://leetcode.com/problems/longest-substring-without-repeating-characters/solutions/6256958/c-modern-readable-code-optimal-time-comp-jh52

// #include <string>
// #include <unordered_set>

// let 'n' be a parameter 'str' length
// time complexity O(n)
// space complexity O(1)
// runtime 3 ms, beats 83.96 %
class Solution {
public:
    int lengthOfLongestSubstring(std::string const & str) const {
        auto maxLength{std::numeric_limits<int>::min()};
        auto charsToIdxs{std::unordered_map<char, size_t>{}};
        auto subStrBegin{0};
        for(auto idx{0}; idx < str.size(); ++idx) {
            if(!charsToIdxs.contains(str.at(idx)) ||
                charsToIdxs.at(str.at(idx)) < subStrBegin
            ) {
                charsToIdxs[str.at(idx)] = idx;
                continue;
            }
            maxLength = std::max(maxLength, idx - subStrBegin);
            subStrBegin = charsToIdxs.at(str.at(idx)) + 1;
            charsToIdxs.at(str.at(idx)) = idx;
        }
        return std::max(maxLength,
            static_cast<int>(str.size() - subStrBegin));
    }
};
