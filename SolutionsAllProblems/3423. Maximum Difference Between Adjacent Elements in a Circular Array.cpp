// problem : https://leetcode.com/problems/maximum-difference-between-adjacent-elements-in-a-circular-array/description/
// submission : https://leetcode.com/problems/maximum-difference-between-adjacent-elements-in-a-circular-array/
//    submissions/1662104647
// solution post : https://leetcode.com/problems/maximum-difference-between-adjacent-elements-in-a-circular-array/
//    solutions/6837048/c-modern-readable-code-beats-100-runtime-2w77

// #include <cmath>
// #include <vector>

class Solution {
public:
// let 'n' be a length of the given array
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    int maxAdjacentDistance(std::vector<int> const & nums_) const;
};

int Solution::maxAdjacentDistance(std::vector<int> const & nums_) const {
    using IntT = std::numeric_limits<int>;
    auto const numsSz{nums_.size()};
    if(numsSz < 2) {
        return -1;
    } 
    auto diffMax{std::abs(nums_.at(0) - nums_.at(numsSz - 1))};
    for(auto numIt{nums_.begin()}, numLast{nums_.end() - 1}; numIt < numLast;
        ++numIt
    ) {
        diffMax = std::max(diffMax, std::abs(*numIt - *(numIt + 1)));
    }
    return diffMax;
}
