// problem : https://leetcode.com/problems/maximum-candies-allocated-to-k-children/description/
// submission : https://leetcode.com/problems/maximum-candies-allocated-to-k-children/submissions/1573935486
// solution post : https://leetcode.com/problems/maximum-candies-allocated-to-k-children/solutions/6537313/
//     c-modern-readable-code-optimal-time-comp-4fm4

// #include <algorithm>
// #include <vector>

// let 'c' be a count of the piles of candies
// 'm' - the greatest count of canies in a pile
// time complexity O(c * log(m))
// space complexity O(1)
// runtime 19 ms, beats 84.83 %
class Solution {
public:
    int maximumCandies(
        std::vector<int> const & candies_,
        long long childrenCount
    ) const ;
private:
    bool IsEnoughCandies(
        std::vector<int> const & candies_,
        long long const childrenCount,
        int const candiesPerChild_ 
    ) const;
};
 

int Solution::maximumCandies(
    std::vector<int> const & candies_,
    long long childrenCount
) const {
    auto maxCandiesInPile{*std::max_element(candies_.begin(), candies_.end())};
    auto minCandiesPerChild{0};
    auto maxCandiesPerChild{maxCandiesInPile};
    while(minCandiesPerChild < maxCandiesPerChild) {
        auto const middleCandiesPerChild{(maxCandiesPerChild +
            minCandiesPerChild + 1) / 2};
        if(IsEnoughCandies(candies_, childrenCount, middleCandiesPerChild)) {
            minCandiesPerChild = middleCandiesPerChild;
        } else {
            maxCandiesPerChild = middleCandiesPerChild - 1;
        }
    }
    return minCandiesPerChild;
}

bool Solution::IsEnoughCandies(
    std::vector<int> const & candies_,
    long long const childrenCount,
    int const candiesPerChild_ 
) const {
    auto const childrenWithCanies{std::accumulate(candies_.begin(), 
        candies_.end(), 0LL, [=](auto const sum_, auto const num_) {
            return sum_ + num_ / candiesPerChild_;
        })};
    return childrenWithCanies >= childrenCount;
}
