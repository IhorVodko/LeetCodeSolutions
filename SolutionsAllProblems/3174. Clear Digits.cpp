// problem : https://leetcode.com/problems/clear-digits/description/?envType=daily-question&envId=2025-02-10
// submission : https://leetcode.com/problems/clear-digits/submissions/1538556670
// solution post : https://leetcode.com/problems/clear-digits/solutions/6404793/
//     c-modern-readable-code-beats-100-runtime-gxq2

// #include <string>

// let 'n' be a length of the given string
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    std::string clearDigits(std::string & str) const {
        if(str.size() < 2) {
            return str;
        }  
        for(auto idxPrev{0}, idxCurr{1}; 0 <= idxPrev &&
            idxCurr < str.size();
        ) {
            if(std::isdigit(str.at(idxCurr))) {
                str.erase(idxCurr, 1);
                str.erase(idxPrev, 1);
                if(idxPrev >= 1) {
                    --idxPrev;
                    --idxCurr;
                }
            } else {
                ++idxPrev;
                ++idxCurr;
            }
        } 
        return str;
    }    
};
