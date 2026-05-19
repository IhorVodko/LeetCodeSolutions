// problem : https://leetcode.com/problems/minimum-common-value/description
// submission : https://leetcode.com/problems/minimum-common-value/submissions/2007414673
// solution post : https://leetcode.com/problems/minimum-common-value/solutions/8278160/c-modern-readable-code-beats-100-runtime-z9uc

// Approach : Two-Pointer with Duplicate Skipping
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the length of the first array of nubmers
// 'm' - lenth of the second array of numbers
// complexity :  O(n + m)
// complexity : O(1)

// import std;

class Solution final {
public:
    [[nodiscard]]
    auto getCommon(
        std::vector<int> const & nums1_,
        std::vector<int> const & nums2_
    ) const -> int;
};

auto Solution::getCommon(
    std::vector<int> const & nums1_,
    std::vector<int> const & nums2_
) const -> int {
    namespace vs = std::views;

    auto const end1{nums1_.cend()};
    auto const end2{nums2_.cend()};
    auto num1{nums1_.cbegin()};
    auto num2{nums2_.cbegin()};

    while(num1 != end1 && num2 != end2) {
        // First match is guaranteed to be the minimum common value.
        if(*num1 == *num2) {
            return *num1;
        } else if(*num1 < *num2) {
            // Skips duplicates in the lagging first array.
            auto const prevNum{*num1};
            while(num1 != end1 && prevNum == *num1) {
                ++num1;
            }
        } else {
            // Skips duplicates in the lagging second array.
            auto const prevNum{*num2};
            while(num2 != end2 && prevNum == *num2) {
                ++num2;
            }
        }
    }

    // No common elements exist.
    return -1;
}

namespace {

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace
