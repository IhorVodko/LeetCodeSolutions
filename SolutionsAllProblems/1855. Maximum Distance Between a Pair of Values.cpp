// problem : https://leetcode.com/problems/maximum-distance-between-a-pair-of-values/description
// submission : https://leetcode.com/problems/maximum-distance-between-a-pair-of-values/submissions/1982635476
// solution post : https://leetcode.com/problems/maximum-distance-between-a-pair-of-values/solutions/7994559/
//    c-modern-readable-code-beats-100-runtime-n86c

// Approach : Two Pointers
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the length of the first array of numbers
// 'm' - of the second array of numbers
// complexity :  O(max(n, m))
// complexity : O(1)

// import std;

namespace {

// Compile-time initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    auto maxDistance(
        std::vector<int> const & nums1_,
        std::vector<int> const & nums2_
    ) const noexcept -> int;
};

auto Solution::maxDistance(
    std::vector<int> const & nums1_,
    std::vector<int> const & nums2_
) const noexcept -> int {
    auto const nums1Sz{std::ssize(nums1_)};
    auto const nums2Sz{std::ssize(nums2_)};
    auto maxDist{0};  

    for(auto i1{0}, i2{0}; i1 < nums1Sz && i2 < nums2Sz; ) {
        if(nums1_[i1] > nums2_[i2]) {
            // Move the first pointer forward to find a smaller or equal element
            ++i1;

        // Otherwise, the condition nums1[i1] <= nums2[i2] is met
        } else {
            auto const currDist{i2 - i1};

            maxDist = std::max(maxDist, currDist);
            // Move the second pointer forward to seek a larger distance
            ++i2;
        }
    }

    return static_cast<int>(maxDist);
}
