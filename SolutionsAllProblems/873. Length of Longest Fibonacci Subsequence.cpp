// problem : https://leetcode.com/problems/length-of-longest-fibonacci-subsequence/description/
// submission : https://leetcode.com/problems/length-of-longest-fibonacci-subsequence/submissions/1557473481
// solution post : https://leetcode.com/problems/length-of-longest-fibonacci-subsequence/solutions/6478620/
//     c-modern-readable-code-optimal-time-comp-3eop

// #include <array>
// #include <alogrithm>
// #include <vector>

namespace Consants {
    auto static dp{std::array<std::array<int, 1000>, 1000>{}};
}

// let 'n' be a length of the given array
// time complexity O(n^2)
// space complexity O(n^2)
// runtime 290 ms, beats 55.69 %
class Solution {
public:
    int lenLongestFibSubseq(std::vector<int> const & nums) const {
        using namespace Consants;
        auto maxSubseq{0};
        auto const numsCount{nums.size()};
        auto numToIdx{std::unordered_map<int, int>{}};
        for(auto lastIdx{0}; lastIdx < numsCount; ++lastIdx) {
            numToIdx[nums[lastIdx]] = lastIdx;
            for(auto startIdx{0}; startIdx < lastIdx; ++startIdx) {
                auto const diffNum{nums[lastIdx] - nums[startIdx]};
                auto prevIdx{numToIdx.contains(diffNum) ?
                    numToIdx[diffNum] : -1};
                if(diffNum < nums[startIdx] && prevIdx >= 0) {
                    dp[startIdx][lastIdx] = dp[prevIdx][startIdx] + 1;
                } else {
                    dp[startIdx][lastIdx] = 2;
                } 
                maxSubseq = std::max(maxSubseq, dp[startIdx][lastIdx]);
            }
        }
        return maxSubseq > 2 ? maxSubseq : 0;
    }
};
