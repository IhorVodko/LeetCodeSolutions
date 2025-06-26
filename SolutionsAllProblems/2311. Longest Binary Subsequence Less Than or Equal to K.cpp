// problem : https://leetcode.com/problems/longest-binary-subsequence-less-than-or-equal-to-k/description/
// submission : https://leetcode.com/problems/longest-binary-subsequence-less-than-or-equal-to-k/submissions/1677363057
// solution post : https://leetcode.com/problems/longest-binary-subsequence-less-than-or-equal-to-k/solutions/6888831/
//    c-modern-readable-code-beats-100-runtime-fyt2

// #include <bit>
// #include <ranges>
// #include <string_veiw>

namespace Util {
    auto constexpr KBitOn{'1'};
}

class Solution {
public:
// let 'n' be a length of the given string
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    int longestSubsequence(
        std::string_view const str_,
        int const numMax_
    ) const;
};

int Solution::longestSubsequence(
    std::string_view const str_,
    int const numMax_
) const {
    using namespace Util;
    namespace views = std::views;
    auto numCurr{0};
    auto subSeqSzMax{0};
    auto numMaxBitWidth{std::bit_width(static_cast<unsigned>(numMax_))};
    auto const strSz{str_.size()};
    for(auto const idx: views::iota(0u, strSz)) {
        auto const chr{str_.at(strSz - 1 - idx)};
        if(chr == KBitOn) {
            if(idx < numMaxBitWidth) {
                auto const numDelta{static_cast<int>(std::pow(2, idx))};
                if(auto const numCurrNew{numCurr + numDelta};
                    numCurrNew <= numMax_
                ) {
                    numCurr = numCurrNew;
                    ++subSeqSzMax;
                }
            }
        } else {
                ++subSeqSzMax;
        }
    }
    return subSeqSzMax;
}
