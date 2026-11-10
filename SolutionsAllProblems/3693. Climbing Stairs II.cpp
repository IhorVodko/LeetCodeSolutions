// problem : https://leetcode.com/problems/climbing-stairs-ii/description/
// submission : https://leetcode.com/problems/climbing-stairs-ii/submissions/2193329283
// solution post : https://leetcode.com/problems/climbing-stairs-ii/solutions/8608216/simplanation-simple-explanation-by-cyber-tq5b

// Approach : Dynamic Programming with State Space Reduction
// Runtime : 17 ms, beats 65.27 %

// Complexity analysis
// let 'n' be the number of stairs
// Time :  O(n)
// Space : O(1)

// import std;

// #include <algorithm>
// #include <ios>
// #include <iostream>
// #include <ranges>
// #include <vector>

namespace rs = std::ranges;
namespace vs = std::views;

namespace {

// Fixed penalties for leaping one, two, or three stairs respectively.
constexpr auto kSingleJumpCost{1};
constexpr auto kDoubleJumpCost{4};
constexpr auto kTripleJumpCost{9};

// Tracks the minimal accumulated costs for the three most recent stairs.
struct AccumCosts final {
    int cost1{};
    int cost2{};
    int cost3{};
};

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
    static auto climbStairs(
        int const stairsTot_,
        std::vector<int> const & stepCosts_
    ) -> int;
};

auto Solution::climbStairs(
    int const stairsTot_,
    std::vector<int> const & stepCosts_
) -> int {
    // 1. Generate a lazily evaluated sequence of all stairs to be evaluated.
    auto stairs{vs::iota(0, stairsTot_)};
    // 2. Define the state transition to compute the cheapest path to a given stair.
    const auto processJump{[&stepCosts_] (auto const accumCosts_, auto const step_) {
        auto const [cost1, cost2, cost3]{accumCosts_};
        // 3. Find the optimal previous stair to jump from by comparing penalties.
        auto const nextCost{rs::min({
            cost1 + kTripleJumpCost,
            cost2 + kDoubleJumpCost,
            cost3 + kSingleJumpCost
        }) + stepCosts_[step_]};

        // 4. Shift the sliding window forward to include the newly reached stair.
        return AccumCosts{cost2, cost3, nextCost};
    }};

    // 5. Traverse all stairs, continuously updating the window of minimum costs.
    const auto accumCosts{rs::fold_left(stairs, AccumCosts{}, processJump)};

    // 6. Extract the overall minimum cost required to conquer the final stair.
    return accumCosts.cost3;
}
