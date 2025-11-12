// problem : https://leetcode.com/problems/maximum-sum-circular-subarray/description/
// submission : https://leetcode.com/problems/maximum-sum-circular-subarray/submissions/1827844560
// solution post : https://leetcode.com/problems/maximum-sum-circular-subarray/solutions/7343927/
//    c-modern-readable-code-beats-100-runtime-mg14

// import std;

class Solution {
public:
// let 'n' be the number of given nubmers
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto maxSubarraySumCircular(
        std::span<int const> const nums_
    ) const -> int;
};

auto Solution::maxSubarraySumCircular(
    std::span<int const> const nums_
) const -> int {
    if(nums_.empty()) {
        return 0;
    }
    auto currMaxSum{0};
    auto currMinSum{0};
    auto maxSum{nums_[0]};
    auto minSum{nums_[0]};
    auto totalSum{0};
    for(auto const num: nums_) {
        currMaxSum = std::max(currMaxSum, 0) + num;
        maxSum = std::max(maxSum, currMaxSum);
        currMinSum = std::min(currMinSum, 0) + num;
        minSum = std::min(minSum, currMinSum);
        totalSum += num;
    }
    if(totalSum == minSum) {
        return maxSum;
    }
    auto const maxSumCircular{totalSum - minSum};
    auto maxSumSubArr{std::max(maxSum, maxSumCircular)};
    return maxSumSubArr;
}
