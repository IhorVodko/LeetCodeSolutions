// problem : https://leetcode.com/problems/number-of-strings-that-appear-as-substrings-in-word/description
// submission : https://leetcode.com/problems/number-of-strings-that-appear-as-substrings-in-word/submissions/2050120357
// solution post : https://leetcode.com/problems/number-of-strings-that-appear-as-substrings-in-word/solutions/8365804/
//    modern-readable-code-optimal-time-comple-omv8

// Approach : Iterative Substring Search
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the number of patterns
// 'm' - the word length
// Time :  O(n * m)
// Space : O(1)

// import std;

class Solution final {
public:
    [[nodiscard]]
    static auto numOfStrings(
        std::vector<std::string> const & patterns_,
        std::string_view const word_
    ) -> int;
};

auto Solution::numOfStrings(
    std::vector<std::string> const & patterns_,
    std::string_view const word_
) -> int {
    // Accumulate total valid substring occurrences.
    return std::ranges::count_if(patterns_, [&] (auto const pattern_) {
        return word_.contains(pattern_);
    });
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
