// problem : https://leetcode.com/problems/minimum-moves-to-equal-array-elements-iii/description
// submission : https://leetcode.com/problems/minimum-moves-to-equal-array-elements-iii/submissions/2188675381
// solution post : https://leetcode.com/problems/minimum-moves-to-equal-array-elements-iii/solutions/8600533/
//    simplanation-simple-explanation-by-cyber-oehw

// Approach : Target Alignment Strategy - Anchor and Elevate
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the count of numbers
// Time :  O(n)
// Space : O(1)

// import std;

// #include <algorithm>
// #include <ios>
// #include <iostream>
// #include <functional>
// #include <ranges>
// #include <vector>

namespace rs = std::ranges;
namespace vs = std::views;

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
    static auto minMoves(std::vector<int> const & nums_) -> int;
};

auto Solution::minMoves(std::vector<int> const & nums_) -> int {
    // 1. Identify the target baseline that all elements must uniformly reach
    auto const maxNum{rs::max(nums_)};
    // Define the exact adjustment distance required for a single value
    auto const cntMove{[maxNum] (auto const num_) { return maxNum - num_; }};
    // 2. Map current states into a lazy sequence of individual adjustments
    auto moves{nums_ | vs::transform(cntMove)};
    // 3. Accumulate all individual adjustments to determine global cost
    auto const totMoves{rs::fold_left(moves, 0, std::plus{})};

    return totMoves;
}
