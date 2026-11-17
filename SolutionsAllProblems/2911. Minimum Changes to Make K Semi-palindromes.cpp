// problem : leetcode.com/problems/minimum-changes-to-make-k-semi-palindromes/description/
// submission : https://leetcode.com/problems/minimum-changes-to-make-k-semi-palindromes/submissions/2198240552
// solution post : https://leetcode.com/problems/minimum-changes-to-make-k-semi-palindromes/solutions/8616223/
//  simplanation-simple-explanation-by-cyber-8dew

// Approach : Precomputation & Dynamic Programming
// Runtime : 97 ms, beats 90.77 %

// Complexity analysis
// let 'n' be the string length
// 'm' - required target number of semi-palindrome partitions
// Time :  O(n^2 * log(n) + n^2 * m)
// Space : O(n^2 + n * m)

// import std;

// #include <algorithm>
// #include <ios>
// #include <iostream>
// #include <limits>
// #include <ranges>
// #include <string_view>
// #include <vector>

namespace rs = std::ranges;
namespace vs = std::views;

namespace {

constexpr auto kInf{std::numeric_limits<int>::max() / 2};
constexpr auto kMinSubstrLen{2};
constexpr auto kMinDiv{1};
constexpr auto kMinFactor{2};

// Flatten 2D matrix coordinates into a contiguous 1D array index for cache efficiency.
constexpr auto to1dIdx{[] [[nodiscard]] (
    const int rowIdx_,
    const int colIdx_,
    const int maxDim_
) noexcept {
    return rowIdx_ * maxDim_ + colIdx_;
}};

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
    // Calculate minimum character changes to form totSubstrs_ valid semi-palindromes.
    [[nodiscard]]
    static auto minimumChanges(
        const std::string_view str_,
        const int totSubstrs_
    ) -> int;

private:
    // Precompute the minimal modification cost for every possible substring.
    [[nodiscard]]
    static auto createCostPerSubstr(
        const std::string_view str_,
        const int strLen_,
        const int maxDim_
    ) -> std::vector<int>;

    // Generate DP table to find optimal segment boundaries minimizing total cost.
    [[nodiscard]]
    static auto createSubstrCostDp(
        int const strLen_,
        int const totSubstrs_,
        int const maxDim_,
        std::vector<int> const& costPerSubstr_
    ) -> std::vector<int>;
};

auto Solution::minimumChanges(
    const std::string_view str_,
    const int totSubstrs_
) -> int {
    const auto strLen{static_cast<int>(str_.length())};
    const auto maxDim{strLen + 1};
    // 1. Precompute minimum changes required to make every valid substring a semi-palindrome.
    const auto costPerSubstr{createCostPerSubstr(str_, strLen, maxDim)};
    // 2. Compute minimum total changes using DP over the number of partitions.
    const auto substrCostDp{
        createSubstrCostDp(strLen, totSubstrs_, maxDim, costPerSubstr)};

    return substrCostDp[to1dIdx(totSubstrs_, strLen, maxDim)];
}

auto Solution::createCostPerSubstr(
    const std::string_view str_,
    const int strLen_,
    const int maxDim_
) -> std::vector<int> {
    auto costPerSubstr{std::vector<int>(maxDim_ * maxDim_, kInf)};
    auto costPerDiv{std::vector<int>(maxDim_ * maxDim_)};
    const auto maxDiv{strLen_ / kMinFactor};

    // 1. Iterate over all possible divisors representing the period.
    for(const auto div: vs::iota(kMinDiv, maxDiv + 1)) {
        rs::fill(costPerDiv, 0);

        const auto substrMinLen{kMinFactor * div};

        // 2. Evaluate valid substring lengths that are multiples of the current divisor.
        for(const auto substrLen: 
                vs::iota(substrMinLen, strLen_ + 1) | vs::stride(div)
        ) {
            const auto maxSubstrStartIdx{strLen_ - substrLen};

            for(const auto startIndex: vs::iota(0, maxSubstrStartIdx + 1)) {
                // Calculate mismatch cost between corresponding characters in the period.
                const auto isChangeNeeded{[&str_, startIndex, substrLen, div] (
                    const auto chrOffsetIdx_
                ) {
                    const auto leftChrIdx{startIndex + chrOffsetIdx_};
                    const auto rightChrIdx{
                        startIndex + substrLen - div + chrOffsetIdx_};

                    return str_[leftChrIdx] != str_[rightChrIdx];
                }};

                // 3. Accumulate cost using a sliding window approach for the divisor.
                const auto outerCost{
                    rs::count_if(vs::iota(0, div), isChangeNeeded)};

                const auto innerLength{substrLen - kMinFactor * div};
                const auto innerStartIndex{startIndex + div};
                const auto innerCost{
                    costPerDiv[to1dIdx(innerStartIndex, innerLength, maxDim_)]};
                    
                const auto totalCost{static_cast<int>(outerCost) + innerCost};

                costPerDiv[to1dIdx(startIndex, substrLen, maxDim_)] = totalCost;

                auto & minCost{costPerSubstr[to1dIdx(startIndex, substrLen, maxDim_)]};

                // 4. Update the global minimum cost for the specific substring.
                minCost = rs::min(minCost, totalCost);
            }
        }
    }

    return costPerSubstr;
}

auto Solution::createSubstrCostDp(
    const int strLen_,
    const int totSubstrs_,
    const int maxDim_,
    const std::vector<int> & costPerSubstr_
) -> std::vector<int> {
    auto substrCostDp{std::vector<int>((totSubstrs_ + 1) * maxDim_, kInf)};

    // Base case: zero cost for zero substrings and zero length.
    substrCostDp[to1dIdx(0, 0, maxDim_)] = 0;

    // 1. Iterate through all possible partition counts.
    for(auto const substrCntIdx: vs::iota(1, totSubstrs_ + 1)) {
        const auto minSubstrEndIdx{substrCntIdx * kMinSubstrLen};

        // 2. Evaluate all valid ending indices for the current partition count.
        for(const auto substrEndIdx: vs::iota(minSubstrEndIdx, strLen_ + 1)) {
            const auto calcTransitionCost{
                [&substrCostDp, &costPerSubstr_, maxDim_, substrCntIdx, substrEndIdx] (
                    const auto substrStartIdx_ 
                ) {
                    const auto prevCost{
                        substrCostDp[to1dIdx(
                            substrCntIdx - 1, substrStartIdx_, maxDim_)]
                    };

                    // Skip invalid transitions where the previous state is unreachable.
                    if (prevCost == kInf) {
                        return kInf;
                    }

                    const auto substrLen{substrEndIdx - substrStartIdx_};
                    const auto newCost{
                        costPerSubstr_[to1dIdx(substrStartIdx_, substrLen, maxDim_)]};

                    return prevCost + newCost;
                }
            };

            const auto minSubstrStartIdx{(substrCntIdx - 1) * kMinSubstrLen};
            const auto maxSubstrStartIdx{substrEndIdx - kMinSubstrLen};

            // 3. Find optimal starting index minimizing total cost for the partition.
            substrCostDp[to1dIdx(substrCntIdx, substrEndIdx, maxDim_)] = rs::min(
                vs::iota(minSubstrStartIdx, maxSubstrStartIdx + 1) |
                vs::transform(calcTransitionCost)
            );
        }
    }

    return substrCostDp;
}
