// problem : https://leetcode.com/problems/remove-all-occurrences-of-a-substring/description/
// submission : https://leetcode.com/problems/remove-all-occurrences-of-a-substring/submissions/1539495054
// solution post : https://leetcode.com/problems/remove-all-occurrences-of-a-substring/solutions/6408889/
//     c-modern-readable-code-beats-100-runtime-41hj

// #include <string>

// let 'n' be a parameter 'str' length
// let 'm' - 'part' length
// time complexity O(n + m)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    std::string removeOccurrences(
        std::string & str,
        std::string const & part
    ) const {
        auto pos{str.find(part)};
        while(pos != std::string::npos) {
            str.erase(pos, part.size());         
            pos = str.find(part);
        }
        return str;
    }
};
