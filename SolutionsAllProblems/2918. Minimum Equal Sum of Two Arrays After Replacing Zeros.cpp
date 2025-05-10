// problem : https://leetcode.com/problems/minimum-equal-sum-of-two-arrays-after-replacing-zeros/description/
// submission : https://leetcode.com/problems/minimum-equal-sum-of-two-arrays-after-replacing-zeros/submissions/
//    1629829694
// solution post : https://leetcode.com/problems/minimum-equal-sum-of-two-arrays-after-replacing-zeros/solutions/
//    6729744/c-modern-readable-code-optimal-time-comp-2xt0

// #include <algorithm>
// #include <vector>

class Solution {
public:
// let 'n1' be a length of the first given array
// let 'n2' - length of the second given array
// time complexity O(n1 + n2)
// space complexity O(1)
// runtime 121 ms, beats 86.10 %
    long long minSum(
        std::vector<int> const & nums1_,
        std::vector<int> const & nums2_
    ) const;
private:
    std::pair<long long, int> CountSumAndZeroes(
        std::vector<int> const & nums_
    ) const;
};

long long Solution::minSum(
    std::vector<int> const & nums1_,
    std::vector<int> const & nums2_
) const {
    auto const [sum1, zeroesCount1]{CountSumAndZeroes(nums1_)};
    auto const [sum2, zeroesCount2]{CountSumAndZeroes(nums2_)};
    if((sum1 < sum2 && zeroesCount1 == 0) ||
        (sum1 > sum2 && zeroesCount2 == 0)
    ) {
        return -1;
    }
    return std::max(sum1, sum2);
}

std::pair<long long, int> Solution::CountSumAndZeroes(
    std::vector<int> const & nums_
) const {
    auto sum{0LL};
    auto zeroesCount{0};
    for(auto const num: nums_) {
        sum += num;
        if(num == 0) {
            ++sum;
            ++zeroesCount;
        }
    }
    return {sum, zeroesCount};
}
