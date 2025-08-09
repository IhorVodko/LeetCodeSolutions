// problem : https://leetcode.com/problems/power-of-two/?envType=daily-question&envId=2025-08-09
// submission : https://leetcode.com/problems/power-of-two/submissions/1729148276
// solution post : https://leetcode.com/problems/power-of-two/solutions/7061655/
//    c-modern-readable-code-beats-100-runtime-in49

// #include <bit>

class Solution {
public:
// let 'n' be a given number
// time complexity O(1)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    bool isPowerOfTwo(int const num_) const;
};

bool Solution::isPowerOfTwo(int const num_) const {
    if(num_ <= 0) {
        return false;
    }
    auto isPowOf2{std::has_single_bit(static_cast<unsigned>(num_))};
    return isPowOf2;
}
