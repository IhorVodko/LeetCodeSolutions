// problem : https://leetcode.com/problems/longest-subarray-with-maximum-bitwise-and/description
// submission : https://leetcode.com/problems/longest-subarray-with-maximum-bitwise-and/submissions/1717533692
// solution post : https://leetcode.com/problems/longest-subarray-with-maximum-bitwise-and/solutions/7025780/
//    c-modern-readable-code-beats-100-runtime-7z2n

// #include <algorithm>
// #include <vector>

class Solution {
public:
// let 'n' be a count of the given numbers
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    int longestSubarray(std::vector<int> const & nums_) const;
};

int Solution::longestSubarray(std::vector<int> const & nums_) const {
    auto const maxNum{*ranges::max_element(nums_)};
    auto subarrMaxSz{0};
    auto subarrSz{0};
    for(auto const num: nums_) {
        if(num == maxNum) {
            ++subarrSz;
        } else {
            subarrMaxSz = std::max(subarrMaxSz, subarrSz);
            subarrSz = 0;
        }
    }
    subarrMaxSz = std::max(subarrMaxSz, subarrSz);
    return  subarrMaxSz;
}
