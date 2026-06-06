// problem : https://leetcode.com/problems/left-and-right-sum-differences
// submission : https://leetcode.com/problems/left-and-right-sum-differences/submissions/2024552354
// solution post : https://leetcode.com/problems/left-and-right-sum-differences/solutions/8317960/
//    c-modern-readable-code-beats-100-runtime-ym8g

// Approach : Running Total (Prefix and Suffix Sums)
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the count of numbers
// complexity :  O(n)
// complexity : O(1) auxiliary

// import std;

class Solution final {
public:
    [[nodiscard]]
    static auto leftRightDifference(std::vector<int> const & nums_) -> std::vector<int>;
};

auto Solution::leftRightDifference(std::vector<int> const & nums_) -> std::vector<int> {
    namespace vs = std::views;
    namespace rs = std::ranges;

    auto rSum{rs::fold_left(nums_, 0, std::plus{})};
    auto lSum{0};

    auto const ComputeAbsDiff{[&] (auto const num_) {
        rSum -= num_;
        auto const diff{std::abs(lSum - rSum)};
        lSum += num_;
        return diff;
    }};

    return
        nums_ |
        vs::transform(ComputeAbsDiff) |
        rs::to<std::vector>();
}

namespace {

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace
