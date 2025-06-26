// problem : https://leetcode.com/problems/kth-smallest-product-of-two-sorted-arrays/description
// submission : https://leetcode.com/problems/kth-smallest-product-of-two-sorted-arrays/submissions/1677254956
// solution post : https://leetcode.com/problems/kth-smallest-product-of-two-sorted-arrays/solutions/6888546/
//     c-modern-readable-code-optimal-time-comp-d7zp/

// #include <ranges>
// #include <vector>

class Solution {
public:
// let 'n1' be a count of the numbers of the first stream given
// let 'n2'- of the second stream given
// time complexity O((n1 + n2) * log(range of numbers' values))
// space complexity O(n1 + n2)
// runtime 232 ms, beats 77.58 %
    [[nodiscard]]
    long long kthSmallestProduct(
        std::vector<int> const & nums1_,
        std::vector<int> const & nums2_,
        long long SmallestProductKTh_
    ) const;
};

long long Solution::kthSmallestProduct(
    std::vector<int> const & nums1_,
    std::vector<int> const & nums2_,
    long long SmallestProductKTh_
) const {
    namespace ranges = std::ranges;
    auto nums1Count{static_cast<int>(nums1_.size())};
    auto nums2Count{static_cast<int>(nums2_.size())};
    auto const isNonNegative{[] (auto const num)  { return num >= 0; }};
    auto firstPositive1Pos{static_cast<int>(
        ranges::find_if(nums1_, isNonNegative) - nums1_.begin())};
    auto firstPositive2Pos{static_cast<int>(
        ranges::find_if(nums2_, isNonNegative) - nums2_.begin())};
    auto leftProduct{static_cast<long long>(-1e10)};
    auto rightProduct{static_cast<long long>(1e10)};
    while(leftProduct <= rightProduct) {
        auto midProduct{leftProduct + (rightProduct - leftProduct) / 2};
        auto productsLessThanMidCount{0ll};
        // Case 1: Negative * Nonnegative -> product is negative
        for(auto idx1{0}, idx2{firstPositive2Pos - 1};
            idx1 < firstPositive1Pos && idx2 >= 0;
        ) {
            if(static_cast<long long>(nums1_.at(idx1)) * nums2_.at(idx2) >
                midProduct
            ) {
                ++idx1;
            } else {
                productsLessThanMidCount += firstPositive1Pos - idx1;
                --idx2;
            }
        }
        // Case 2: Nonnegative * Nonnegative -> product is NonNegative
        for(auto idx1{firstPositive1Pos}, idx2{nums2Count - 1};
            idx1 < nums1Count && idx2 >= firstPositive2Pos;
        ) {
            if(static_cast<long long>(nums1_.at(idx1)) * nums2_.at(idx2) >
                midProduct
            ) {
                --idx2;
            } else {
                productsLessThanMidCount += idx2 - firstPositive2Pos + 1;
                ++idx1;
            }
        }
        // Case 3: Negative * Negative -> product is positive
        for(auto idx1{0}, idx2{firstPositive2Pos};
            idx1 < firstPositive1Pos && idx2 < nums2Count;
        ) {
            if(static_cast<long long>(nums1_.at(idx1)) * nums2_.at(idx2) >
                midProduct
            ) {
                ++idx2;
            } else {
                productsLessThanMidCount += nums2Count - idx2;
                ++idx1;
            }
        }
        // Case 4: Nonnegative * Negative -> product is negative
        for(auto idx1{firstPositive1Pos}, idx2{0};
            idx1 < nums1Count && idx2 < firstPositive2Pos;
        ) {
            if(static_cast<long long>(nums1_.at(idx1)) * nums2_.at(idx2) >
                midProduct) {
                ++idx1;
            } else {
                productsLessThanMidCount += nums1Count - idx1;
                ++idx2;
            }
        }
        if(productsLessThanMidCount < SmallestProductKTh_) {
            leftProduct = midProduct + 1;
        } else {
            rightProduct = midProduct - 1;
        }
    }
    return leftProduct;
}
