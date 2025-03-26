// problem : https://leetcode.com/problems/minimum-operations-to-make-a-uni-value-grid/description/
// submission : https://leetcode.com/problems/minimum-operations-to-make-a-uni-value-grid/submissions/1586995593
// solution post : https://leetcode.com/problems/minimum-operations-to-make-a-uni-value-grid/solutions/6582337/
//     c-modern-readable-code-beats-95-runtime-y81fe

// #include <algorithm>
// #include <vector>

// let 'n' be a count of numbers given
// time complexity O(n)
// space complexity O(n)
// runtime 9 ms, beats 94.53 %
class Solution {
public:
    using Arr2T = std::vector<std::vector<int>>;
    int minOperations(
        Arr2T const & grid_,
        int const diff_
    ) const {
        auto numsSorted{std::vector<int>{}};
        auto const rowsCount{grid_.size()};
        auto const colsCount{grid_.at(0).size()};
        auto const numsCount{rowsCount * colsCount};
        numsSorted.reserve(numsCount);
        auto minOpsCount{0};
        for(auto const & row: grid_) {
            for(auto const num: row) {
                numsSorted.emplace_back(num);
            }
        }
        std::nth_element(numsSorted.begin(),
            numsSorted.begin() + numsCount / 2, numsSorted.end());
        auto const uniValue{numsSorted[numsCount / 2]};
        for(auto const num: numsSorted) {
            if(num % diff_ != uniValue % diff_) {
                return -1;
            }
            minOpsCount += std::abs(uniValue - num) / diff_;
        }
        return minOpsCount; 
    }
};
