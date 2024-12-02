// problem : https://leetcode.com/problems/palindrome-number/
// submission : https://leetcode.com/problems/palindrome-number/submissions/1453678170
// solution post : https://leetcode.com/problems/palindrome-number/solutions/6048544/c-modern-readable-code-beats-100-runtime

class Solution {
public:
    // let 'n' be an input number
    // time complexity O(log10(n))
    // space complexity O(1)
    // runtime 0 ms, beats 100 %
    bool isPalindrome(int num) {
        if(num < 0){
            return false;
        }
        constexpr int base{10};
        long int reverseNum{0};
        int numCopy{num};
        do{
            reverseNum = reverseNum * base + (numCopy % base);
            numCopy /= base; 
        } while (numCopy != 0);
        return num == reverseNum;
    }
};
