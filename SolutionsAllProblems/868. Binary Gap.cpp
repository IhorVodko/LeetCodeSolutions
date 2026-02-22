// problem : https://leetcode.com/problems/binary-gap/description
// submission : https://leetcode.com/problems/binary-gap/submissions/1927703504
// solution post : https://leetcode.com/problems/binary-gap/solutions/7600653/
//    c-modern-readable-code-beats-100-runtime-d4du

// import std;

// let 'n' be the given number
// time complexity O(log(n))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    [[nodiscard]]
    auto binaryGap(int const num_) const -> int;

private:
    static auto constexpr kMaxNum{1'000'000'000u};
    static auto constexpr kMaxSz{std::bit_width(kMaxNum)};
};

auto Solution::binaryGap(int const num_) const -> int {
    namespace vs = std::views;

    // Represent the input number as a fixed-size bitset
    auto bits{std::bitset<kMaxSz>(static_cast<unsigned>(num_))};
    auto maxDist{0};
    // Iterate over bit positions to find distances between consecutive 1s
    for(auto prev{-1}; auto const cur: vs::iota(0, kMaxSz)) {
        if(bits.test(cur)) {
            if(prev == -1) {
                prev = cur;
            } else {
                // Compute distance between current and previous set bit
                auto const curDist{cur - prev};
                maxDist = std::max(maxDist, curDist);
                prev = cur;
            }
        }
    }
    return maxDist;
}
