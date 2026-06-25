// problem : https://leetcode.com/problems/count-subarrays-with-majority-element-i/description/
// submission : https://leetcode.com/problems/count-subarrays-with-majority-element-i/submissions/2045877430
// solution post : https://leetcode.com/problems/count-subarrays-with-majority-element-i/solutions/8358033/
//    c-modern-readable-code-beats-100-runtime-7zu9

// Approach : Prefix Balance Transformation with On-the-Fly Cumulative Frequencies
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the count of numbers
// Time :  O(n)
// Space : O(n)

// import std;

class Solution final {
public:
    [[nodiscard]]
    static auto countMajoritySubarrays(
        std::vector<int> const & nums_,
        int const targetNum_
    ) -> int;
};

auto Solution::countMajoritySubarrays(
    std::vector<int> const & nums_,
    int const targetNum_
) -> int
{
    auto const numsSz{std::ssize(nums_)};
    auto subarrCnt{0};
    // Shift index to safely handle negative balances in a flat array
    auto const zeroBalanceOffset{numsSz + 1};
    auto currBalance{zeroBalanceOffset};

    // Store the occurrence count for each possible prefix balance
    auto balanceFreqs{std::vector<int>(zeroBalanceOffset * 2)};
    balanceFreqs[currBalance] = 1;

    // Track prefix sums of frequencies to query strictly smaller balances
    auto cumulativeFreqs{std::vector<int>(zeroBalanceOffset * 2)};
    cumulativeFreqs[currBalance] = 1;

    for(auto const num: nums_) {
        currBalance += (num == targetNum_ ? 1 : -1);
        ++balanceFreqs[currBalance];
        cumulativeFreqs[currBalance] =
            cumulativeFreqs[currBalance - 1] + balanceFreqs[currBalance];
        // Valid subarray if previous balance was strictly lower than current
        subarrCnt += cumulativeFreqs[currBalance - 1];
    }

    return subarrCnt;
}

namespace {

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace
