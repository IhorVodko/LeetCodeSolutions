// problem : https://leetcode.com/problems/zero-array-transformation-i/description/
// submission : https://leetcode.com/problems/zero-array-transformation-i/submissions/1639486144
// solution post : https://leetcode.com/problems/zero-array-transformation-i/solutions/6763907/
//    c-modern-readable-code-optimal-time-comp-wg0v

// #include <vector>

class Solution {
public:
    using Arr2T = std::vector<std::vector<int>>;
// let 'n' be a length of the given array of numbers to decrement
// time complexity O(n)
// space complexity O(1)
// runtime 1 ms, beats 92.11 %
    bool isZeroArray(
        std::vector<int> const & nums_,
        Arr2T const & queries_
    ) const;
};

bool Solution::isZeroArray(
    std::vector<int> const & nums_,
    Arr2T const & queries_
) const {
    auto const numsCount{nums_.size()};
    auto maxDecrements{std::vector<int>(numsCount + 1, 0)};
    for(auto const & query: queries_) {
        auto const firstIdx{query.at(0)};
        auto const lastIdx{query.at(1)};
        ++maxDecrements.at(firstIdx);
        --maxDecrements.at(lastIdx + 1);
    }
    auto maxDecrement{0};
    for(auto i{0}; i < numsCount; ++i) {
        maxDecrement += maxDecrements[i];
        if(nums_.at(i) > maxDecrement) {
            return false;
        }
    }
    return true;
}
