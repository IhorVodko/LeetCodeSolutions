// problem : https://leetcode.com/problems/power-of-four/description
// submission : https://leetcode.com/problems/power-of-four/submissions/1736119152
// solution post : https://leetcode.com/problems/power-of-four/solutions/7084267/
//    c-modern-readable-code-beats-100-runtime-7gkp

// #include <bit>
// #include <bitset>

class Solution {
public:
// let 'n' be a given number
// time complexity O(1)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    bool isPowerOfFour(int const num_) const;
};

bool Solution::isPowerOfFour(int const num_) const {
    if(num_ <= 0) {
        return false;
    }
    auto const num{static_cast<size_t>(num_)};
    auto zeroCount{std::countr_zero(num)};
    auto const isPowOfFour{zeroCount % 2 == 0 && std::has_single_bit(num)};
    return isPowOfFour;
}
