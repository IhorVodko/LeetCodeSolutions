// problem : https://leetcode.com/problems/maximum-number-of-jumps-to-reach-the-last-index/description/
// submission : https://leetcode.com/problems/maximum-number-of-jumps-to-reach-the-last-index/submissions/2000540105
// solution post : https://leetcode.com/problems/maximum-number-of-jumps-to-reach-the-last-index/solutions/8193080/
//    c-modern-readable-code-beats-100-runtime-vsob

// Approach : Bottom-Up Iterative 1D Dynamic Programming
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the length of the array of numbers
// complexity :  O(n^2)
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
    using numsT = std::vector<int>;

    [[nodiscard]]
    auto maximumJumps(
        numsT const & nums_,
        int const upLim_
    ) const -> int;

private:
    static auto constexpr kUnreachable{std::numeric_limits<int>::min()};
};

auto Solution::maximumJumps(
    numsT const & nums_,
    int const upLim_
) const -> int {
    namespace vs = std::views;

    auto const numsSz{std::ssize(nums_)};

    auto maxJmpsDp{std::vector<int>(numsSz, kUnreachable)};
    // Base case: zero jumps required for the first index
    maxJmpsDp[0] = 0;

    for(auto const currI: vs::iota(0, numsSz)) {
        auto currMaxJmp{maxJmpsDp[currI]};
        // Skip if this index has not been reached
        if(currMaxJmp == kUnreachable) {
            continue;
        }

        auto const currNum{nums_[currI]};
        // Iterate through subsequent indices to find valid jump targets
        for(auto const jmpI: vs::iota(currI + 1, numsSz)) {
            if(std::abs(nums_[jmpI] - currNum) <= upLim_) {
                auto & nextMaxJmp{maxJmpsDp[jmpI]};
                nextMaxJmp = std::max(nextMaxJmp, currMaxJmp + 1); 
            }
        }
    } 

    return maxJmpsDp.back() == kUnreachable ? -1 : maxJmpsDp.back();
}
