// problem : https://leetcode.com/problems/smallest-stable-index-i/description/
// submission : https://leetcode.com/problems/smallest-stable-index-i/submissions/2130763775
// solution post : https://leetcode.com/problems/smallest-stable-index-i/solutions/8501814/simplanation-simple-explanation-by-cyber-fdk0

// Approach : Prefix Maximum and Suffix Minimum Tracking
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the count of numbers
// Time :  O(n)
// Space : O(n)

// import std;

// #include <algorithm>
// #include <ios>
// #include <iostream>
// #include <limits>
// #include <numeric>
// #include <ranges>
// #include <vector>

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

constexpr auto kMaxNum{std::numeric_limits<int>::max()};
constexpr auto kMinNum{std::numeric_limits<int>::min()};
constexpr auto kStableIdxNodFound{-1};

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
    static auto firstStableIndex(
        std::vector<int> const & nums_,
        int const k
    ) -> int;
};

auto Solution::firstStableIndex(
    std::vector<int> const & nums_,
    int const scoreUpLim_
) -> int {
    auto const numsTot{nums_.size()};

    // 1. Precompute minimum future values to avoid quadratic lookaheads
    auto minNumSuf{std::vector<int>(numsTot, kMaxNum)};
    std::inclusive_scan(
        nums_.rbegin(), nums_.rend(),
        minNumSuf.rbegin(),
        rs::min
    );

    // 2. Find the first split point satisfying the stability threshold
    for(auto prefMaxNum{kMinNum};
        auto const idx: vs::iota(0uz, numsTot)
    ) {
        prefMaxNum = std::max(prefMaxNum, nums_[idx]);

        if(prefMaxNum - minNumSuf[idx] <= scoreUpLim_) {
            return idx;
        }
    }

    return kStableIdxNodFound;
}
