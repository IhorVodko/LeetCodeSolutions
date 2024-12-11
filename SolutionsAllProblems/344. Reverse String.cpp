// problem : https://leetcode.com/problems/reverse-string/description/
// submission : https://leetcode.com/problems/reverse-string/submissions/1476454347
// solution post : https://leetcode.com/problems/reverse-string/solutions/6137275/c-modern-readable-code-beats-100-runtime


// #include <string>


class Solution {
public:
    // let 'n' be a parametr 'str' length
    // time complexity O(n)
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
    void reverseString(
        std::vector<char> & str
    ) const {
        auto chrTemp{'?'};
        for(auto chr1{str.begin()}, chr2{str.end() - 1}; chr1 < chr2;
            ++chr1, --chr2
        ) {
            chrTemp = *chr1;
            *chr1 = *chr2;
            *chr2 = chrTemp;
        } 
    }
};
