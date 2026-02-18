// problem : https://leetcode.com/problems/binary-number-with-alternating-bits/description
// submission : https://leetcode.com/problems/binary-number-with-alternating-bits/submissions/1923681034
// solution post : https://leetcode.com/problems/binary-number-with-alternating-bits/solutions/7590249/
//    c-modern-readable-code-beats-100-runtime-z94e

// import std;

// time complexity O(1)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    // Checks whether the binary representation of a number has alternating bits
    [[nodiscard]]
    auto hasAlternatingBits(int const num_) const -> bool;
};

auto Solution::hasAlternatingBits(int const num_) const -> bool {
    // Cast the input to unsigned to ensure well-defined bit operations
    auto const n{static_cast<unsigned>(num_)};
    // Shift the number right by one bit to compare adjacent bits
    auto const shiftedN{n >> 1};
    // XOR the number with its shifted version
    // For alternating bits, this should produce a sequence of all 1s
    auto const nXor{n ^ shiftedN};
    // If the number of set bits equals the bit width,
    // then the XOR result is of the form 111...1
    return std::popcount(nXor) == std::bit_width(nXor);
}
