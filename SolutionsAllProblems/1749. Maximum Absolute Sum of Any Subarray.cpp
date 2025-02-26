// problem : https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/description/
// submission : https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/submissions/1556445017
// solution post : https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/solutions/6471982/
//     c-modern-readable-code-beats-100-runtime-o21e

// #include <algoritm>
// #include <vector>

// let 'n' be a length of the given array
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int maxAbsoluteSum(std::vector<int> & nums) const {
        auto minPrefixSum{0};
        auto maxPrefixSum{0};
        auto prefixSum{0};
        for(auto const num: nums) {
            prefixSum += num;
            minPrefixSum = std::min(minPrefixSum, prefixSum);
            maxPrefixSum = std::max(maxPrefixSum, prefixSum);
        }
        return maxPrefixSum - minPrefixSum;
    }
};
