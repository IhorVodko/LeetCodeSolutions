// problem : https://leetcode.com/problems/split-array-largest-sum/submissions/1641243354/
// submission : https://leetcode.com/problems/split-array-largest-sum/submissions/1641243354
// solution post : https://leetcode.com/problems/split-array-largest-sum/solutions/6770023/
//    c-modern-readable-code-beats-100-by-cybe-szjt

// #include <algorithm>
// #include <limits>
// #include <vector>

class Solution {
public:
// let 'n' be a length of the given array
// 's' - sum of the numbers in the given array 
// time complexity O(n * log2(S))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    int splitArray(
        std::vector<int> const & nums_,
        int const subArraysCount_
    ) const;
private:
    int CountMinSubarrsRequired(
        std::vector<int> const & nums_,
        int const sumAllowedMax_
    ) const;
};

int Solution::splitArray(
    std::vector<int> const & nums_,
    int const subArraysCount_
) const {
    auto sum{0};
    auto numMax{std::numeric_limits<int>::min()};
    for(auto const num: nums_) {
        sum += num;
        numMax = std::max(numMax, num);
    }
    auto left{numMax};
    auto right{sum};
    auto minMaxSubArrSum{0};
    while(left <= right) {
        auto const sumAllowedMax{left + (right - left) / 2};
        auto const minSubarrsRequiredCount{
            CountMinSubarrsRequired(nums_, sumAllowedMax)};
        if(minSubarrsRequiredCount <= subArraysCount_) {
            right = sumAllowedMax - 1;
            minMaxSubArrSum = sumAllowedMax;
        } else {
            left = sumAllowedMax + 1;
        }
    }
    return minMaxSubArrSum;
}

int Solution::CountMinSubarrsRequired(
    std::vector<int> const & nums_,
    int const sumAllowedMax_
) const {
    auto sumRunning{0};
    auto splitsRequiredCount{0};
    for(auto const num: nums_) {
        if(sumRunning + num <= sumAllowedMax_) {
            sumRunning += num;
        } else {
            sumRunning = num;
            ++splitsRequiredCount; 
        }
    }
    return splitsRequiredCount + 1;
}
