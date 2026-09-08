// problem : https://leetcode.com/problems/count-commas-in-range/description
// submission : https://leetcode.com/problems/count-commas-in-range/submissions/2135075164
// solution post : https://leetcode.com/problems/count-commas-in-range/solutions/8509599/simplanation-simple-explanation-by-cyber-26s1

// Approach : O(1) Boundary Thresholding
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// Time :  O(1)
// Space : O(1)

// import std;

namespace {

// Threshold up to which string representation lacks thousand separators.
constexpr auto kMaxNumberWithoutComma{999};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    static auto countCommas(int const num_) -> int;
};

auto Solution::countCommas(int const num_) -> int {
    // 1. Calculate the count of numbers that require at least one comma.
    // 2. Prevent negative counts for small bounds.
    return std::max(num_ - kMaxNumberWithoutComma, 0);
}
