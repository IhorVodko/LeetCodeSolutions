// problem : https://leetcode.com/problems/sqrtx/description/
// submission : https://leetcode.com/problems/sqrtx/submissions/1511271925
// solution post : https://leetcode.com/problems/sqrtx/solutions/6293156/c-modern-readable-code-beats-100-runtime-s3zu

// let 'n' be a parameter 'x' value
// time complexity O(log(n))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int mySqrt(int const x) const {
        if(x < 2) {
            return x;
        }
        auto num{long{0}};
        auto pivot{long{0}};
        auto left{2};
        auto right{x / 2};
        while(left <= right) {
            pivot = left + (right - left) / 2;
            num = pivot * pivot;
            if(num > x) {
                right = pivot - 1;
            } else if(num < x) {
                left = pivot + 1;
            } else {
                return pivot;
            }
        }
        return right;
    }
};
