// problem : https://leetcode.com/problems/make-string-a-subsequence-using-cyclic-increments/description/
// submission : https://leetcode.com/problems/make-string-a-subsequence-using-cyclic-increments/submissions/1470277574
// solution post : https://leetcode.com/problems/make-string-a-subsequence-using-cyclic-increments/solutions/6113403/c-modern-readable-code-beats-100-runtime

// #include <string>

class Solution {
public:
    // let 'n' be an str1 length
    // time complexity O(n)
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
    bool canMakeSubsequence(
        std::string const str1,
        std::string const str2
    ) const {
        static constexpr auto diff{1}; 
        static constexpr auto alphabetCycle{25}; 
        if(str1.size() < str2.size()) {
            return false;
        }
        auto matchesCount{size_t{0}};
        for(auto indx1{size_t{0}}, indx2{size_t{0}}; 
            indx1 < str1.size() && indx2 < str2.size(); ++indx1
        ) {
            if(str1.at(indx1) == str2.at(indx2) ||
                str1.at(indx1) + diff == str2.at(indx2) ||
                str1.at(indx1) == str2.at(indx2) + alphabetCycle
            ) {
                ++indx2;
                ++matchesCount;
            }
        }
        return matchesCount == str2.size();
    }
};
