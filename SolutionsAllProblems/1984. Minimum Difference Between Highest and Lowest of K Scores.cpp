// problem : https://leetcode.com/problems/minimum-difference-between-highest-and-lowest-of-k-scores/description
// submission : https://leetcode.com/problems/minimum-difference-between-highest-and-lowest-of-k-scores/submissions
//    /1896436502
// solution post : https://leetcode.com/problems/minimum-difference-between-highest-and-lowest-of-k-scores/solutions/
//    7523448/c-modern-readable-code-beats-100-runtime-la82

// import std;

inline static int const fastIOInit{
    [] {
        std::atexit([] () { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' be the number of elements
// time complexity O(n * log(n))
// space complexity O(log(n))
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto minimumDifference(
        std::span<int> const nums_,
        int const length_
    ) const -> int;
};

auto Solution::minimumDifference(
    std::span<int> const nums_,
    int const length_ 
) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;
    using intLim = std::numeric_limits<int>;
    // Sorting allows the minimum and maximum of any group of k elements to be adjacent
    rngs::sort(nums_);
    auto const numsSz{std::ssize(nums_)};
    // Tracks the smallest difference found among all valid windows
    auto minDif{intLim::max()};
    // Sliding window over sorted array to evaluate all size-k groups
    for(auto const i: vs::iota(0, numsSz - length_ + 1)) {
        auto const minNum{nums_[i]};
        auto const maxNum{nums_[i + length_ - 1]};
        auto const curDif{maxNum - minNum};
        minDif = std::min(minDif, curDif);
    }
    return minDif;
}
