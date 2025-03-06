// problem : https://leetcode.com/problems/find-missing-and-repeated-values/description/
// submission : https://leetcode.com/problems/find-missing-and-repeated-values/submissions/1565247903
// solution post : https://leetcode.com/problems/find-missing-and-repeated-values/solutions/6506635/
//     c-modern-readable-code-beats-100-runtime-jk21

// #include <vector>

// let 'n' be a length and width of the given matrix
// time complexity O(n^2)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    using Arr2T = std::vector<std::vector<int>>;
    vector<int> findMissingAndRepeatedValues(Arr2T const & grid_) const {
        auto sum{0LL};
        auto sumSqr{0LL};
        auto const gridSz{static_cast<long long>(grid_.size())};
        for(auto const & row: grid_) {
            for(auto const num: row) {
                sum += num;
                sumSqr += static_cast<long long>(num) * num;
            }
        }
        auto const numsCount{gridSz * gridSz};
        auto sumDiff{sum - numsCount * (numsCount + 1) / 2};
        auto sumSqrDiff{sumSqr - numsCount * (numsCount + 1) *
            (2 * numsCount + 1) / 6};
        auto repeatedTwiceNum{(sumSqrDiff / sumDiff + sumDiff) / 2}; 
        auto missingNum{(sumSqrDiff / sumDiff - sumDiff) / 2}; 
        return {static_cast<int>(repeatedTwiceNum),
            static_cast<int>(missingNum)};
    }
};
