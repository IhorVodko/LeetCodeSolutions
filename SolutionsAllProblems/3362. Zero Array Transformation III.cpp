// problem : https://leetcode.com/problems/zero-array-transformation-iii/description
// submission : https://leetcode.com/problems/zero-array-transformation-iii/submissions/1641290419
// solution post : https://leetcode.com/problems/zero-array-transformation-iii/solutions/6770188/
//    c-modern-readable-code-optimal-time-comp-vpty

// #include <algorithm>
// #include <prioriyt_queue>
// #include <vector>

class Solution {
public:
    using Arr2T = std::vector<std::vector<int>>;
// let 'n' be a numbers count given
// 'r' - count of ranges(queries) given
// time complexity O(n + r * log2(r))
// space complexity O(n + r)
// runtime 115 ms, beats 68.67 %
    int maxRemoval(
        std::vector<int> const & nums_,
        Arr2T & ranges_
    ) const;
};

int Solution::maxRemoval(
    std::vector<int> const & nums_,
    Arr2T & ranges_
) const {
    std::sort(ranges_.begin(), ranges_.end());
    auto rangeEndsMaxFirst{std::priority_queue<int>{}};
    auto diffArrOfOps{std::vector<int>(nums_.size() + 1, 0)};
    auto opsCount{0};
    for(auto i1{0}, i2{0}; i1 < nums_.size(); ++i1) {
        opsCount += diffArrOfOps.at(i1);
        while(i2 < ranges_.size() && ranges_.at(i2).at(0) == i1) {
            rangeEndsMaxFirst.emplace(ranges_.at(i2).at(1));
            ++i2;
        }
        while(opsCount < nums_.at(i1) && !rangeEndsMaxFirst.empty() &&
            rangeEndsMaxFirst.top() >= i1
        ) {
            opsCount += 1;
            diffArrOfOps.at(rangeEndsMaxFirst.top() + 1) -= 1;
            rangeEndsMaxFirst.pop();
        }
        if(opsCount < nums_.at(i1)) {
            return -1;
        }
    }
    return rangeEndsMaxFirst.size();
}
