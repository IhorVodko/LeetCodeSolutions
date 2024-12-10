// problem :  https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/
// submission : https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/submissions/1475516974
// solution post : https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/solutions/6133886/c-modern-readable-code-beats-100-runtime


// #include <string>
// #include <iterator>


class Solution {
public:
    // let 'n' be a 'needle' string length
    // 'm' - a 'haystack' string length
    // time complexity O(n * m)
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
    int strStr(
        std::string const haystack,
        std::string const needle
    ) const {
        for(auto chr{haystack.cbegin()}, end{haystack.cend()}; chr < end;
            ++chr
        ) {
            if(isPresent(needle, chr, end)) {
                return std::distance(haystack.cbegin(), chr);
            }
        }
        return -1;
    }
private: 
    bool isPresent(
        auto const & needle,
        auto chr,
        auto end
    ) const {
        for(auto chr2{needle.cbegin()}, end2{needle.cend()};
            chr < end && chr2 < end2; ++chr, ++chr2
        ) {
            if(*chr != *chr2) {
                break;
            }
            if(chr2 == end2 - 1) {
                return true;
            }
        }
        return false;;
    }
};
