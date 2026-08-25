// problem : https://leetcode.com/problems/smallest-missing-multiple-of-k/description
// submission : https://leetcode.com/problems/smallest-missing-multiple-of-k/submissions/2119647979
// solution post : https://leetcode.com/problems/smallest-missing-multiple-of-k/solutions/8482147/
//    simplanation-simple-explanation-by-cyber-r4re

// Approach : Bounded Iterative Search via Hashing
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the count of input nubmers
// 'm' - maximum possible number
// 'k' - given divisor
// Time :  O(n + m / k)
// Space : O(m), or O(1) auxiliary

// import std;

// #include <vector>
// #include <ranges>
// #include <algorithm>
// #include <bitset>
// #include <ios>
// #include <iostream>

namespace {

namespace rs = std::ranges;
namespace vs =std::views;

constexpr auto kMaxNum{100};

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
    static auto missingMultiple(
        std::vector<int> const & nums_,
        int const div_
    ) -> int;
};

auto Solution::missingMultiple(
    std::vector<int> const & nums_,
    int const div_
) -> int {
    // 1. Hash the array elements to allow constant time presence checks
    auto presentNums{std::bitset<kMaxNum + 1>{}}; 
    for(auto const num: nums_) {
        presentNums.set(num);
    }

    // 2. Find the first multiple of div_ missing from our set
    return *rs::find_if(
        vs::iota(div_) | vs::stride(div_),
        [&] (auto const num_) {
            // Multiples exceeding max array limit are guaranteed to be missing
            return num_ > kMaxNum || !presentNums.test(num_);
        }
    );
}
