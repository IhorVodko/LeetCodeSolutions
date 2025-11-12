// problem : https://leetcode.com/problems/minimum-number-of-operations-to-make-all-array-elements-equal-to-1/
//    description
// submission : https://leetcode.com/problems/minimum-number-of-operations-to-make-all-array-elements-equal-to-1/
//    submissions/1827893622
// solution post : https://leetcode.com/problems/minimum-number-of-operations-to-make-all-array-elements-equal-to-1/
//    solutions/7344054/c-modern-readable-code-beats-100-runtime-fgk4

// import std;

class Solution {
public:
// let 'n' be the number of given numbers
// 'm' - the maximum of given numbers 
// time complexity O(n^2 * log(m))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto minOperations(
        std::span<int const> const nums_
    ) const -> int;
};

auto Solution::minOperations(
    std::span<int const> const nums_
) const -> int {
    namespace vs = std::views;

    auto const numsSz{static_cast<int>(nums_.size())};
    auto onesCnt{0};
    auto gcd{0};
    for(auto const num: nums_) {
        if(num == 1) {
            ++onesCnt;
        }
        gcd = std::gcd(gcd, num);
    }
    if(onesCnt > 0) {
        auto const minOpCnt{numsSz - onesCnt};
        return minOpCnt;
    }
    if(gcd != 1) {
        auto const minOpCnt{-1};
        return minOpCnt;
    }
    auto minLen{numsSz};
    for(auto const idxFirst: vs::iota(0, numsSz)) {
        auto gcd{0};
        for(auto const idxLast: vs::iota(idxFirst, numsSz)) {
            gcd = std::gcd(gcd, nums_[idxLast]);
            if(gcd == 1) {
                minLen = std::min(minLen, idxLast - idxFirst + 1);
                break;
            }
        }
    }
    auto const minOpCnt{minLen + numsSz - 2};
    return minOpCnt;
}
