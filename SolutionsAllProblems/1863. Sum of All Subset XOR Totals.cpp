// problem : https://leetcode.com/problems/sum-of-all-subset-xor-totals/description/
// submission : https://leetcode.com/problems/sum-of-all-subset-xor-totals/submissions/1600623385
// solution post : https://leetcode.com/problems/sum-of-all-subset-xor-totals/solutions/6629326/
//     c-modern-readable-code-beats-100-runtime-4w6p

// #include <algorithm>
// #include <vector>

// let 'n' be count of numbers given
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int subsetXORSum(std::vector<int> const & nums_) const;
};

int Solution::subsetXORSum(std::vector<int> const & nums_) const {
    auto result{std::accumulate(nums_.begin(), nums_.end(), 0, [&]
        (auto const init, auto const num) {return init | num;})};
    return result << (nums_.size() - 1);
}
