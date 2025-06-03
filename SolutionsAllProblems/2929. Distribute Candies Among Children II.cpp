// problem : https://leetcode.com/problems/distribute-candies-among-children-ii/description
// submission : https://leetcode.com/problems/distribute-candies-among-children-ii/submissions/1652844925
// solution post : https://leetcode.com/problems/distribute-candies-among-children-ii/solutions/6807978/
//    c-modern-readable-code-beats-100-runtime-i965

class Solution {
public:
// time complexity O(1)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    long long distributeCandies(
        int const candiesCount_,
        int const candiesLimitPerChild_
    ) const;
private:
    long long Calculate(long long const num_) const;
};

long long Solution::distributeCandies(
    int const candiesCount_,
    int const candiesLimitPerChild_
) const {
    auto const distributionsCountTotal{Calculate(candiesCount_ + 2)};
    auto const atLeastOneChildMoreThanLimit{
        3 * Calculate(candiesCount_ - candiesLimitPerChild_ + 1)};
    auto const atLeastTwoChildrenMoreThanLimit{
        3 * Calculate(candiesCount_ - (candiesLimitPerChild_ + 1) * 2 + 2)};
    auto const threeChildrenMoreThanLimit{
        Calculate(candiesCount_ - 3 * (candiesLimitPerChild_ + 1) + 2)};
    auto const validDistributionsCount{
            distributionsCountTotal
        -   atLeastOneChildMoreThanLimit
        +   atLeastTwoChildrenMoreThanLimit
        -   threeChildrenMoreThanLimit
    };
    return validDistributionsCount; 
}

long long Solution::Calculate(long long const num_) const {
    return num_ < 0 ? 0 : ((num_ - 1) * num_ / 2); 
}
