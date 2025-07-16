// problem : https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-i/description
// submission : https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-i/submissions/1699825434
// solution post : https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-i/solutions/6965810/
//    c-modern-readable-code-optimal-time-comp-gc6g

// #include <algorithm>
// #include <array>
// #include <ranges>
// #include <vector>

namespace Util {
    inline auto constexpr kPatterns{std::array<std::array<int, 2>, 4>{{
        {0, 0}, {0, 1}, {1, 0}, {1, 1}}}};
}

class Solution {
public:
// let 'n' be a count of the given numbers
// time complexity O(n)
// space complexity O(1)
// runtime 16 ms, beats 22.35 %
    [[nodiscard]]
    int maximumLength(std::vector<int> const & nums_) const;
};

int Solution::maximumLength(std::vector<int> const & nums_) const {
    namespace views = std::views;
    namespace ranges = std::ranges;
    using namespace Util;
    auto const countSubseqSz{[&] (auto & pattern_) {
        auto subseqSz{0};
        for(auto num: nums_) {
            if(num % 2 == pattern_.at(subseqSz % 2)) {
                ++subseqSz;
            }
        }
        return subseqSz;
    }};
    auto maxSubseqSz{ranges::max(kPatterns | views::transform(countSubseqSz))};
    return maxSubseqSz;
}
