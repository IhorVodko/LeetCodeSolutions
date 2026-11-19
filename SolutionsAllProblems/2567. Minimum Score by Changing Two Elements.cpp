// problem : https://leetcode.com/problems/minimum-score-by-changing-two-elements/description
// submission : https://leetcode.com/problems/minimum-score-by-changing-two-elements/submissions/2199436229
// solution post : https://leetcode.com/problems/minimum-score-by-changing-two-elements/solutions/8618181/
//  simplanation-simple-explanation-by-cyber-pjub

// Approach : Greedy Extreme Selection via Partial Sorting
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the count of numbers
// Time :  O(n)
// Space : O(1)

// import std;

// #include <algorithm>
// #include <array>
// #include <functional>
// #include <ios>
// #include <iostream>
// #include <ranges>
// #include <vector>

namespace rs = std::ranges;
namespace vs = std::views;

namespace {

// Only the 3 smallest and 3 largest values can become the new bounds.
auto constexpr kExtremeNumsTot{3uz};

// Optimize standard I/O stream operations performance.
[[maybe_unused]]
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespae 

class Solution final {
public:
    [[nodiscard]]
    static auto minimizeSum(std::vector<int> const & nums_) -> int;
};

auto Solution::minimizeSum(std::vector<int> const & nums_) -> int {
    // With 3 numbers, changing two to match the third gives a score of 0.
    if(nums_.size() == kExtremeNumsTot) {
        return 0;
    }

    // 1. Find the 3 smallest values as possible new minimums.
    auto minNums{std::array<int, kExtremeNumsTot>{}};
    rs::partial_sort_copy(nums_, minNums); 

    // 2. Find the 3 largest values as possible new maximums.
    auto maxNums{std::array<int, kExtremeNumsTot>{}};
    rs::partial_sort_copy(nums_, maxNums, std::greater{});

    // 3. Find the remaining range for each of the 3 ways to drop 2 extremes.
    auto candidateScores{vs::zip_transform(std::minus{}, maxNums | vs::reverse, minNums)};

    // 4. The low score can always be 0, so the smallest range (the high score) wins.
    return rs::min(candidateScores);
}
