// problem : https://leetcode.com/problems/largest-divisible-subset/description
// submission : https://leetcode.com/problems/largest-divisible-subset/submissions/1600685116
// solution post : https://leetcode.com/problems/largest-divisible-subset/solutions/6629574/
//     c-modern-readable-code-optimal-time-comp-fz41

// #include <algorithm>
// #include <vector>

// let 'n' be a given numbers count 
// time complexity O(n^2)
// space complexity O(n)
// runtime 8 ms, beats 83.85 %
class Solution {
public:
    std::vector<int> largestDivisibleSubset(
        std::vector<int> & nums_) const;
private:
    std::vector<int> CalculateMaxSusbsetSizes(
        std::vector<int> & nums_,
        int & maxSubsetSize_,
        int & maxSubsetIndex_
    ) const;
    std::vector<int> ReconstructMaxSubset(
        std::vector<int> const & nums_,
        std::vector<int> const & maxSubsetSizes_,
        int const maxSubsetSize_,
        int const maxSubsetIndex_
    ) const;
};

std::vector<int> Solution::largestDivisibleSubset(
    std::vector<int> & nums_
) const {
    if(nums_.empty()) {
        return {};
    } 
    auto const numsCount{nums_.size()};
    auto maxSubsetSize{-1};
    auto maxSubsetIndex{-1};
    auto const maxSubsetSizes{CalculateMaxSusbsetSizes(nums_, maxSubsetSize,
        maxSubsetIndex)}; 
    auto const maxSubset{ReconstructMaxSubset(nums_, maxSubsetSizes,
        maxSubsetSize, maxSubsetIndex)};
    return maxSubset;
}

std::vector<int> Solution::CalculateMaxSusbsetSizes(
    std::vector<int> & nums_,
    int & maxSubsetSize_,
    int & maxSubsetIndex_
) const {
    auto const numsCount{nums_.size()};
    auto maxSubsetSizes{std::vector<int>(numsCount, 0)}; 
    std::sort(nums_.begin(), nums_.end());
    for(auto currNumIdx{0}; currNumIdx < numsCount; ++currNumIdx) {
        auto subsetSize{0};
        for(auto prevNumIdx{0}; prevNumIdx < currNumIdx; ++prevNumIdx) {
            if(nums_[currNumIdx] % nums_[prevNumIdx] == 0 && 
                subsetSize < maxSubsetSizes[prevNumIdx]
            ) {
                subsetSize = maxSubsetSizes[prevNumIdx];
            }
        }
        maxSubsetSizes[currNumIdx] = subsetSize + 1;
        if(maxSubsetSize_ < maxSubsetSizes[currNumIdx]) {
            maxSubsetSize_ = maxSubsetSizes[currNumIdx];
            maxSubsetIndex_ = currNumIdx;
        }
    }
    return maxSubsetSizes;
}

std::vector<int> Solution::ReconstructMaxSubset(
    std::vector<int> const & nums_,
    std::vector<int> const & maxSubsetSizes_,
    int const maxSubsetSize_,
    int const maxSubsetIndex_
) const {
    auto maxSubset{std::vector<int>{}};
    maxSubset.reserve(nums_.size());
    auto currSize{maxSubsetSize_};
    auto currTail{nums_.at(maxSubsetIndex_)};
    for(auto i{maxSubsetIndex_}; i >= 0; --i) {
        if(currSize == 0) {
            break;
        } 
        if(currTail % nums_[i] == 0 && currSize == maxSubsetSizes_[i]) {
            maxSubset.emplace_back(nums_[i]);
            currTail = nums_[i];
            currSize -= 1;
        }
    }
    std::reverse(maxSubset.begin(), maxSubset.end());
    return maxSubset;
}
