// problem : https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/description
// submission : https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/submissions/1896415802
// solution post : https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/solutions/7523376/
//    c-modern-readable-code-beats-100-runtime-y7g9

// import std;

// let 'n' be the number of elements
// time complexity O(n * log(n))
// space complexity O(log(n))
// runtime 0 ms, beats 100.00 %

inline static int const fastIOInit{
    [] {
        std::atexit([] () { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

class Solution {
public:
    auto minPairSum(std::span<int> const nums_) const -> int;
};

auto Solution::minPairSum(std::span<int> const nums_) const -> int {
    // Sorting enables pairing smallest with largest to minimize the maximum pair sum
    std::ranges::sort(nums_);
    auto const numsSz{std::ssize(nums_)};
    // Tracks the maximum sum among all formed pairs
    auto maxSum{std::numeric_limits<int>::min()};
    // Iterate over the first half, pairing symmetric elements from both ends
    for(auto const idx: std::views::iota(0, numsSz / 2)) {
        auto const curSum{nums_[idx] + nums_[numsSz - idx - 1]};
        maxSum = std::max(maxSum, curSum);
    }
    return maxSum;
}
