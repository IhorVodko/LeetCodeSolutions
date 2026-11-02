// problem : https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/description
// submission : https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/submissions/2187931733
// solution post : https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/solutions/8599217/
//    simplanation-simple-explanation-by-cyber-vf8d

// Approach : Median Element Selection
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the count of numbers 
// Time :  O(n)
// Space : O(1)

// import std;

// #include <algorithm>
// #include <functional>
// #include <ios>
// #include <iostream>
// #include <ranges>
// #include <vector>
// #include <cmath>

namespace vs = std::views;
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
    static auto minMoves2(std::vector<int> & nums_) -> int;
};

auto Solution::minMoves2(std::vector<int> & nums_) -> int {
    // 1. Target median which minimizes sum of absolute deviations.
    auto const midIt{nums_.begin() + nums_.size() / 2};

    // 2. Partition array to place median at correct sorted index.
    rs::nth_element(nums_, midIt);

    // 3. Accumulate total moves required to equal the median.
    return rs::fold_left(
        nums_ | vs::transform([midIt] (auto const num_) { 
            return std::abs(*midIt - num_);
        }),
        0,
        std::plus{}
    );
}
