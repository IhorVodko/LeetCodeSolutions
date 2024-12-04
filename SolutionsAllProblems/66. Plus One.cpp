// problem : https://leetcode.com/problems/plus-one/description/ 
// submission : https://leetcode.com/problems/plus-one/submissions/1470315689
// solution post : https://leetcode.com/problems/plus-one/solutions/6113573/c-modern-readable-code-beats-100-runtime


// #include <vector>


class Solution {
public:
    // let 'n' be an input length
    // time complexity O(n)
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
    std::vector<int> plusOne(
        std::vector<int> & digits
    ) {
        for(auto digit{digits.rbegin()}, end{digits.rend()}; digit < end;
            ++digit
        ) {
            if(*digit == 9) {
                *digit = 0;
            } else {
                ++*digit;
                return digits;
            }
        }
        digits.insert(digits.begin(), 1); 
        return digits;
    }
};
