// problem : https://leetcode.com/problems/longest-harmonious-subsequence/description/
// submission : https://leetcode.com/problems/longest-harmonious-subsequence/submissions/1681750539
// solution post : https://leetcode.com/problems/longest-harmonious-subsequence/solutions/6903868/
//    c-modern-readable-code-optimal-time-comp-edwh

// #include <algorithm>
// #include <vector>
// #include <unordered_map>

class Solution {
public:
// let 'n' be a count of the given numbers
// 'u' - count of the unique numbers
// time complexity O(n)
// space complexity O(u)
// runtime 13 ms, beats 78.03 %
    [[nodiscard]]
    int findLHS(std::vector<int> const & nums_) const;
};

int Solution::findLHS(std::vector<int> const & nums_) const {
    auto const numsSz{nums_.size()};
    auto numToCount{std::unordered_map<int, int>{}};
    auto subseqSzMax{0};
    for(auto const num: nums_) {
        ++numToCount[num];
    }
    for(auto const [num, count]: numToCount) {
        if(auto numToCountIt{numToCount.find(num + 1)}; numToCountIt != numToCount.end()) {
            auto const subseqSzCurr{numToCount.at(num) + numToCountIt->second};
            subseqSzMax = std::max(subseqSzMax, subseqSzCurr);
        }
    }
    return subseqSzMax;
}
