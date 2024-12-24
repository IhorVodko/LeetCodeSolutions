// problem : https://leetcode.com/problems/first-unique-character-in-a-string/description/
// submission : https://leetcode.com/problems/first-unique-character-in-a-string/submissions/1487380906
// solution post : https://leetcode.com/problems/first-unique-character-in-a-string/solutions/6182229/c-modern-readable-code-by-cyberartist-wdd7


// #include <string>
// #incldue <unordered_map>


class Solution {
public:
    // let 'n' be a parameter 'str' length
    // time complexity O(n)
    // space complexity O(1)
    // runtime 9 ms, beats 69.28 %
    int firstUniqChar(std::string const str) const {
        auto charsToFreqs{std::unordered_map<char, size_t>{}};
        for(auto chr{str.cbegin()}, end{str.cend()}; chr < end; ++chr) {
            ++charsToFreqs[*chr]; 
        } 
        for(auto chr{str.cbegin()}, end{str.cend()}; chr < end; ++chr) {
            if(charsToFreqs.at(*chr) == 1) {
                return chr - str.cbegin();
            }
        }
        return -1;
    }
};
