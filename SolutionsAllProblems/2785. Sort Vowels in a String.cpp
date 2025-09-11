// problem : https://leetcode.com/problems/sort-vowels-in-a-string/description
// submission : https://leetcode.com/problems/sort-vowels-in-a-string/submissions/1767407444
// solution post : https://leetcode.com/problems/sort-vowels-in-a-string/solutions/7179683/
//    c-modern-readable-code-optimal-time-comp-isgd

// #include <map>
// #include <unordered_set>
// #include <string>

class Solution {
public:
// let 'n' be a length of the given string
// time complexity O(n)
// space complexity O(1)
// runtime 18 ms, beats 39.99 %
    [[nodiscard]]
    std::string sortVowels(std::string str_) const; 
private:
    static const std::unordered_set<char> mkVowels;
};

std::string Solution::sortVowels(std::string str_) const  {
    auto const strSz{str_.size()};
    auto chrToCnt{std::map<char, int>{}};
    for(auto const chr: str_) {
        if(mkVowels.contains(chr)) {
            ++chrToCnt[chr];
        }
    }
    auto chrToCntIt{chrToCnt.begin()};
    for(auto & chr: str_) {
        if(mkVowels.contains(chr)) {
            chr = chrToCntIt->first;
            if(--chrToCntIt->second == 0) {
                ++chrToCntIt;
            }
        }
    }
    return str_;
}

const std::unordered_set<char> Solution::mkVowels{
    'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u'
};
