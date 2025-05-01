// problem : https://leetcode.com/problems/find-peak-element/description/
// submission : https://leetcode.com/problems/find-peak-element/submissions/1623094929
// solution post : https://leetcode.com/problems/find-peak-element/solutions/6705949/
//    c-modern-readable-code-beats-100-runtime-tzv6

// #include <vector>

// let 'n' be a length of the given array
// time complexity O(log2(n))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int findPeakElement(std::vector<int> const & nums_) const;
private:
};

int Solution::findPeakElement(std::vector<int> const & nums_) const {
    auto const begin{nums_.begin()};
    auto const end{nums_.end()};
    auto left{begin};
    for(auto right{end - 1}, mid{begin + (end - 1 - begin) / 2}; left < right;
        mid = left + (right - left) / 2
    ) {
        if(*mid > *(mid + 1)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left - begin; 
}
