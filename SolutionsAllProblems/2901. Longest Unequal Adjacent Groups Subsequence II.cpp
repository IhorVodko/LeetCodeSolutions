// problem : https://leetcode.com/problems/longest-unequal-adjacent-groups-subsequence-ii/description/
// submission : https://leetcode.com/problems/longest-unequal-adjacent-groups-subsequence-ii/submissions/1635630681
// solution post : https://leetcode.com/problems/longest-unequal-adjacent-groups-subsequence-ii/solutions/6750587/
//    c-modern-readable-code-optimal-time-comp-40ia

// #include <string>
// #include <vector>

class Solution {
public:
// let 'w' be a words count given
// 'l' - length of the longest of the words given
// time complexity O(w^2 * l)
// space complexity O(1)
// runtime 39 ms, beats 84.38 %
    std::vector<std::string> getWordsInLongestSubsequence(
        std::vector<std::string> const & words_,
        std::vector<int> const & groups_
    ) const;
private:
    bool IsValidDistance(
        std::string const & str1_,
        std::string const & str2_
    ) const;
};

std::vector<std::string> Solution::getWordsInLongestSubsequence(
    std::vector<std::string> const & words_,
    std::vector<int> const & groups_
) const {
    auto wordsCount{groups_.size()};
    auto dpCurr{std::vector<int>(wordsCount, 1)};
    auto dpPrev{std::vector<int>(wordsCount, -1)};
    auto idxOfMax{0};
    for(auto i1{1}; i1 < wordsCount; ++i1) {
        for(auto i2{0}; i2 < i1; ++i2) {
            if(IsValidDistance(words_.at(i1), words_.at(i2)) == 1 &&
                dpCurr.at(i2) + 1 > dpCurr.at(i1) &&
                groups_.at(i1) != groups_.at(i2)
            ) {
                dpCurr.at(i1) = dpCurr.at(i2) + 1;
                dpPrev.at(i1) = i2;
            }
        }
        idxOfMax = dpCurr.at(i1) > dpCurr.at(idxOfMax) ? i1 : idxOfMax;
    }
    auto subseq{std::vector<std::string>{}};
    subseq.reserve(words_.size());
    for(auto i{idxOfMax}; i >= 0; i = dpPrev.at(i)) {
        subseq.emplace_back(words_.at(i));
    }
    std::reverse(subseq.begin(), subseq.end());
    return subseq;
}

bool Solution::IsValidDistance(
    std::string const & str1_,
    std::string const & str2_
) const {
    if(str1_.size() != str2_.size()) {
        return false;
    }
    auto diffsCount{0};
    auto const chrsCount{str1_.size()};
    for(auto i{0}; i < chrsCount; ++i) {
        diffsCount += str1_.at(i) == str2_.at(i) ? 0 : 1; 
        if(diffsCount > 1) {
            return false;
        }
    }
    return true;
}
