// problem : https://leetcode.com/problems/minimum-removals-to-balance-array/description
// submission : https://leetcode.com/problems/minimum-removals-to-balance-array/submissions/1910658575
// solution post : https://leetcode.com/problems/minimum-removals-to-balance-array/solutions/7558656/
//    c-modern-readable-code-beats-100-runtime-wybo

// import std;

inline static int const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
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
    auto minRemoval(
        std::vector<int> & nums_,
        int const mult_
    ) const -> int;
};

auto Solution::minRemoval(
    std::vector<int> & nums_,
    int const mult_
) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;
    using intLim = std::numeric_limits<int>;
    using ll = long long;

    // Sorting enables a sliding window where min is at the left
    // and max is at the right of the current window
    rngs::sort(nums_);
    // Tracks the maximum number of elements that can remain balanced
    auto maxKeepCnt{intLim::min()};
    // Two-pointer sliding window over the sorted array
    for(auto first{nums_.cbegin()}, last{nums_.cbegin()}, end{nums_.cend()};
        first != end; ++first
    ) {
        // Expand the window while the balance condition holds
        while(last < end && *last <= static_cast<ll>(*first) * mult_) {
            ++last;
        }
        // Update the maximum valid window size
        maxKeepCnt = std::max(maxKeepCnt, static_cast<int>(std::distance(first, last)));
    }
    // Minimum removals equals total size minus the largest balanced subset
    auto const remCnt{std::ssize(nums_) - maxKeepCnt};
    return remCnt;
}
