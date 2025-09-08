// problem : https://leetcode.com/problems/convert-integer-to-the-sum-of-two-no-zero-integers/description
// submission : https://leetcode.com/problems/convert-integer-to-the-sum-of-two-no-zero-integers/submissions/1763882007
// solution post : https://leetcode.com/problems/convert-integer-to-the-sum-of-two-no-zero-integers/solutions/7169457/
//    c-modern-readable-code-beats-100-runtime-p77f

// #include <vector>

class Solution {
public:
// let 'n' be a given sum of two numbers
// time complexity O(log10(n))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    std::vector<int> getNoZeroIntegers(int sum_) const;
};

std::vector<int> Solution::getNoZeroIntegers(int sum_) const {
    auto num1{0};
    auto num2{0};
    auto digitIdx{1};
    while(sum_ > 0) {
        auto digit{sum_ % 10};
        sum_ /= 10;
        if(digit <= 1 && sum_ > 0) {
            digit += 10;
            sum_ -= 1;
        }
        auto reminder{digit % 2};
        digit /= 2;
        num1 += digit * digitIdx;
        num2 += (digit + reminder) * digitIdx; 
        digitIdx *= 10;
    }
    return {num1, num2};
}
