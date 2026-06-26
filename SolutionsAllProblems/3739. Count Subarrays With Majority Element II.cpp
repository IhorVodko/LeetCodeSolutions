// problem : https://leetcode.com/problems/count-subarrays-with-majority-element-ii/description/
// submission : https://leetcode.com/problems/count-subarrays-with-majority-element-ii/submissions/2046735422
// solution post : https://leetcode.com/problems/count-subarrays-with-majority-element-ii/solutions/8359459/
//    modern-readable-code-optimal-time-comple-aym0

// Approach : Running Balance and Prefix Frequency Tracking
// Runtime : 3 ms, beats 96.69 %

// Complexity
// let 'n' be the count of numbers
// Time :  O(n)
// Space : O(n)

// import std;

class Solution final {
public:
    using ll = long long;

    [[nodiscard]]
    static auto countMajoritySubarrays(
        std::vector<int> const & nums_,
        int const targetNum_
    ) -> ll;
};

auto Solution::countMajoritySubarrays(
    std::vector<int> const & nums_,
    int const targetNum_
) -> ll {
    // Shift zero balance to prevent negative indices
    auto const zeroBalanceOffset{nums_.size() + 1};
    auto currBalance{zeroBalanceOffset};

    // Store the occurrence count for each possible prefix balance
    auto balanceFreqs{std::vector<ll>(zeroBalanceOffset * 2)};
    balanceFreqs[currBalance] = 1;

    auto subarrCnt{0ll};
    // Running sum of prefix frequencies where past balance < currBalance
    auto cumFreqSum{0ll};

    for(auto const num: nums_) {
        // Target seen: balance grows, adding old balance to valid prefix pool
        if(num == targetNum_) {
            cumFreqSum += balanceFreqs[currBalance++];
        // Non-target seen: balance drops, removing new balance from valid prefix pool
        } else {
            cumFreqSum -= balanceFreqs[--currBalance];
        }

        // Record new balance state and accumulate valid subarrays ending here
        ++balanceFreqs[currBalance];
        subarrCnt += cumFreqSum;
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
