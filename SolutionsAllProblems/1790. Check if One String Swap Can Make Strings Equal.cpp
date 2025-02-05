// problem : https://leetcode.com/problems/check-if-one-string-swap-can-make-strings-equal/description/
// submission : https://leetcode.com/problems/check-if-one-string-swap-can-make-strings-equal/submissions/1532731951
// solution post : https://leetcode.com/problems/check-if-one-string-swap-can-make-strings-equal/solutions/6381618/c-modern-readable-code-beats-100-runtime-ytzn

// #include <string>

// let 'n' be a length of the given strings
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    bool areAlmostEqual(
        std::string const & s1,
        std::string const & s2
    ) const {
        auto idxDiff1{size_t{0}};    
        auto idxDiff2{size_t{0}};    
        auto diffCount{size_t{0}};
        for(auto idx{size_t{0}}; idx < s1.size(); ++idx) {
            if(s1.at(idx) == s2.at(idx)) {
                continue;
            }
            ++diffCount;
            if(diffCount == 1) {
                idxDiff1 = idx;
            } else if(diffCount == 2) {
                idxDiff2 = idx;
            } else {
                return false;
            }
        }
        return s1.at(idxDiff1) == s2.at(idxDiff2) &&
            s1.at(idxDiff2) == s2.at(idxDiff1);
    }
};
