// problem : https://leetcode.com/problems/count-operations-to-obtain-zero/description
// submission : https://leetcode.com/problems/count-operations-to-obtain-zero/submissions/1825431809
// solution post : https://leetcode.com/problems/minimum-one-bit-operations-to-make-integers-zero/
//    solutions/7335362/c-modern-readable-code-beats-100-runtime-5wpz

// import std;

class Solution {
public:
// let 'n1' be the first given number
// 'n2' - the second given number
// time complexity O(log(max(n1, n2))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto countOperations(
        int num1_,
        int num2_
    ) const -> int;
};

auto Solution::countOperations(
    int num1_,
    int num2_
) const -> int {
    auto ops{0};
    while(num1_ > 0 && num2_ > 0) {
        ops += num1_ / num2_;
        num1_ %= num2_;
        std::swap(num1_, num2_);
    }
    return ops;
}
