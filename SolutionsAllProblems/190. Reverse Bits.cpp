// problem : https://leetcode.com/problems/reverse-bits/description
// submission : https://leetcode.com/problems/reverse-bits/submissions/1921237297
// solution post : https://leetcode.com/problems/reverse-bits/solutions/7584333/
//    c-modern-readable-code-beats-100-runtime-0qt9

// import std;

class Solution {
public:
    [[nodiscard]]
    auto reverseBits(int const num_) const -> int;
};

// time complexity O(1)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
auto Solution::reverseBits(int const num_) const -> int {
    namespace vs = std::views;

    static auto constexpr kBitsCnt{32};

    // Convert the integer to a 32-bit bitset for easy bit access
    auto bits{std::bitset<kBitsCnt>(static_cast<unsigned>(num_))};
    for(auto const i: vs::iota(0, kBitsCnt / 2)) {
        // Swap the i-th bit with its mirrored position
        auto const temp{static_cast<bool>(bits[i])};
        bits[i] = bits[kBitsCnt - i - 1];
        bits[kBitsCnt - i - 1] = temp;
    }
    // Convert the reversed bitset back to an integer
    auto const revNum{bits.to_ulong()};
    return static_cast<int>(revNum);
}
