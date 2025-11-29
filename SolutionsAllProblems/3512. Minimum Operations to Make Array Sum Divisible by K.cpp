// problem : https://leetcode.com/problems/minimum-operations-to-make-array-sum-divisible-by-k/description
// submission : https://leetcode.com/problems/minimum-operations-to-make-array-sum-divisible-by-k/submissions/1842520223
// solution post : https://leetcode.com/problems/minimum-operations-to-make-array-sum-divisible-by-k/solutions/7381514/
//    c-modern-readable-code-beats-100-runtime-vnja

// import std;

class Solution {
public:
// let 'n' be the number of given numbers
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto minOperations(
        std::span<int const> const & nums_,
        int const divisor_
    ) const -> int;
};

auto Solution::minOperations(
    std::span<int const> const & nums_,
    int const divisor_
) const -> int {
    namespace rngs = std::ranges;

    auto const sum{rngs::fold_left(nums_, 0, std::plus{})};
    auto const minOpCnt{sum % divisor_};
    return minOpCnt;
}
