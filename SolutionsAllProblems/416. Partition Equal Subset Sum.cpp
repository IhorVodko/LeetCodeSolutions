// problem : https://leetcode.com/problems/partition-equal-subset-sum/description
// submission : https://leetcode.com/problems/partition-equal-subset-sum/submissions/1599765465
// solution post : https://leetcode.com/problems/partition-equal-subset-sum/solutions/6626245/
//     c-modern-readable-code-optimal-time-comp-vq4o

// #include <algorithm>
// #include <vector>

// let 'n' be a count of numbers given
// 's' sum of the numbers given
// time complexity O(n * s)
// space complexity O(n)
// runtime 129 ms, beats 48.83 %
class Solution {
public:
    bool canPartition(std::vector<int> const & nums_) const {
        auto totalSum{std::accumulate(nums_.begin(), nums_.end(), 0)};
        if(totalSum % 2 != 0) {
            return false;
        }
        auto subsetSum{totalSum / 2};
        auto dp{std::vector<bool>(subsetSum + 1, false)};
        dp.at(0) = true;
        for(auto const num: nums_) {
            for(auto sum{subsetSum}; sum >= num; --sum) {
                dp.at(sum) = dp.at(sum) || dp.at(sum - num);
            }
            if(dp.at(subsetSum)) {
                return true;
            }
        }
        return dp.at(subsetSum);
    }
};
