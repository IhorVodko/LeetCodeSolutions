// problem : https://leetcode.com/problems/median-of-two-sorted-arrays/description/
// submission : https://leetcode.com/problems/median-of-two-sorted-arrays/submissions/1639443694
// solution post : https://leetcode.com/problems/median-of-two-sorted-arrays/solutions/6763790/
//    c-modern-readable-code-beats-100-by-cybe-446m

// #include <algorithm>
// #include <limits>
// #include <vector>

class Solution {
public:
    using LimitsT = std::numeric_limits<int>;
// let 'l1' be a length of the given first array
// let 'l2' - length of the given second array
// time complexity O(log2(min(l1, l2))
// space complexity O(1)B
// runtime 0 ms, beats 100.00 %
    double findMedianSortedArrays(
        std::vector<int> const & nums1_,
        std::vector<int> const & nums2_
    ) const;
};

double Solution::findMedianSortedArrays(
    std::vector<int> const & nums1_,
    std::vector<int> const & nums2_
) const {
    auto const nums1Count{nums1_.size()};
    auto const nums2Count{nums2_.size()};
    if(nums1Count > nums2Count) {
        return findMedianSortedArrays(nums2_, nums1_);
    }
    auto leftIdx{0};
    auto rightIdx{nums1Count};
    while(leftIdx <= rightIdx) {
        auto partition1Idx{leftIdx + (rightIdx - leftIdx) / 2};
        auto partition2Idx{(nums1Count + nums2Count + 1) / 2 - partition1Idx};
        auto maxLeft1{partition1Idx == 0 ? LimitsT::min() :
            nums1_.at(partition1Idx - 1)};
        auto minRight1{partition1Idx == nums1Count ? LimitsT::max() :
            nums1_.at(partition1Idx)};
        auto maxLeft2{partition2Idx == 0 ? LimitsT::min() :
            nums2_.at(partition2Idx - 1)};
        auto minRight2{partition2Idx == nums2Count ? LimitsT::max() :
            nums2_.at(partition2Idx)};
        if(maxLeft1 <= minRight2 && maxLeft2 <= minRight1) {
            if((nums1Count + nums2Count) % 2 == 0) {
                auto const median{(std::max(maxLeft1, maxLeft2) +
                    std::min(minRight1, minRight2)) / 2.0};
                return median;
            } else {
                auto const median{std::max(maxLeft1, maxLeft2)};
                return median;
            }
        } else if(maxLeft1 > minRight2) {
            rightIdx = partition1Idx - 1;
        } else {
            leftIdx = partition1Idx + 1;
        }
    }
    return std::numeric_limits<double>::max();
}
