// problem : https://leetcode.com/problems/total-characters-in-string-after-transformations-i/description/
// submission : https://leetcode.com/problems/total-characters-in-string-after-transformations-i/submissions/1633170228
// solution post : https://leetcode.com/problems/total-characters-in-string-after-transformations-i/solutions/6741890/
//    c-modern-readable-code-optimal-time-comp-m0l9

// #include <algorithm>
// #include <array>
// #include <string>
// #include <vector>

namespace Utility {
    auto constexpr kMod{static_cast<size_t>(1e9 + 7)};
    auto constexpr kAlphabetSize{static_cast<size_t>(26)};
    auto constexpr kAlphabetBegin{'a'};
}

class Solution {
public:
// let 's' be a length of the stirng given
// 'c' - size of the given character set
// time complexity O(s + c)
// space complexity O(c)
// runtime 101 ms, beats 74.63 %
    int lengthAfterTransformations(
        std::string const & str_, 
        int const transformationsCount_
    ) const;
};

int Solution::lengthAfterTransformations(
    std::string const & str_, 
    int const transformationsCount_
) const {
    using namespace Utility;
    auto chrsCounts{std::array<size_t, kAlphabetSize>{}};
    chrsCounts.fill(0);
    for(auto const chr: str_) {
        ++chrsCounts.at(chr - kAlphabetBegin);
    }
    auto nextChrsCount{std::array<size_t, kAlphabetSize>{}};
    for(auto transofrmationsDoneCount{static_cast<size_t>(0)};
        transofrmationsDoneCount < transformationsCount_;
        ++transofrmationsDoneCount
    ) {
        nextChrsCount.fill(0);
        nextChrsCount.at(0) = chrsCounts.at(kAlphabetSize - 1);
        nextChrsCount.at(1) = (chrsCounts.at(kAlphabetSize - 1) +
            chrsCounts.at(0)) % kMod;
        for(auto chrIdx{static_cast<size_t>(2)}; chrIdx < kAlphabetSize;
            ++chrIdx
        ) {
            nextChrsCount.at(chrIdx) = chrsCounts.at(chrIdx - 1);
        }
        std::copy(nextChrsCount.cbegin(), nextChrsCount.cend(),
            chrsCounts.begin());
    }
    auto strFinalLength{static_cast<size_t>(0)};
    for(auto chrIdx{static_cast<size_t>(0)}; chrIdx < kAlphabetSize; ++chrIdx) {
        strFinalLength = (strFinalLength + chrsCounts.at(chrIdx)) % kMod;
    }
    return strFinalLength;
}
