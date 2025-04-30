// problem : https://leetcode.com/problems/search-in-rotated-sorted-array/description/
// submission : https://leetcode.com/problems/search-in-rotated-sorted-array/submissions/1622010726
// solution post : https://leetcode.com/problems/search-in-rotated-sorted-array/solutions/6702353/
//     c-modern-readable-code-beats-100-runtime-5d6y

// #include <vector>

class Solution {
public:
    int search(
        std::vector<int> const & nums_,
        int const target_
    ) const;
};

// let 'n' be a length of the given array
// time complexity O(log(n))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
int Solution::search(
    std::vector<int> const & nums_,
    int const target_
) const {
    auto const begin{nums_.begin()};
    auto const end{nums_.end()};
    for(auto left{begin}, right{end - 1}, mid{begin + (end - 1 - begin) / 2};
        left <= right; mid = left + (right - left) / 2
    ) {
        if(*mid == target_) {
            return mid - begin;
        } else if(*mid >= *left) {
            if(*left <= target_ && target_ < *mid) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {
            if(*mid < target_ && target_ <= *right) {
                left = mid + 1;
            } else {
                right = mid - 1;
            } 
        }
    }
    return -1;
}
