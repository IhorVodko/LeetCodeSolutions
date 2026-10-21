// problem : https://leetcode.com/problems/minimum-operations-to-sort-a-string/description
// submission : https://leetcode.com/problems/minimum-operations-to-sort-a-string/submissions/2177954858
// solution post : https://leetcode.com/problems/minimum-operations-to-sort-a-string/solutions/8582437/
//  simplanation-simple-explanation-by-cyber-f2dm

// Approach : Constructive Case Analysis
// Runtime : 4 ms, beats 91.59 %

// Complexity analysis
// let 'n' be the number of
// Time :  O(n)
// Space : O(1)

// import std;

// #include <algorithm>
// #include <ios>
// #include <iostream>
// #include <iterator>
// #include <string_view>

namespace rs = std::ranges;

namespace {

// Represents an unsolvable configuration
constexpr auto kNotPossible{-1};

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
    static auto minOperations(std::string_view const str_) -> int;  
};

auto Solution::minOperations(std::string_view const str_) -> int {
    // 1. Return zero if the sequence is already in the sorted state
    if(rs::is_sorted(str_)) {
        return 0;
    }

    // 2. Reject unsorted sequences of length two as proper subsegments have length one
    if(str_.length() == 2) {
        return kNotPossible;
    }

    // 3. Locate iterators for both minimum and maximum elements in one pass
    auto const [minChrIt, maxChrIt]{rs::minmax_element(str_)};
    auto const strLastIt{rs::prev(str_.cend())};

    // 4. Return one if at least one extreme is positioned at its target boundary
    if(minChrIt == str_.begin() || maxChrIt == strLastIt) {
        return 1;
    }

    // 5. Handle complete inversion where extremes block each other
    if(minChrIt == strLastIt && maxChrIt == str_.begin()) {
        return 3;
    }

    // 6. Resolve all other configurations using two overlapping sorts
    return 2;
}
