// problem : https://leetcode.com/problems/prime-number-of-set-bits-in-binary-representation/description
// submission : https://leetcode.com/problems/prime-number-of-set-bits-in-binary-representation/submissions/1927568937
// solution post : https://leetcode.com/problems/prime-number-of-set-bits-in-binary-representation/solutions/7600266/
//    c-modern-readable-code-beats-100-runtime-nqov

// import std;

class Solution {
public:
    [[nodiscard]]
    auto countPrimeSetBits(
        int const minNum_,
        int const maxNum_
    ) const -> int;

private:
    static auto constexpr kMaxNum{1'000'000u};
    // Bitmask where index represents popcount value and bit is set if that value is
    // prime (0..20)
    static auto constexpr kIsPrime{std::bitset<std::bit_width(kMaxNum) + 1>{
        "010100010100010101100"}};
};

// let 'n' be the minimum number
// 'm' - maximum number
// time complexity O(m - n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
auto Solution::countPrimeSetBits(
    int const minNum_,
    int const maxNum_
) const -> int {
    namespace vs = std::views;

    auto primeCnt{0};
    for(auto const num: vs::iota(minNum_, maxNum_ + 1)) {
        // Count number of set bits in current number
        auto const setBitCnt{std::popcount(static_cast<unsigned>(num))};
        if(kIsPrime.test(setBitCnt)) {
            ++primeCnt;
        }
    }
    return primeCnt;
}
