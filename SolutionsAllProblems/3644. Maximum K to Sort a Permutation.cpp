// problem : https://leetcode.com/problems/maximum-k-to-sort-a-permutation/description
// submission : https://leetcode.com/problems/maximum-k-to-sort-a-permutation/submissions/2179733055
// solution post : https://leetcode.com/problems/maximum-k-to-sort-a-permutation/solutions/8585325/
//    simplanation-simple-explanation-by-cyber-bznp

// Approach : Bitwise Constraint Aggregation
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the total number of elements in the input array
// Time :  O(n)
// Space : O(1)

// import std;

// #include <algorithm>
// #include <functional>
// #include <ios>
// #include <iostream>
// #include <limits>
// #include <ranges>
// #include <utility>
// #include <vector>

namespace vs = std::views;
namespace rs = std::ranges;

namespace {

// Represent the identity value for bitwise AND operations.
auto constexpr kMaxNum{std::numeric_limits<unsigned>::max()}; 

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
    static auto sortPermutation(std::vector<int> const & nums_) -> int;
};

auto Solution::sortPermutation(std::vector<int> const & nums_) -> int {
    // 1. Isolate permutation elements that are out of their sorted target positions.
    auto misplacedNums_{
        nums_ |
        vs::enumerate |
        vs::filter([] (auto const idxAndNum_) static {
            auto const [idx, num]{idxAndNum_};
            // Identify elements requiring swaps to reach their sorted destination.
            return std::cmp_not_equal(idx, num);
        }) |
        vs::elements<1> |
        vs::transform([] (auto const num_) static {
            // Prevent signed extension issues during bitwise operations.
            return static_cast<unsigned>(num_);
        })
    };

    // 2. Calculate the maximum k by taking the bitwise AND of out-of-place elements.
    auto const maxAnd{rs::fold_left(
        misplacedNums_,
        kMaxNum,
        std::bit_and{}
    )};

    // 3. Return 0 if the permutation is already sorted, otherwise return the computed k.
    return maxAnd == kMaxNum ? 0 : static_cast<int>(maxAnd);
}
