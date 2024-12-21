// problem : https://leetcode.com/problems/isomorphic-strings/description/
// submission : https://leetcode.com/problems/isomorphic-strings/submissions/1484718315
// solution post : https://leetcode.com/problems/isomorphic-strings/solutions/6171358/c-modern-readable-code-beats-100-runtime-yrt3


// #include <algorithm>
// #include <string>
// #include <vector>
// #include <unordered_map>


class Solution {
public:
    // let 'n' be a parameter 'st1' length
    // time complexity O(n)
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
    bool isIsomorphic(
        std::string str1,
        std::string str2
    ) const {
        if(str1.size() != str2.size()) {
            return false;
        }
        auto charToChar{std::unordered_map<char, char>{}};
        auto chr1{'?'};
        auto chr2{'?'};
        for(auto idx{size_t{0}}; idx < str1.size(); ++idx) {
            chr1 = str1.at(idx);
            chr2 = str2.at(idx);
            if(!charToChar.contains(chr1)) {
                if(std::any_of(charToChar.cbegin(), charToChar.cend(),
                    [&] (auto const charChar) {
                        return charChar.second == chr2;
                    })
                ) {
                    return false;
                }
                charToChar[chr1] = chr2;
            } else if (charToChar.at(chr1) != chr2){
                return false;
            }
        }
        return true;
    }
};
