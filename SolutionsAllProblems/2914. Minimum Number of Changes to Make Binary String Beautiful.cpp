// problem : https://leetcode.com/problems/minimum-number-of-changes-to-make-binary-string-beautiful/description 
// submission : https://leetcode.com/problems/minimum-number-of-changes-to-make-binary-string-beautiful/submissions/2198773887
// solution post : https://leetcode.com/problems/minimum-number-of-changes-to-make-binary-string-beautiful/solutions/8617100/
//    simplanation-simple-explanation-by-cyber-decp

// Approach : Greedy Pairwise Partitioning
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the string length
// Time :  O(n)
// Space : O(1)

// import std;

// #include <algorithm>
// #include <ios>
// #include <iostream>
// #include <ranges>
// #include <string_view>

namespace rs = std::ranges;
namespace vs = std::views;

namespace {

constexpr auto kChunkSz{2};

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
    static auto minChanges(std::string_view const str_) -> int;
};

auto Solution::minChanges(std::string_view const str_) -> int {
    // 1. Isolate adjacent non-overlapping pairs
    auto chunkedStr{str_ | vs::chunk(kChunkSz)};
    // Detect mixed characters breaking the uniform block requirement
    const auto isChangeNeeded{[] (const auto & chrPair_) {
        return chrPair_.front() != chrPair_.back();
    }}; 

    // 2. Sum the bit flips required across all pairs
    const auto totChanges{rs::count_if(chunkedStr, isChangeNeeded)};

    return static_cast<int>(totChanges);
}
