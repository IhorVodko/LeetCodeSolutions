// problem : https://leetcode.com/problems/smallest-index-with-digit-sum-equal-to-index/description/
// submission : https://leetcode.com/problems/smallest-index-with-digit-sum-equal-to-index/submissions/2152022997
// solution post : https://leetcode.com/problems/smallest-index-with-digit-sum-equal-to-index/solutions/8538040/
//  simplanation-simple-explanation-by-cyber-6bf3

// Approach : Linear Sequential Search with Digit Mapping
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the count of numbers
// 'm' - the maximum number given 
// Time :  O(n * log(m))
// Space : O(1)

// import std;

// #include <algorithm>
// #include <ios>
// #include <iostream>
// #include <ranges>
// #include <tuple>
// #include <vector>

// #include <cstdlib>

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

constexpr auto kNoSolution{-1};
constexpr auto kRadix{10};

constexpr auto calcDigitSum{[] [[nodiscard]] (int num_) {
    auto sum{0};

    while(num_ > 0) {
        // Extract lowest base-10 digit to accumulate total numeric value sum.
        auto const res{std::div(num_, kRadix)};

        sum += res.rem;
        num_ = res.quot; 
    }

    return sum;
}};

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
    static auto smallestIndex(std::vector<int> const & nums_) -> int;
};

auto Solution::smallestIndex(std::vector<int> const & nums_) -> int {
    // 1. Map sequence values to their zero-based positions for simultaneous evaluation.
    auto searchSpace{nums_ | vs::enumerate};
    // 2. Scan linearly to find the earliest occurrence where position equals digit sum.
    auto const foundIdxAndNumIt{rs::find_if(
        searchSpace,
        [] (auto const idxAndNum_) { 
            auto const [idx, num]{idxAndNum_};

            return idx == calcDigitSum(num);
        }
    )};

    // 3. Resolve the underlying index if found, or yield the designated missing state.
    return foundIdxAndNumIt == searchSpace.end() ?
        kNoSolution :
        static_cast<int>(std::get<0>(*foundIdxAndNumIt))
    ;
}
