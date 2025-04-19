// problem : https://leetcode.com/problems/count-the-number-of-fair-pairs/description/
// submission : https://leetcode.com/problems/count-the-number-of-fair-pairs/submissions/1611868664
// solution post : https://leetcode.com/problems/count-the-number-of-fair-pairs/solutions/6668167/
//    c-modern-readable-code-beats-99-runtime-6k8e8

// #include <algorithm>
// #include <vector>

// let 'n' be a count of the given numbers
// time complexity O(n * log(n))
// space complexity O(1)
// runtime 22 ms, beats 99.10 %
class Solution {
public:
    long long countFairPairs(
        std::vector<int> & nums_,
        int const lowerLimit_,
        int const upperLimit_
    ) const {
        std::sort(nums_.begin(), nums_.end());
        return LowerBound(nums_, upperLimit_ + 1) -
            LowerBound(nums_, lowerLimit_);
    }
private:
    long long LowerBound(
        std::vector<int> & nums_,
        int const num_ 
    ) const {
        auto lowerIdx{0};
        auto upperIdx{nums_.size() - 1};
        auto pairsCount{0ll};
        while(lowerIdx < upperIdx) {
            auto const sum{nums_[lowerIdx] + nums_[upperIdx]};
            if(sum < num_) {
                pairsCount += upperIdx - lowerIdx;
                ++lowerIdx;
            } else {
                --upperIdx;
            }
        }
        return pairsCount;
    }
};
