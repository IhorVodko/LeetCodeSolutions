// problem : https://leetcode.com/problems/check-if-number-is-a-sum-of-powers-of-three/description/
// submission : https://leetcode.com/problems/check-if-number-is-a-sum-of-powers-of-three/submissions/1562154221
// solution post : https://leetcode.com/problems/check-if-number-is-a-sum-of-powers-of-three/solutions/6496448/
//     c-modern-readable-code-beats-100-runtime-s4qj

// let 'n' be a given number
// time complexity O(log3(n))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    bool checkPowersOfThree(int num) const {
        while(num > 0) {
            if(num % 3 == 2) {
                return false;
            }
            num /= 3;
        }
        return true;
    }
};
