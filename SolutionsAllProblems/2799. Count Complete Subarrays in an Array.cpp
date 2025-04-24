// problem : https://leetcode.com/problems/count-complete-subarrays-in-an-array/description/
// submission : https://leetcode.com/problems/count-complete-subarrays-in-an-array/submissions/1616561110
// solution post : https://leetcode.com/problems/count-complete-subarrays-in-an-array/solutions/6683149/
//     c-modern-readable-code-beats-98-runtime-mz92p

// #include <vector>
// #include <unordered_map>

// let 'n' be a count of the given numbers
// time complexity O(n)
// space complexity O(n)
// runtime 6 ms, beats 97.86 %
class Solution {
public:
    int countCompleteSubarrays(std::vector<int> const & nums_) const;
};

int Solution::countCompleteSubarrays(std::vector<int> const & nums_) const {
    auto numToCount{std::unordered_map<int, size_t>{}};
    for(auto const num: nums_) {
        ++numToCount[num];
    }
    auto const distinctNumsCount{numToCount.size()};
    auto subArrsCount{0};
    numToCount = std::unordered_map<int, size_t>{};
    ++numToCount[nums_.at(0)];
    for(auto first{nums_.begin()}, last{nums_.begin()}, end{nums_.end()};
        last < end;
    ) {
        if(numToCount.size() == distinctNumsCount) {
            subArrsCount += end - last;
            if(--numToCount.at(*first) == 0) {
                numToCount.erase(*first);
            }
            ++first;
        } else {
            if(++last == end) {
                return subArrsCount;
            }
            ++numToCount[*last]; 
        }
    } 
    return subArrsCount;
} 
