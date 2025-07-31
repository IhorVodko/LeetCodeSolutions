// problem : https://leetcode.com/problems/bitwise-ors-of-subarrays/description/
// submission : https://leetcode.com/problems/bitwise-ors-of-subarrays/submissions/1718162272
// solution post : https://leetcode.com/problems/bitwise-ors-of-subarrays/solutions/7027795
//    /c-modern-readable-code-optimal-time-comp-gcx6

// #include <ranges>
// #include <vector>
// #include <unordered_set>

class Solution {
public:
// let 'n' be a count of the given numbers
// 'm' - bit size of the number given
// time complexity O(n)
// space complexity O(m)
// runtime 707 ms, beats 83.22 %
    [[nodiscard]]
    int subarrayBitwiseORs(std::vector<int> & nums_) const;
};

int Solution::subarrayBitwiseORs(std::vector<int> & nums_) const {
    namespace views = std::views;
    auto uniqueOrVals{std::unordered_set<int>{}};
    auto const numsSz{std::ssize(nums_)};
    for(auto const currIdx: views::iota(0, numsSz)) {
        auto prevOrVal{0};
        auto currOrVal{nums_.at(currIdx)};
        uniqueOrVals.emplace(currOrVal);
        auto prevIdx{currIdx - 1};
        while(prevIdx >= 0 && currOrVal != prevOrVal) {
            auto const currNum{nums_.at(prevIdx)};
            currOrVal |= currNum;
            prevOrVal |= currNum;
            uniqueOrVals.emplace(currOrVal);
            --prevIdx;
        }
    }
    auto const uniqueOrValsCount{uniqueOrVals.size()};
    return uniqueOrValsCount;
}
