// problem : https://leetcode.com/problems/powx-n/description/
// submission : https://leetcode.com/problems/powx-n/submissions/1632136020
// solution post : https://leetcode.com/problems/powx-n/solutions/6738442/
//    c-modern-readable-code-beats-100-by-cybe-22af

class Solution {
public:
// let 'n' be a value of the exponent given
// time complexity O(log2(n))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    double myPow(
        double base_,
        int const exp_
    ) const;
};

double Solution::myPow(
    double base_,
    int const exp_
) const {
    if(exp_ == 0) {
        return 1;
    }
    auto exp{static_cast<long long>(exp_)};
    if(exp < 0) {
        exp *= -1;
        base_ = 1 / base_;
    }
    auto product{1.0};
    while(exp > 0) {
        if(exp % 2 == 1) {
            product *= base_;
            --exp;
        }
        base_ *= base_;
        exp /= 2;
    }
    return product;
}
