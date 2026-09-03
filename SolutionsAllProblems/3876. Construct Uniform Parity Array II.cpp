// problem : https://leetcode.com/problems/construct-uniform-parity-array-ii/description
// submission : https://leetcode.com/problems/construct-uniform-parity-array-ii/submissions/2129677825
// solution post : https://leetcode.com/problems/construct-uniform-parity-array-ii/solutions/8499632/
//    simplanation-simple-explanation-by-cyber-uj7w

// Approach : Parity Reduction via Minimum Element
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the count of numbers
// Time :  O(n)
// Space : O(1)

// import std;

// #include <algorithm>
// #include <ios>
// #include <iostream>
// #include <limits>
// #include <ranges>
// #include <utility>
// #include <vector>
// #include <cstdint>

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

auto constexpr kMaxNum{std::numeric_limits<int>::max()};

auto constexpr isEven{[] [[nodiscard]] (auto const num_) { return num_ % 2 == 0; }};
auto constexpr isOdd{[] [[nodiscard]] (auto const num_) { return num_ % 2 == 1; }};

// Initializer to configure fast I/O before main() runs
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
    static auto uniformArray(std::vector<int> const & numsIn_) -> bool;
};

auto Solution::uniformArray(std::vector<int> const & numsIn_) -> bool {
    // 1. Find the smallest number to flip parities, and check if all numbers start even
    auto const [minNum, areAllEven]{rs::fold_left(
        numsIn_,
        std::pair{kMaxNum, true},
        [] (auto accum_, auto const num_) {
            auto & [minNum, areAllEven]{accum_};

            areAllEven = areAllEven && isEven(num_);
            minNum = std::min(minNum, num_);

            return accum_;
        }
    )};

    // 2. An odd minimum fixes mixed parities, but an even minimum needs an all-even array
    return isOdd(minNum) ? true : areAllEven;
}
