// problem : https://leetcode.com/problems/maximum-unique-subarray-sum-after-deletion/description
// submission : https://leetcode.com/problems/maximum-unique-subarray-sum-after-deletion/submissions/1713638086
// solution post : https://leetcode.com/problems/maximum-unique-subarray-sum-after-deletion/solutions/7012668
//    /c-modern-readable-code-beats-100-runtime-77p8

// #include <algorithm>
// #include <bitset>
// #include <limits>
// #include <vector>

namespace Util {
    inline auto constexpr kMaxNumSz{100u};
}

class Solution {
public:
// let 'n' be a count of the given numbers
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    int maxSum(std::vector<int> const & nums_) const;
};

int Solution::maxSum(std::vector<int> const & nums_) const {
    using namespace Util;
    using intT = std::numeric_limits<int>;
    if(nums_.size() == 1) {
        return nums_.at(0);
    }
    auto uniqueNums{std::bitset<kMaxNumSz + 1>{}};
    auto sum{0};
    auto maxNum{intT::min()};
    for(auto const num: nums_) {
        maxNum = std::max(maxNum, num);
        if(num <= 0 || uniqueNums.test(num)) {
            continue;
        }
        uniqueNums.set(num);
        sum += num;
    }
    if(uniqueNums.none()) {
        sum = maxNum;
    }
    return sum;
}
