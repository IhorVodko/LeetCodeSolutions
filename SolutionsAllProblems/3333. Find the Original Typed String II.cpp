// problem : https://leetcode.com/problems/find-the-original-typed-string-ii/description/
// submission : https://leetcode.com/problems/find-the-original-typed-string-ii/submissions/1683996625
// solution post : https://leetcode.com/problems/find-the-original-typed-string-ii/solutions/6911724/
//    c-modern-readable-code-optimal-time-comp-hma7

// #include <ranges>
// #include <string>
// #include <vector>

namespace Util {
    inline auto constexpr kMod{static_cast<int>(1e9) + 7};
}

class Solution {
public:
// let 'n' be a length of the given word
// 'm' - a given minimum size of the word
// time complexity O(n + m^2)
// space complexity O(m)
// runtime 675 ms, beats 8.33 %
    [[nodiscard]]
    int possibleStringCount(
        std::string_view const word_,
        int const wordSzMin_
    ) const;
};

int Solution::possibleStringCount(
    std::string_view const word_,
    int const wordSzMin_
) const {
    namespace views = std::views;
    using namespace Util;
    auto const wordSz{word_.size()};
    auto chrCnt{1};
    auto chrCnts{std::vector<int>{}};
    for(auto const && [chr1, chr2]: views::zip(word_, word_ | views::drop(1))
    ) {
        if(chr1 == chr2) {
            ++chrCnt;
        } else {
            chrCnts.emplace_back(chrCnt);
            chrCnt = 1;
        }
    }
    chrCnts.emplace_back(chrCnt);
    auto wordsCnt{1};
    for(auto && chrCnt: chrCnts) {
        wordsCnt = (static_cast<long long>(wordsCnt) * chrCnt) % kMod;
    }
    if(chrCnts.size() >= wordSzMin_) {
        return wordsCnt;
    }
    auto wordsCntOfSzLessMinPrev{std::vector<int>(wordSzMin_, 0)};
    auto wordsCntOfSzLessMinCurr{std::vector<int>(wordSzMin_ , 1)};
    wordsCntOfSzLessMinPrev.at(0) = 1;
    for(auto const && idx: views::iota(0u, chrCnts.size())) {
        auto wordsCntOfSzLessMinPrevNew{std::vector<int>(wordSzMin_, 0)};
        for(auto const && idx2: views::iota(1, wordSzMin_)) {
            wordsCntOfSzLessMinPrevNew.at(idx2) =
                wordsCntOfSzLessMinCurr.at(idx2 -1);
            if(idx2 - chrCnts.at(idx) - 1 >= 0) {
                wordsCntOfSzLessMinPrevNew.at(idx2) =
                    (wordsCntOfSzLessMinPrevNew.at(idx2) -
                    wordsCntOfSzLessMinCurr.at(
                        idx2 - chrCnts.at(idx) - 1) + kMod) % kMod;
            }
        }
        auto wordsCntOfSzLessMinCurrNew{std::vector<int>(wordSzMin_, 0)};
        wordsCntOfSzLessMinCurrNew.at(0) = wordsCntOfSzLessMinPrevNew.at(0);
        for(auto const && idx2: views::iota(1, wordSzMin_)) {
            wordsCntOfSzLessMinCurrNew[idx2] =
                (wordsCntOfSzLessMinCurrNew[idx2 - 1] +
                wordsCntOfSzLessMinPrevNew[idx2]) % kMod;
        } 
        wordsCntOfSzLessMinPrev = std::move(wordsCntOfSzLessMinPrevNew);
        wordsCntOfSzLessMinCurr = std::move(wordsCntOfSzLessMinCurrNew);
    }
    wordsCnt = (wordsCnt - wordsCntOfSzLessMinCurr.at(wordSzMin_ - 1) + kMod) % kMod;
    return wordsCnt;
}
