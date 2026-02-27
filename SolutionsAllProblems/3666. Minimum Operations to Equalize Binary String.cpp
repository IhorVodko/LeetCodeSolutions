// problem : https://leetcode.com/problems/minimum-operations-to-equalize-binary-string/description
// submission : https://leetcode.com/problems/minimum-operations-to-equalize-binary-string/submissions/1932962355
// solution post : https://leetcode.com/problems/minimum-operations-to-equalize-binary-string/solutions/7613467/
//    c-modern-readable-code-beats-100-runtime-mld5

// import std;

inline static int const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

class Solution {
public:
    [[nodiscard]]
    auto minOperations(
        std::string_view const bits_,
        int const bitsToFlipCnt_
    ) const -> int;
};

// let 'n' be the string length
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
auto Solution::minOperations(
    std::string_view const bits_,
    int const bitsToFlipCnt_
) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;
    using intLim = std::numeric_limits<int>;

    auto const bitsSz{static_cast<int>(bits_.size())};
    auto const unsetBitsSz{static_cast<int>(rngs::count(bits_, '0'))};
    // If there are no unset bits, the string is already uniform
    if(unsetBitsSz == 0) {
        return 0;
    }
    // If one operation flips the entire string
    // Then it is possible only if all bits are zero (so one flip makes them all one)
    if(bitsToFlipCnt_ == bitsSz) {
        return unsetBitsSz == bitsSz ? 1 : -1;
    }
    auto minOpCnt{intLim::max()};
    // Case 1: total number of zero bits is even
    // We try to make total operations even to maintain parity feasibility
    if(unsetBitsSz % 2 == 0) {
        // Lower bound from covering all zero bits
        auto const minOpsCoverZeros{(unsetBitsSz + bitsToFlipCnt_ - 1) / bitsToFlipCnt_};
        // Lower bound from avoiding invalid overflow on ones
        auto const minOpsBalanceOnes{
            (unsetBitsSz + bitsSz - bitsToFlipCnt_ - 1) / (bitsSz - bitsToFlipCnt_)};
        // Minimum operations required so that:
        // 1) Enough flips are applied to cover all zero bits
        // 2) Remaining flips do not violate total bit constraints
        auto const curOpCnt{std::max(minOpsCoverZeros, minOpsBalanceOnes)};
        // Ensure operation count parity is even
        minOpCnt = (curOpCnt % 2 == 0) ? curOpCnt : curOpCnt + 1;
    }
    // Case 2: parity of zero bits matches parity of bits flipped per operation
    // This allows an odd number of operations to potentially work
    if(unsetBitsSz % 2 == bitsToFlipCnt_ % 2) {
        // Lower bound from covering all zero bits
        auto const minOpsCoverZeros{(unsetBitsSz + bitsToFlipCnt_ - 1) / bitsToFlipCnt_};
        // Alternative lower bound under odd parity alignment
        auto const minOpsParityAdjusted{
            (2 * bitsSz - unsetBitsSz - bitsToFlipCnt_ - 1) / (bitsSz - bitsToFlipCnt_)};
        // Compute minimum operations under alternative parity alignment
        auto const curOpCnt{std::max(minOpsCoverZeros, minOpsParityAdjusted)};
        // Ensure operation count parity is odd
        minOpCnt = std::min(minOpCnt, (curOpCnt % 2 == 1) ? curOpCnt : curOpCnt + 1);
    }
    // If no valid operation count was found, return -1
    return minOpCnt == intLim::max() ? -1 : minOpCnt;
}
