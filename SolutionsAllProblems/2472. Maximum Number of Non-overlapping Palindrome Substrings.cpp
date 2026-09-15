// problem : https://leetcode.com/problems/maximum-number-of-non-overlapping-palindrome-substrings/description
// submission : https://leetcode.com/problems/maximum-number-of-non-overlapping-palindrome-substrings/submissions/2142613884
// solution post : https://leetcode.com/problems/maximum-number-of-non-overlapping-palindrome-substrings/solutions/8522921/
//  simplanation-simple-explanation-by-cyber-xeaj

// Approach : Greedy Early Acceptance
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'N' be the stirng length
// 'M' - minimum required substring length
// Time :  O(N * M)
// Space : O(1)

// import std;

// #include <algorithm>
// #include <ios>
// #include <iostream>
// #include <iterator>
// #include <ranges>
// #include <string>
// #include <string_view>

// #include <cstddef>

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

// Evaluate if string view characters are identical when read symmetrically.
constexpr auto isPalindrome{[] (std::string_view const str_) {
    auto const halfSz{str_.size() / 2};
    auto const frontHalf{str_ | vs::take(halfSz)};
    auto const backHalfRev{str_ | vs::reverse | vs::take(halfSz)};

    return rs::equal(frontHalf, backHalfRev);
}};

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
    static auto maxPalindromes(
        std::string const & str_, 
        int const substrMinLen_
    ) -> int;
};

auto Solution::maxPalindromes(
    std::string const & str_, 
    int const substrMinLen_
) -> int {
    auto const strEndIt{str_.cend()};
    auto palindromeCnt{0};

    // 1. Traverse string dynamically to isolate maximum disjoint palindromes.
    for(auto substrStartIt{str_.cbegin()}, substrNextIt{str_.cbegin()};
        strEndIt - substrStartIt >= substrMinLen_;
        substrStartIt = substrNextIt
    ) {
        // 2. Greedily match shortest allowed palindrome to save characters.
        if(isPalindrome(std::string_view{substrStartIt, substrStartIt + substrMinLen_})
        ) {
            ++palindromeCnt;
            substrNextIt += substrMinLen_;
        } else
        // 3. Fallback to length plus one to handle alternate center parities.
        if( auto const substrLen{substrMinLen_ + 1};
            strEndIt - substrStartIt >= substrLen &&
            isPalindrome(std::string_view{substrStartIt, substrStartIt + substrLen})
        ) {
            ++palindromeCnt;
            substrNextIt += substrLen;
        } else {
            // 4. Advance search window incrementally if no palindrome starts here.
            ++substrNextIt;
        }
    }
    
    return palindromeCnt;
}
