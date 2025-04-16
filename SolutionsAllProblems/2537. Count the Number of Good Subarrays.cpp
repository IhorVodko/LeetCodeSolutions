// problem : https://leetcode.com/problems/count-the-number-of-good-subarrays/description/
// submission : https://leetcode.com/problems/count-the-number-of-good-subarrays/submissions/1608439617
// solution post : https://leetcode.com/problems/count-the-number-of-good-subarrays/solutions/6656320/
//     c-modern-readable-code-optimal-time-comp-wift

// #include <iterator>
// #include <vector>

// let 'n' be a count of the given numbers
// time complexity O(n)
// space complexity O(n)
// runtime 77 ms, beats 75.12 %
class Solution {
public:
    long long countGood(
        std::vector<int> const & nums_,
        int const minPairsRequired_
    ) const;
};

long long Solution::countGood(
    std::vector<int> const & nums_,
    int const minPairsRequired_
) const {
    auto const numsCount{nums_.size()};
    auto duplicateNumsCount{0};
    auto numToCount{std::unordered_map<int, int>{{nums_.at(0), 1}}};
    auto goodSubArrsCount{0LL};
    auto rightNumIt{nums_.begin()};
    for(auto leftNumIt{nums_.begin()}, numsEnd{nums_.end()};
        leftNumIt < numsEnd; ++leftNumIt
    ) {
        while(duplicateNumsCount < minPairsRequired_ &&
            rightNumIt + 1 < numsEnd
        ) {
            ++rightNumIt;
            duplicateNumsCount += numToCount[*rightNumIt];
            ++numToCount[*rightNumIt];
        }
        if(duplicateNumsCount >= minPairsRequired_) {
            goodSubArrsCount += std::distance(rightNumIt, numsEnd);
        }
        --numToCount[*leftNumIt];
        duplicateNumsCount -= numToCount[*leftNumIt];
    }
    return goodSubArrsCount;
}
