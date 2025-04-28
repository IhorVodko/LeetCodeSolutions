// problem : https://leetcode.com/problems/count-subarrays-with-fixed-bounds/description/
// submission : https://leetcode.com/problems/count-subarrays-with-fixed-bounds/submissions/1620200663
// solution post : https://leetcode.com/problems/count-subarrays-with-fixed-bounds/solutions/6695479/
//     c-modern-readable-code-beats-100-runtime-kh0i

// #include <algorithm>
// #include <vector>

// let 'n' be a length of the given array
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    long long countSubarrays(
        std::vector<int> const & nums_,
        int const numMin_,
        int const numMax_
    ) const;
};

long long Solution::countSubarrays(
    std::vector<int> const & nums_,
    int const numMin_,
    int const numMax_
) const {
    auto subArrsTotalCount{0z};
    auto minValidIdx{-1};
    auto maxValidIdx{-1};
    auto recentNotValidIdx{-1};
    auto const numsCount{nums_.size()};
    for(size_t i{0}; i < numsCount; ++i) {
        auto const num{nums_[i]};
        if(num < numMin_ || num > numMax_) {
            recentNotValidIdx = i;
        }
        minValidIdx = num == numMin_ ? i : minValidIdx;
        maxValidIdx = num == numMax_ ? i : maxValidIdx;
        auto const subArrsCount{std::max(0,
            std::min(maxValidIdx, minValidIdx) - recentNotValidIdx)};
        subArrsTotalCount += subArrsCount;
    } 
    return subArrsTotalCount;
}
