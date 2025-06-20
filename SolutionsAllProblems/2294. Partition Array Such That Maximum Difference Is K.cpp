// problem : https://leetcode.com/problems/partition-array-such-that-maximum-difference-is-k/description
// submission : https://leetcode.com/problems/partition-array-such-that-maximum-difference-is-k/submissions/1670561975
// solution post : https://leetcode.com/problems/partition-array-such-that-maximum-difference-is-k/solutions/6865775/
//    c-modern-readable-code-optimal-time-comp-9b0p

// #include <algorithm>
// #include <ranges>
// #include <vector>

class Solution {
public:
// let 'n' be a count of the give numbers
// time complexity O(n * log2(n))
// space complexity O(n)
// runtime 27 ms, beats 93.52 %
    [[nodiscard]]
    int partitionArray(
        std::vector<int> & nums_,
        int const diffMax_
    ) const;
};

int Solution::partitionArray(
    std::vector<int> & nums_,
    int const diffMax_
) const {
    std::ranges::sort(nums_);
    auto subSeqMinCount{1};
    auto numMin{nums_.at(0)};
    for(auto const & num: nums_) {
        if(num - numMin > diffMax_) {
            numMin = num;
            ++subSeqMinCount;
        }
    }
    return subSeqMinCount;
}
