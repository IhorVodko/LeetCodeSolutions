// problem : https://leetcode.com/problems/find-k-th-smallest-pair-distance/description/
// submission : https://leetcode.com/problems/find-k-th-smallest-pair-distance/submissions/1640451962
// solution post : https://leetcode.com/problems/find-k-th-smallest-pair-distance/solutions/6767515/
//    c-modern-readable-code-optimal-time-comp-i30s

// #include <vector>

class Solution {
public:
// let 'n' be a numbers count given
// 'd' - absolute difference between any of two numbers given
// time complexity O(n * log2(max(d)) + n * log2(n))
// space complexity O(std::sort)
// runtime 1 ms, beats 78.50 %
    int smallestDistancePair(
        std::vector<int> & nums_,
        int const kThLargestDistance_
    ) const;
private:
    int CountDistancesLessThenMaxDistance(
        std::vector<int> const & nums_,
        int const maxDistance_
    ) const;
};

int Solution::smallestDistancePair(
    std::vector<int> & nums_,
    int const kThLargestDistance_
) const {
    std::sort(nums_.begin(), nums_.end());
    auto const numsCount{nums_.size()};
    auto leftDistance{0};
    auto rightDistance{nums_.at(numsCount - 1) - nums_.at(0)};
    while(leftDistance < rightDistance) {
        auto const midDistance{
            leftDistance + (rightDistance - leftDistance) / 2};
        auto const validDistancesCount{
            CountDistancesLessThenMaxDistance(nums_, midDistance)};
        if(validDistancesCount < kThLargestDistance_) {
            leftDistance = midDistance + 1;
        } else {
            rightDistance = midDistance;
        }
    }
    return leftDistance;
}

int Solution::CountDistancesLessThenMaxDistance(
    std::vector<int> const & nums_,
    int const maxDistance_
) const {
    auto validDistancesCount{0};
    auto numsCount{nums_.size()};
    auto leftNum{0};
    for(auto rightNum{0}; rightNum < numsCount; ++rightNum) {
        while(nums_.at(rightNum) - nums_.at(leftNum) > maxDistance_) {
            ++leftNum;
        }
        validDistancesCount += rightNum - leftNum;
    }
    return validDistancesCount;
}
