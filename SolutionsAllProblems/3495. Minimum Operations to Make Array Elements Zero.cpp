// problem : https://leetcode.com/problems/minimum-operations-to-make-array-elements-zero/description
// submission : https://leetcode.com/problems/minimum-operations-to-make-array-elements-zero/submissions/1761615556
// solution post : https://leetcode.com/problems/minimum-operations-to-make-array-elements-zero/solutions/7161904/
//    c-modern-readable-code-optimal-time-comp-nuyg

// #include <algorithm>

class Solution {
public:
    using queryT = std::vector<int>;
    using queriesT = std::vector<queryT>;
// let 'n' be a length of the given
// 'r' - a maximum value of the right index among all given queries
// time complexity O(n * log2(r))
// space complexity O(1)
// runtime 24 ms, beats 60.15 %
    [[nodiscard]]
    long long minOperations(queriesT const & queries_) const;
    [[nodiscard]]
    long long CountOps(int const num_) const;
};

long long Solution::minOperations(queriesT const & queries_) const {
    auto opCountTotal{0ll};
    for(auto const & query: queries_) {
        auto const lIdx{query.at(0)};
        auto const rIdx{query.at(1)};
        auto const lIdxOpCount{CountOps(rIdx)};
        auto const rIdxOpCount{CountOps(lIdx - 1)};
        auto const opCountCurr{(lIdxOpCount - rIdxOpCount + 1) / 2};
        opCountTotal += opCountCurr;
    }
    return opCountTotal;
}

long long Solution::CountOps(int const num_) const {
    auto stepCount{1ll};
    auto currNum{1};
    auto opCountTotal{0ll};
    while(currNum <= num_) {
        auto const nextNum{std::min(currNum * 2 - 1, num_)};
        auto const numLeft{nextNum - currNum + 1};
        auto const opCountCurr{(stepCount + 1) / 2 * numLeft};
        opCountTotal += opCountCurr; 
        ++stepCount;
        currNum *= 2;
    }
    return opCountTotal;
}
