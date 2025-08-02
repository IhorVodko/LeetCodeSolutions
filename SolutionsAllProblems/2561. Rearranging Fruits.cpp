// problem : https://leetcode.com/problems/rearranging-fruits/description
// submission : https://leetcode.com/problems/rearranging-fruits/submissions/1720832136
// solution post : https://leetcode.com/problems/rearranging-fruits/solutions/7036484/
//    c-modern-readable-code-optimal-time-comp-yviz

// #include <algorithm>
// #include <limits>
// #include <ranges>
// #include <vector>

class Solution {
public:
// let 'n' be a length of each of the given fruits baskets 
// time complexity O(n)
// space complexity O(n)
// runtime 30 ms, beats 92.41 %
    [[nodiscard]]
    long long minCost(
        std::vector<int> & costs1_,
        std::vector<int> & costs2_
    ) const;
};

long long Solution::minCost(
    std::vector<int> & costs1_,
    std::vector<int> & costs2_
) const {
    namespace ranges = std::ranges;
    namespace views = std::views;
    using intT = std::numeric_limits<int>;
    auto minCost{intT::max()};
    auto costToCount{std::unordered_map<int, int>{}};
    for(auto const b1: costs1_) {
        ++costToCount[b1];
        minCost = std::min(minCost, b1);
    }
    for(auto const b2: costs2_) {
        --costToCount[b2];
        minCost = std::min(minCost, b2);
    }
    auto allCosts{std::vector<int>{}};
    for(auto const [cost, count]: costToCount) {
        if(count % 2 == 1) {
            return -1;
        }
        auto const halfCount{std::abs(count) / 2};
        allCosts.insert(allCosts.end(), halfCount, cost);
    }
    auto const middlePos{allCosts.size() / 2};
    ranges::nth_element(allCosts, allCosts.begin() + middlePos);
    auto minCostToRearrange{0ll};
    minCost *= 2;
    for(auto const currCost: allCosts | views::take(middlePos)) {
        minCostToRearrange += std::min(minCost, currCost);
    }
    return minCostToRearrange;
}
