// problem : https://leetcode.com/problems/count-equal-and-divisible-pairs-in-an-array/description/
// submission : https://leetcode.com/problems/count-equal-and-divisible-pairs-in-an-array/submissions/1611784429
// solution post : https://leetcode.com/problems/count-equal-and-divisible-pairs-in-an-array/solutions/6667963/
//    c-modern-readable-code-beats-100-runtime-2k41

// #include <vector>

// let 'n' be a given numbers count
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int countPairs(
        std::vector<int> const & nums_,
        int const divisor_
    ) const;
};

int Solution::countPairs(
    std::vector<int> const & nums_,
    int const divisor_
) const {
    auto pairsCount{0};
    auto const numsCount{nums_.size()};
    for(auto i{0}; i < numsCount - 1; ++i) {
        for(auto j{i + 1}; j < numsCount; ++j) {
            if(nums_[i] == nums_[j] && (i * j) % divisor_ == 0) {
                ++pairsCount;
            }
        }
    }
    return pairsCount;
}
