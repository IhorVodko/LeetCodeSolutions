// problem : https://leetcode.com/problems/smallest-integer-divisible-by-k/description/
// submission : https://leetcode.com/problems/smallest-integer-divisible-by-k/submissions/1840395520
// solution post : https://leetcode.com/problems/smallest-integer-divisible-by-k/solutions/7376073/
//    c-modern-readable-code-beats-100-runtime-i5as

// import std;

class Solution {
public:
// let 'n' be the given number
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto smallestRepunitDivByK(int const div_) const -> int;
};

auto Solution::smallestRepunitDivByK(int const div_) const -> int {
    for(auto rem{0}; auto const sz: std::views::iota(1, div_ + 1))
        if(rem = (rem * 10 + 1) % div_; rem == 0)
            return sz;
    return -1;
}
