// problem : https://leetcode.com/problems/min-cost-climbing-stairs/description/
// submission : https://leetcode.com/problems/min-cost-climbing-stairs/submissions/1775035568
// solution post : https://leetcode.com/problems/min-cost-climbing-stairs/solutions/7202555/
//    c-modern-readable-code-beats-100-runtime-0y3c

// import std;

class Solution {
public:
// let 'n' be a staircase length
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto minCostClimbingStairs(std::vector<int> const & costs_) const -> int;
};

auto Solution::minCostClimbingStairs(
    std::vector<int> const & costs_
) const -> int {
    namespace views = std::views;
    auto const costsCnt{std::ssize(costs_)};
    auto prevPaidCost{costs_.at(0)};
    auto currPaidCost{costs_.at(1)};
    for(auto const cost: costs_ | views::drop(2)) {
        auto const nextPaidCost{std::min(prevPaidCost, currPaidCost) + cost};
        prevPaidCost = currPaidCost;
        currPaidCost = nextPaidCost;
    }
    auto const minPaidCost{std::min(prevPaidCost, currPaidCost)};
    return  minPaidCost;
}
