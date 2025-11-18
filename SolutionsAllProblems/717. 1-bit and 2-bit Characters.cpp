// problem : https://leetcode.com/problems/1-bit-and-2-bit-characters/description
// submission : https://leetcode.com/problems/1-bit-and-2-bit-characters/submissions/1833361361
// solution post : https://leetcode.com/problems/1-bit-and-2-bit-characters/solutions/7357895/
//    c-modern-readable-code-beats-100-runtime-ec6y

// import std;

class Solution {
public:
// let 'n' be the number of given bits
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto isOneBitCharacter(
        std::span<int> const bits_
    ) const -> bool;
};

auto Solution::isOneBitCharacter(
    std::span<int> const bits_
) const -> bool {
    auto const sz{std::ssize(bits_)};
    auto idx{0};
    while(idx < sz - 1) {
        idx += bits_[idx] + 1;
    }
    auto const isLastBitSet{idx == sz - 1};
    return isLastBitSet;
}
