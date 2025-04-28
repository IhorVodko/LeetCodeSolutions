// problem : https://leetcode.com/problems/count-of-interesting-subarrays/description/
// submission : https://leetcode.com/problems/count-of-interesting-subarrays/submissions/1620179182
// solution post : https://leetcode.com/problems/count-of-interesting-subarrays/solutions/6695389/
//     c-modern-readable-code-optimal-time-comp-0hy5

// #include <vector>
// #include <unordered_map>

// let 'n' be length of the given array
// 'm' - values of the given modulus
// time complexity O(n)
// space complexity O(min(n, m))
// runtime 48 ms, beats 86.27 %
class Solution {
public:
    long long countInterestingSubarrays(
        std::vector<int> const & nums_,
        int const modulus_,
        int const remainder_
    ) const;
};

long long Solution::countInterestingSubarrays(
    std::vector<int> const & nums_,
    int const modulus_,
    int const remainder_
) const {
    auto const numsCount{nums_.size()};
    auto idxsToCount{std::unordered_map<int, size_t>{}};
    auto subArrsCount{0z};
    auto prefisSumSubArrsCount{0};
    idxsToCount[0] = 1;
    for(size_t i{0}; i < numsCount; ++i) {
        prefisSumSubArrsCount += nums_[i] % modulus_ == remainder_ ? 1 : 0;
        subArrsCount += idxsToCount[
            (prefisSumSubArrsCount - remainder_ + modulus_) % modulus_];
        ++idxsToCount[prefisSumSubArrsCount % modulus_];
    }
    return subArrsCount;
}
