// problem : https://leetcode.com/problems/count-total-number-of-colored-cells/description/
// submission : https://leetcode.com/problems/count-total-number-of-colored-cells/submissions/1564017051
// solution post : https://leetcode.com/problems/count-total-number-of-colored-cells/solutions/6506384/
//     c-modern-readable-code-beats-100-runtime-lxuo

// let 'n' be a given number
// time complexity O(1)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    long long coloredCells(int const minutesCount_) const {
        return 1 + 2LL * minutesCount_ * (minutesCount_ - 1);
    }
};
