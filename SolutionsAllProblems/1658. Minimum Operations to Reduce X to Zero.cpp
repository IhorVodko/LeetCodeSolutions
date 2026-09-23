// problem : https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/description
// submission : https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/submissions/2150841108
// solution post : https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/solutions/8536208/
//  simplanation-simple-explanation-by-cyber-p6qq

// Approach : Two-Pointer Prefix-Suffix Sum
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
// #include <iterator>
// #include <optional>
// #include <ranges>
// #include <vector>

// #include <cstddef>

namespace {
    
namespace rs = std::ranges;
namespace vs = std::views;

// Map difference types for pointer arithmetic.
using std::ptrdiff_t;

// Define a constant for unmatched target scenarios.
constexpr auto kNotFound{-1z};

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
    static auto minOperations(
        std::vector<int> const & nums_,
        int const targetSum_
    ) -> int;
};

auto Solution::minOperations(
    std::vector<int> const & nums_,
    int const targetSum_
) -> int {
    auto const numTot{std::ssize(nums_)};
    
    // 1. Initialize the running sum to the total array sum.
    auto currSum_{rs::fold_left(nums_, 0, std::plus{})};
    auto minOpCnt{std::optional<ptrdiff_t>{}};

    for(auto lIdx{0z};
        auto const [rIdx, num]: nums_ | vs::enumerate
    ) {
        // 2. Shrink the right side of the suffix to reduce the sum.
        currSum_ -= num;

        // 3. Expand the prefix from the left if the sum falls below the target.
        while(currSum_ < targetSum_ && lIdx <= rIdx) {
            currSum_ += nums_[lIdx];
            ++lIdx;
        }

        // 4. Update the minimum operations when the exact target sum is achieved.
        if(currSum_ == targetSum_) {
            auto const currOpCnt{numTot - rIdx - 1z + lIdx};

            minOpCnt = std::min(minOpCnt.value_or(currOpCnt), currOpCnt);
        }
    }

    // 5. Cast the optional result or return the not-found sentinel.
    return static_cast<int>(minOpCnt.value_or(kNotFound));
}
