// problem : https://leetcode.com/problems/longest-subsequence-with-non-zero-bitwise-xor/description
// submission : https://leetcode.com/problems/longest-subsequence-with-non-zero-bitwise-xor/submissions/2107869796
// solution post : https://leetcode.com/problems/longest-subsequence-with-non-zero-bitwise-xor/solutions/8462773/
//  simplanation-simple-explanation-by-cyber-7bbd/

// Approach : Total XOR Evaluation Strategy
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the count of numbers
// Time :  O(n)
// Space : O(1)

// import std;

namespace {

namespace rs = std::ranges;
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
    static auto longestSubsequence(std::vector<int> const & nums_) -> int;
};

auto Solution::longestSubsequence(std::vector<int> const & nums_) -> int {
    // 1. Isolate elements that can actively influence the XOR state
    auto nonZeroNums{nums_ | vs::filter([] (auto const num_) { return num_ != 0; })};
    // 2. An array of pure zeros mathematically cannot form a non-zero XOR subsequence
    if(rs::empty(nonZeroNums)) {
        return 0;
    }

    // 3. Determine if the entire array inherently satisfies the non-zero XOR condition
    auto const totXor{rs::fold_left(nonZeroNums, 0, std::bit_xor{})};
    auto numsSz{static_cast<int>(nums_.size())};

    // 4. If XOR balances to zero, dropping any one non-zero element breaks the balance
    return totXor == 0 ? numsSz - 1 : numsSz;
}
