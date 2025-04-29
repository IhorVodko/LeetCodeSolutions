// problem : https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times/description/
// submission : https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times/submissions/
//    1621224794
// solution post : https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times/solutions/
//    6699183/c-modern-readable-code-beats-100-runtime-f53c

// #include <algorithm>
// #include <vector>

// let 'n' be a length of the given array
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    long long countSubarrays(
        std::vector<int> const & nums_,
        int lowerLimitTimes_
    ) const;
};

long long Solution::countSubarrays(
    std::vector<int> const & nums_,
    int lowerLimitMaxNumCount_
) const {
    auto subArrsCount{0z};
    auto const numMax{*std::max_element(nums_.begin(), nums_.end())};
    auto maxNumCount{nums_.at(0) == numMax ? 1 : 0};
    for(auto first{nums_.begin()}, last{nums_.begin()}, end{nums_.end()};;) {
        if(maxNumCount == lowerLimitMaxNumCount_) {
            subArrsCount += end - last;
            maxNumCount -= *first == numMax ? 1 : 0;
            ++first;
        } else {
            ++last;
            if(last == end) {
                return subArrsCount;
            }
            maxNumCount += *last == numMax ? 1 : 0;
        }
    }
    return -1;
}
