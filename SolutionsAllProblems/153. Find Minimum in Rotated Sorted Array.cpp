// problem : https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/description/
// submission : https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/submissions/1627177872
// solution post : https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/solutions/6720918/
//    c-modern-readable-code-beats-100-runtime-4hrz

// #include <vector>

class Solution {
public:
// let 'n' be a length of the given array
// time complexity O(log2(n))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    int findMin(std::vector<int> const & nums_) const;
};

int Solution::findMin(std::vector<int> const & nums_) const {
    auto const begin{nums_.begin()};
    auto const end{nums_.end()};
    auto mid{begin + ((end - 1) - begin) / 2};
    for(auto left{begin}, right{end - 1}; left < right;) {
        if(*left <= *mid) {
            if(*left < *right) {
                right = mid - 1;
            } else {
                left = mid + 1;    
            }
        } else {
            right = mid;
        }
        mid = left + (right - left) / 2;
    }
    return *mid;
}
