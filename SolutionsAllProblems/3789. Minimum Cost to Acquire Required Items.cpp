// problem : https://leetcode.com/problems/minimum-cost-to-acquire-required-items/description
// submission : https://leetcode.com/problems/minimum-cost-to-acquire-required-items/submissions/2194012803
// solution post : https://leetcode.com/problems/minimum-cost-to-acquire-required-items/solutions/8609433/
//    simplanation-simple-explanation-by-cyber-jxe8

// Approach : Piecewise Linear Boundary Evaluation
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// Time :  O(1)
// Space : O(1)

// import std;

// #include <algorithm>
// #include <initializer_list>
// #include <ios>
// #include <iostream>

namespace rs = std::ranges;

namespace {

// Optimize standard I/O stream operations performance.
[[maybe_unused]]
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace 

class Solution final {
public:
    [[nodiscard]]
    static auto minimumCost(
        const int cost1_,
        const int cost2_,
        const int cost1And2_,
        const int reqQty1_,
        const int reqQty2_
    ) -> long long;  
};

auto Solution::minimumCost(
    const int cost1_,
    const int cost2_,
    const int cost1And2_,
    const int reqQty1_,
    const int reqQty2_
) -> long long {
    // 1. Promote quantities to 64-bit integers to prevent overflow during scaling.
    const auto reqQty1{static_cast<long long>(reqQty1_)};
    const auto reqQty2{static_cast<long long>(reqQty2_)};

    // 2. Return the minimal cost from the four boundary evaluations.
    // Extreme vertices represent optimal buying strategies in piecewise logic.
    return rs::min({
        // Scenario: Bundle price is higher than buying both items separately.
        cost1_ * reqQty1 + cost2_ * reqQty2,
        // Scenario: Bundle price is so low that discarding surplus items is optimal.
        cost1And2_ * (std::max(reqQty1, reqQty2)),
        // Scenario: Bundles save money, but Item 2 alone is cheaper than excess bundles.
        cost1And2_ * reqQty1 + cost2_ * std::max(reqQty2 - reqQty1, 0ll),
        // Scenario: Bundles save money, but Item 1 alone is cheaper than excess bundles.
        cost1_ * std::max(reqQty1 - reqQty2, 0ll) + cost1And2_ * reqQty2
    });
}
