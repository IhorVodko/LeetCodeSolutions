// problem : https://leetcode.com/problems/n-th-tribonacci-number/description 
// submission : https://leetcode.com/problems/n-th-tribonacci-number/submissions/1775881340
// solution post : https://leetcode.com/problems/n-th-tribonacci-number/solutions/7205012/
//    c-modern-readable-code-beats-100-runtime-l1lv

// import std;

class Solution {
public:
// let 'n' be a given number
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto tribonacci(int const num_) const noexcept -> int;
};

auto Solution::tribonacci(int num_) const noexcept -> int {
    if(num_ == 0) {
        return 0;
    }
    auto prevPrevNum{0};
    auto prevNum{1};
    auto currNum{1};
    num_ -= 3;
    while(num_-- >= 0) {
        auto const nextNum{prevPrevNum + prevNum + currNum};
        prevPrevNum = prevNum;
        prevNum = currNum;
        currNum = nextNum;
    }
    return currNum;
}
