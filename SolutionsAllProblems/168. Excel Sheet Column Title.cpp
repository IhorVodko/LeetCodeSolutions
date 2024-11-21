// problem :  https://leetcode.com/problems/excel-sheet-column-title/description/
// submission : https://leetcode.com/problems/excel-sheet-column-title/submissions/1459522424
// solution post: https://leetcode.com/problems/excel-sheet-column-title/solutions/6070084/c-modern-readable-code-beat-100-runtime

// #include <cmath>
// #include <string>
// #include <vector>

class Solution{
public:
    std::string convertToTitle(int colNum) const {
        // let 'n' be an input number
        // time complexity O(log(n))
        // space complexity O(1)
        // runtime 0 ms, beats 100.00 %
        // memory 7.12 mb, beats 96.88 %
        auto title{std::string{}};
        auto constexpr asciiOffset{int(65)};
        auto constexpr alphabetSize{int(26)};
        auto quotRem{div_t{0, 0}};
        while(colNum-- > 0){
            quotRem = std::div(colNum, alphabetSize);
            title.push_back(char(asciiOffset + quotRem.rem));
            colNum = quotRem.quot;
        }
        std::reverse(std::begin(title), std::end(title));
        return title;
    }
};
