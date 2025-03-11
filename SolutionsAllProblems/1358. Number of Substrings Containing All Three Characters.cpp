// problem : https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/description/
// submission : https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/submissions/
//     1570666247 
// solution post : https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/
//     solutions/6525675/c-modern-readable-code-optimal-time-comp-hfv7

// #include <algorithm>
// #include <string>
// #include <vector>

// let 'n' be a length of the given string
// time complexity O(n)
// space complexity O(1)
// runtime 6 ms, beats 73.19 %
class Solution {
public:
    int numberOfSubstrings(std::string const & str_) const {
        auto validSubstrsCount{0}; 
        auto chrsLatestIdx{std::array<int, 3>{{-1, -1, -1}}};
        for(auto i{0}; i < str_.size(); ++i) {
            chrsLatestIdx[str_[i] - 'a'] = i;
            validSubstrsCount += 1 + *std::min_element(chrsLatestIdx.cbegin(),
                chrsLatestIdx.cend());
        }
        return validSubstrsCount;
    }
};
