// problem : https://leetcode.com/problems/gcd-of-odd-and-even-sums/description
// submission : https://leetcode.com/problems/gcd-of-odd-and-even-sums/submissions/2068626682
// solution post : https://leetcode.com/problems/gcd-of-odd-and-even-sums/solutions/8399085/modern-readable-code-optimal-time-comple-a7i0

// Approach : Constant-Time Mathematical Simplification
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// Time :  O(1)
// Space : O(1)

// import std;

class Solution final {
public:
    [[nodiscard]]
    static auto gcdOfOddEvenSums(int const num_) -> int;
};

auto Solution::gcdOfOddEvenSums(int const num_) -> int {
    // Math reduction: GCD of sum of odd numbers, n^2, and sum of even numbers, n(n+1),
    // reduces to n as n and n+1 are coprime.
   return num_;
}
