// problem : https://leetcode.com/problems/zero-array-transformation-ii/description/
// submission : https://leetcode.com/problems/zero-array-transformation-ii/submissions/1572544928
// solution post : https://leetcode.com/problems/zero-array-transformation-ii/solutions/6532858/
//     c-modern-readable-code-beats-93-runtime-hoxdb

// #include <algorithm>
// #include <vector>

// let 'a' be a length of the given array
// 'q' - count of the given queries
// time complexity O(a + q)
// space complexity O(a)
// runtime 3 ms, beats 93.49 %
class Solution {
public:
    int minZeroArray(
        std::vector<int> & nums_,
        std::vector<std::vector<int>> const & queries_
    ) const;
};

int Solution::minZeroArray(
    std::vector<int> & nums_,
    std::vector<std::vector<int>> const & queries_
) const {
    auto const numsSz{nums_.size()};
    auto sum{0};
    auto minQueriesCount{0};
    auto differenceArray{std::vector<int>(numsSz + 1, 0)};
    for(auto numIdx{0}; numIdx < numsSz; ++numIdx) {
        while(sum + differenceArray[numIdx] < nums_[numIdx]) {
            ++minQueriesCount;
            if(minQueriesCount > queries_.size()) {
                return -1;
            }
            auto const leftIdx{queries_[minQueriesCount - 1][0]};
            auto const rightIdx{queries_[minQueriesCount - 1][1]};
            auto const subtrahend{queries_[minQueriesCount - 1][2]};
            if(rightIdx >= numIdx) {
                differenceArray[std::max(leftIdx, numIdx)] += subtrahend;
                differenceArray[rightIdx + 1] -= subtrahend;
            }
        }
        sum += differenceArray[numIdx];
    }
    return minQueriesCount;
}
