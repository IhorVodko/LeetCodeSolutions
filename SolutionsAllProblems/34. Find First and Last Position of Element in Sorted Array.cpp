// problem : https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/description/
// submission : https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
//    submissions/1627858880
// solution post : https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/solutions/
//    6723214/c-modern-readable-code-beats-100-runtime-p90w

// #include <vector>

namespace Utility {
    enum class eBoundType {
        eLower,
        eUpper
    };
}

class Solution {
public:
// let 'n' be a length of the given array
// time complexity O(log2(n))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    std::vector<int> searchRange(
        std::vector<int> const & nums_,
        int const target_
    ) const;
private:
    int findBoundIdx(
        std::vector<int> const & nums_,
        int const target_,
        Utility::eBoundType const boundType_ 
    ) const;
};

std::vector<int> Solution::searchRange(
    std::vector<int> const & nums_,
    int const target_
) const {
    using Utility::eBoundType;
    auto const idxFirst{findBoundIdx(nums_, target_, eBoundType::eLower)};
    if(idxFirst == -1) {
        return {-1, -1};
    }
    auto const idxLast{findBoundIdx(nums_, target_, eBoundType::eUpper)};
    return {idxFirst, idxLast};
}

int Solution::findBoundIdx(
    std::vector<int> const & nums_,
    int const target_,
    Utility::eBoundType const boundType_
) const {
    using Utility::eBoundType;
    if(nums_.empty()) {
        return -1;
    }
    auto const N{nums_.size()};
    auto const begin{nums_.begin()};
    auto const end{nums_.end()};
    for(auto left{begin}, right{end - 1}, mid{begin + (end - 1 - begin) / 2};
        left <= right; mid = left + (right - left) / 2
    ) {
        if(*mid == target_) {
            if(boundType_ == eBoundType::eLower) {
                if(left == mid || *(mid - 1) != target_) {
                    return mid - begin; 
                }
                right = mid - 1;
            } else {
                if(mid == right || *(mid + 1) != target_) {
                    return mid - begin;
                }
                left = mid + 1;
            }
        } else if(target_ < *mid) {
           right = mid - 1; 
        } else {
            left = mid + 1;
        } 
    }
    return -1;
}
