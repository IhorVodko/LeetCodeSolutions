// problem : https://leetcode.com/problems/valid-perfect-square/description/
// submission : https://leetcode.com/problems/valid-perfect-square/submissions/1632931387
// solution post : https://leetcode.com/problems/valid-perfect-square/solutions/6741120/
//    c-modern-readable-code-beats-100-by-cybe-vmsx

class Solution {
public:
// let 'n' be a number given
// time complexity O(log2(n))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    bool isPerfectSquare(int const num_) const;
};

bool Solution::isPerfectSquare(int const num_) const {
    if(num_ < 2) {
        return true;
    }
    for(auto left{2}, right{num_ / 2}, mid{num_ / 4}; left <= right;
        mid = left + (right - left) / 2
    ) {
        auto const numSquared{static_cast<long long>(mid) * mid};
        if(numSquared == num_) {
            return true;
        } else if(numSquared < num_) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return false;
}
