// problem : https://leetcode.com/problems/divisible-and-non-divisible-sums-difference/description
// submission : https://leetcode.com/problems/divisible-and-non-divisible-sums-difference/submissions/1646180210
// solution post : https://leetcode.com/problems/divisible-and-non-divisible-sums-difference/solutions/6787415/
//    c-modern-readable-code-beats-100-by-cybe-52cn

class Solution {
public:
// let 'n' be a value of the 'numUpperLimit_' parameter
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    int differenceOfSums(
        int const numUpperLimit_,
        int const divisor_
    ) const; 
};

int Solution::differenceOfSums(
    int const numUpperLimit_,
    int const divisor_
) const {
    auto const k{numUpperLimit_ / divisor_};
    auto const diff{numUpperLimit_ * (numUpperLimit_ + 1) / 2 -
        k * (k + 1) * divisor_};
    return diff;
}
