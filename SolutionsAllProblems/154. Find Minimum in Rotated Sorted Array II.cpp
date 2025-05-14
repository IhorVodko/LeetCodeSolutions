// problem : https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/description/
// submission : https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/submissions/1633910301
// solution post : https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/solutions/6744268/
//    c-modern-readable-code-beats-100-by-cybe-nmc1

// #include <vector>

class Solution {
public:
// let 'n' be a length of the given array
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    int findMin(std::vector<int> const & nums_) const;
};

int Solution::findMin(std::vector<int> const & nums_) const {
    auto const begin{nums_.begin()};
    auto const end{nums_.end()};
    auto left{begin};
    for(auto mid{begin + ((end - 1) - begin) / 2}, right{end - 1};
        left < right; mid = left + (right - left) / 2
    ) {
        if(*mid < *right) {
            right = mid;
        } else if(*mid > *right) {
            left = mid + 1;
        } else {
            --right;
        }
    }
    return *left;
}
