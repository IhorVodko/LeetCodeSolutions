// problem : https://leetcode.com/problems/count-subarrays-of-length-three-with-a-condition/description/
// submission : https://leetcode.com/problems/count-subarrays-of-length-three-with-a-condition/submissions/1620224169
// solution post : https://leetcode.com/problems/count-subarrays-of-length-three-with-a-condition/solutions/6695559/
//     c-modern-readable-code-beats-100-runtime-y2t7

// #include <vector>

// let 'n' be a length of the given array
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int countSubarrays(std::vector<int> const & nums_) const;
};

int Solution::countSubarrays(std::vector<int> const & nums_) const {
    auto subArrsCount{0};
    for(auto first{nums_.begin()}, second{nums_.begin() + 1},
        third{nums_.begin() + 2}, end{nums_.end()}; third < end;
        ++first, ++second, ++third
    ) {
        subArrsCount += (*first + *third) * 2 == *second ? 1 : 0;
    }
    return subArrsCount;
}
