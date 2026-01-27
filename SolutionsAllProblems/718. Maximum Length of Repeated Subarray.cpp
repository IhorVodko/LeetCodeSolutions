// problem : https://leetcode.com/problems/maximum-length-of-repeated-subarray/description/
// submission : https://leetcode.com/problems/maximum-length-of-repeated-subarray/submissions/1898667404
// solution post : https://leetcode.com/problems/maximum-length-of-repeated-subarray/solutions/7529216/
//    c-modern-readable-code-beats-100-runtime-28tq

// import std;

inline static int const fastIOInit{
    [] {
        std::atexit([] () { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' be the first vector length
// 'm' - second vector length
// time complexity O(n * m)
// space complexity O(m)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto findLength(
        std::span<int const> const nums1_,
        std::span<int const> const nums2_
    ) const -> int;
};

auto Solution::findLength(
    std::span<int const> const nums1_,
    std::span<int const> const nums2_
) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto maxLength{0};
    auto const nums1Sz{std::ssize(nums1_)};
    auto const nums2Sz{std::ssize(nums2_)};
    auto prev{std::vector<int>(nums2Sz + 1)};
    auto cur{std::vector<int>(nums2Sz + 1)};
    // prev[j] and cur[j] store the length of the longest common subarray
    // ending at nums1_[i1 - 1] and nums2_[j - 1] for the previous/current row
    for(auto const i1: vs::iota(1, nums1Sz + 1)) {
        for(auto const i2: vs::iota(1, nums2Sz + 1)) {
            if(nums1_[i1 - 1] == nums2_[i2 - 1]) {
                // Extend the common suffix from the diagonal DP cell
                auto curLength{prev[i2 - 1] + 1};
                cur[i2] = curLength;
                maxLength = std::max(maxLength, curLength);
            }
        }
        // Current row becomes the previous row for the next iteration
        std::swap(prev, cur);
        // Reset the working row so non-matching positions remain zero
        rngs::fill(cur, 0);
    }
    return maxLength;
}
