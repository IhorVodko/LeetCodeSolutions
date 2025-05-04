// problem : https://leetcode.com/problems/number-of-equivalent-domino-pairs/description/
// submission : https://leetcode.com/problems/number-of-equivalent-domino-pairs/submissions/1625574243
// solution post : https://leetcode.com/problems/number-of-equivalent-domino-pairs/solutions/6715099/
//    c-modern-readable-code-beats-100-runtime-sdua

// #include <algorithm>
// #include <vector>

class Solution {
public:
    using Arr2T = std::vector<std::vector<int>>;
// let 'n' be a count of the given dominoes
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    int numEquivDominoPairs(vector<vector<int>> const & dominoes_) const;
};

int Solution::numEquivDominoPairs(vector<vector<int>> const & dominoes_) const {
    auto valCounts{std::vector<int>(100, 0)};
    auto pairsEqualCount{0};
    for(auto const & domino: dominoes_) {
        auto const & val1{domino.at(0)};
        auto const & val2{domino.at(1)};
        auto val{std::min(val1, val2) * 10 + std::max(val1, val2)};
        pairsEqualCount += valCounts.at(val);
        ++valCounts.at(val);
    }
    return pairsEqualCount;
} 
