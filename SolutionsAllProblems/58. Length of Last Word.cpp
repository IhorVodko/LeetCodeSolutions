// problem : https://leetcode.com/problems/length-of-last-word/description/
// submission : https://leetcode.com/problems/length-of-last-word/submissions/1510603021
// solution post : https://leetcode.com/problems/length-of-last-word/solutions/6290148/c-modern-readable-code-beats-100-runtime-0ilp

// #include <cctype>
// #include <string>

// let 'n' be a parameter 'str' length
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int lengthOfLastWord(std::string const & str) const {
        auto chr1{str.rbegin()};
        while(std::isspace(*chr1)) {
            ++chr1;
        }
        auto chr2{chr1};
        auto end{str.rend()};
        while(chr2 < end && std::isalpha(*chr2)) {
            ++chr2;
        }
        return chr2 == chr1 ? 1 : chr2 - chr1; 
    }
};
