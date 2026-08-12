// problem : https://leetcode.com/problems/length-of-longest-subarray-with-at-most-k-frequency/description
// submission : https://leetcode.com/problems/length-of-longest-subarray-with-at-most-k-frequency/submissions/2104293948
// solution post : https://leetcode.com/problems/length-of-longest-subarray-with-at-most-k-frequency/solutions/8457024/
//    simplanation-simple-explanation-by-cyber-ykyp

// Approach : Optimized Sliding Window (Non-Shrinking Window)
// Runtime : 36 ms, beats 99.89 %

// Complexity analysis
// let 'n' be the count of numbers
// Time :  O(n)
// Space : O(n)

// import std;

namespace {

namespace vs = std::views;

// Initializer to configure fast I/O before main() runs
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
    static auto maxSubarrayLength(
        std::vector<int> const & nums_,
        int const freqUpLim_
    ) -> int;
};

auto Solution::maxSubarrayLength(
    std::vector<int> const & nums_,
    int const freqUpLim_
) -> int {
    // 1. Initialize frequency map and window tracking variables
    auto numToFreq{std::unordered_map<int, int>{}};
    auto startIdx{0};
    // Tracks count of distinct elements exceeding the frequency limit
    auto freqViolationsCnt{0};

    // 2. Expand the right boundary of the window
    for(auto const num: nums_) {
        // 3. Update frequency and check for limit violations
        if(++numToFreq[num] == freqUpLim_ + 1) {
            ++freqViolationsCnt;           
        }

        // 4. Grow the maximum valid window size
        if(freqViolationsCnt == 0) {
            continue;
        } 
        
        // 5. Slide window by moving left boundary to maintain max size
        if(--numToFreq[nums_[startIdx]] == freqUpLim_) {
            --freqViolationsCnt;
        }

        ++startIdx;
    }

    // 6. Calculate the final maximum subarray length
    return static_cast<int>(nums_.size()) - startIdx;
}
