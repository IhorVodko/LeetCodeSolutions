// problem : https://leetcode.com/problems/find-x-value-of-array-i/description
// submission : https://leetcode.com/problems/find-x-value-of-array-i/submissions/2148717075
// solution post : https://leetcode.com/problems/find-x-value-of-array-i/solutions/8533138/simplanation-simple-explanation-by-cyber-jisl

// Approach : Dynamic State Expansion (Prefix Subarrays)
// Runtime : 5 ms, beats 99.11 %

// Complexity analysis
// let 'N' be the count of numbers
// 'M' - modulo value
// Time :  O(N * M)
// Space : O(M)

// import std;

// #include <algorithm>
// #include <ios>
// #include <iostream>
// #include <ranges>
// #include <tuple>
// #include <utility>
// #include <vector>

// #include <cstddef>

namespace {

using std::size_t;

namespace rs = std::ranges;
namespace vs = std::views;

// Optimize standard I/O stream operations performance.
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
    static auto resultArray(
        std::vector<int> const & nums_,
        int const mod_
    ) -> std::vector<long long>;
};

[[nodiscard]]
auto Solution::resultArray(
    std::vector<int> const & nums_,
    int const mod_
) -> std::vector<long long> {
    auto const mod{static_cast<size_t>(mod_)};

    // 1. Return immediately for modulo 1 since all products map to zero remainder.
    if( auto const numsSz{static_cast<long long>(nums_.size())};
        mod == 1uz
    ) {
        return {(numsSz * (numsSz + 1)) / 2ll}; 
    }

    // 2. Initialize accumulator to store total subarray counts per remainder.
    auto subarrTotCntPerRem{std::vector(mod, 0ll)};

    // State arrays maintaining subarray frequencies ending at current and next index.
    auto currSubarrCntPerRem{std::vector(mod, 0ll)};
    auto nextSubarrCntPerRem{std::vector(mod, 0ll)};

    // 3. Process sequence linearly to build subarray combinations dynamically.
    for(auto const num: nums_) {
        auto const currRem{static_cast<size_t>(num) % mod};

        rs::fill(nextSubarrCntPerRem, 0);

        // 4. Begin a standalone subarray utilizing only the current element.
        ++nextSubarrCntPerRem[currRem];
        ++subarrTotCntPerRem[currRem];

        // 5. Expand existing contiguous segments with the new element multiplier.
        for(auto const [prevRem, prevSubarrCnt] :
                currSubarrCntPerRem |
                vs::enumerate |
                vs::filter([] (auto const remAndCnt) {
                    return std::get<1>(remAndCnt) > 0;
                } )
        ) {
            auto const nextRem{(static_cast<size_t>(prevRem) * currRem) % mod};

            // 6. Accumulate configurations matching the derived product remainder.
            nextSubarrCntPerRem[nextRem] += prevSubarrCnt;
            subarrTotCntPerRem[nextRem] += prevSubarrCnt;
        }

        // 7. Advance the dynamic programming window for the next iteration.
        std::swap(currSubarrCntPerRem, nextSubarrCntPerRem);
    }

    return subarrTotCntPerRem;
}
