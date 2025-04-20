// problem : https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/description/
// submission : https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/submissions/1612916817
// solution post : https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/solutions/6672169/
//    c-modern-readable-code-optimal-time-comp-n1ld

// #include <algorithm>
// #include <vector>
// #include <unordered_map>

// let 'n' be a length of the given array
// time complexity O(n)
// space complexity O(n)
// runtime 159 ms, beats 60.92 %
class Solution {
public:
    int maxSubArrayLen(
        std::vector<int> const & nums_,
        int const targetSum_
    ) const {
        auto prefixSum{0};
        auto maxSubarrLength{0};
        auto prefixSumToIdx{std::unordered_map<long long, int>{}};
        for(auto idx{0}; idx < nums_.size(); ++idx) {
            prefixSum += nums_[idx];
            if(prefixSum == targetSum_) {
                maxSubarrLength = idx + 1;
            } else {
                auto const compliment{
                    static_cast<long long>(prefixSum) - targetSum_};
                if(prefixSumToIdx.contains(compliment)) {
                    maxSubarrLength = std::max(maxSubarrLength,
                        idx - prefixSumToIdx[compliment]);
                }
            }
            prefixSumToIdx.insert({prefixSum, idx});
        }
        return maxSubarrLength;
    }
};
