// problem : https://leetcode.com/problems/count-commas-in-range-ii/description
// submission : https://leetcode.com/problems/count-commas-in-range-ii/submissions/2136579293
// solution post : https://leetcode.com/problems/count-commas-in-range-ii/solutions/8512302/simplanation-simple-explanation-by-cyber-d66a

// Approach :  Cumulative Positional Counting (Vertical Aggregation)
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the given number
// Time :  O(log(n))
// Space : O(1)

// import std;

// #include <ios>
// #include <iostream>

namespace {

// Threshold multipliers and offsets for interval length calculations
constexpr auto kInclusiveRngOffset{1ll};
constexpr auto kCommaCntMult{1'000ll};
constexpr auto kMinNumWithCommas{1'000ll};

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
    static auto countCommas(long long const num_) -> long long;
};

auto Solution::countCommas(long long const num_) -> long long {
    auto commaCnt{0ll};
    // 1. Set starting boundary for the first comma appearance
    auto thresholdNum{kMinNumWithCommas};

    // 2. Iterate through increasing comma magnitude thresholds
    while(thresholdNum <= num_) {
        // 3. Add quantity of numbers exceeding the current threshold
        commaCnt += num_ - thresholdNum + kInclusiveRngOffset;
        // 4. Shift boundary to the next sequential comma position
        thresholdNum *= kCommaCntMult;
    }

    return commaCnt;
}
