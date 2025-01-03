// problem : https://leetcode.com/problems/number-of-ways-to-split-array/description/
// submission : https://leetcode.com/problems/number-of-ways-to-split-array/submissions/1496740050
// solution post : https://leetcode.com/problems/number-of-ways-to-split-array/solutions/6226545/c-modern-readable-code-beats-100-runtime-9bpl

// #include <algorithm>
// #include <vector>

// let 'n' be a parameter 'nums' length
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int waysToSplitArray(std::vector<int> const & nums) const {
        auto sumPostifx{std::accumulate(nums.cbegin(), nums.cend(), 0LL)}; 
        auto sumPrefix{0LL};
        auto ways{0};
        for(auto num{nums.cbegin()}, end(nums.cend() - 1); num < end; ++num) {
            sumPrefix += *num;
            sumPostifx -= *num;
            if(sumPrefix >= sumPostifx) {
                ++ways;
            }
        }
        return ways;
    }
};
