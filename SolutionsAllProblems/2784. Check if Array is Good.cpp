// problem : https://leetcode.com/problems/check-if-array-is-good/description
// submission : https://leetcode.com/problems/check-if-array-is-good/submissions/2003025645
// solution post : https://leetcode.com/problems/check-if-array-is-good/solutions/8228278/c-modern-readable-code-beats-100-runtime-4cj6

// Approach : Frequency Counting with Pigeonhole Principle
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the length of the array of numbers
// complexity :  O(n)
// complexity : O(n)

// import std;

namespace {

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    auto isGood(std::vector<int> nums_) const -> bool;
};

auto Solution::isGood(std::vector<int> nums_) const -> bool {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto const numsSz{std::ssize(nums_)};
    auto cntPerNum{std::vector<int>(numsSz)};
    
    // Pigeonhole principle verification loop
    for(auto const num: nums_) {
        if( num >= numsSz || 
            (num < numsSz - 1 && cntPerNum[num] > 0) ||
            (num == numsSz - 1 && cntPerNum[num] > 1)
        ) {
            return false;
        }

        ++cntPerNum[num];
    }

    return true;
}
