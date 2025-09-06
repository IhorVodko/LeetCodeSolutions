// problem : https://leetcode.com/problems/minimum-operations-to-make-the-integer-zero/description
// submission : https://leetcode.com/problems/minimum-operations-to-make-the-integer-zero/submissions/1761564822
// solution post : https://leetcode.com/problems/minimum-operations-to-make-the-integer-zero/solutions/7161726/
//    c-modern-readable-code-beats-100-runtime-ys8o

// #include <bit>

class Solution {
public:
// let 'n' be a given first number
// time complexity O(log2(n))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    int makeTheIntegerZero(
        int const num1_,
        int const num2_
    ) const;
};

int Solution::makeTheIntegerZero(
    int const num1_,
    int const num2_
) const {
    auto opsCount{1};
    auto numLeft{static_cast<long long>(num1_ - num2_)};
    while(numLeft >= opsCount) {
        if( opsCount >=
            std::popcount(static_cast<unsigned long long>(numLeft))
        ) {
            return opsCount;
        }
        ++opsCount;
        numLeft -= num2_;
    }
    return -1;
}
