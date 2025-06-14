// problem : https://leetcode.com/problems/minimize-the-maximum-difference-of-pairs/description/
// submission : https://leetcode.com/problems/minimize-the-maximum-difference-of-pairs/submissions/1663988534
// solution post : https://leetcode.com/problems/minimize-the-maximum-difference-of-pairs/solutions/6843452/
//    c-modern-readable-code-beats-99-runtime-q0d85

// #include <algorithm>
// #include <vector>

class Solution {
public:
// let 'n' be a count of the given numbers
// 'm' - the maximum number of the given
// time complexity O(n * (log2(m) + log2(n))
// space complexity O(n)
// runtime 15 ms, beats 99.17 %
    int minimizeMax(
        std::vector<int> & nums_,
        int const p
    ) const;
private:
    int CountValidPairs(
        std::vector<int> & nums_,
        int const diffUpperLimit_
    ) const;
};

int Solution::minimizeMax(
    std::vector<int> & nums_,
    int const pairsCountReq_
) const {
    std::sort(nums_.begin(), nums_.end());
    auto const numsCount{nums_.size()};
    auto leftDiff{0};
    auto rightDiff{nums_.at(numsCount - 1) - nums_.at(0)};
    while(leftDiff < rightDiff) {
        auto const midDiff{leftDiff + (rightDiff - leftDiff) / 2};
        if(CountValidPairs(nums_, midDiff) >= pairsCountReq_) {
            rightDiff = midDiff;
        } else {
            leftDiff = midDiff + 1;
        }
    }
    return leftDiff;
}

int Solution::CountValidPairs(
    std::vector<int> & nums_,
    int const diffUpperLimit_
) const {
    auto pairsCount{0};
    for(auto numIt{nums_.begin()}, numLastIt{nums_.end() - 1};
        numIt < numLastIt; ++numIt
    ) {
        if(*(numIt + 1) - *numIt <= diffUpperLimit_) {
            ++pairsCount;
            ++numIt;
        }
    }
    return pairsCount;
}
