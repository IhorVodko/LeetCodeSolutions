// problem : https://leetcode.com/problems/longest-unequal-adjacent-groups-subsequence-i/description/
// submission : https://leetcode.com/problems/longest-unequal-adjacent-groups-subsequence-i/submissions/1634629460
// solution post : https://leetcode.com/problems/longest-unequal-adjacent-groups-subsequence-i/solutions/6747027/
//    c-modern-readable-code-beats-100-by-cybe-ps1r

// #include <vector>

// let 'n' be a given words count
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    std::vector<std::string> getLongestSubsequence(
        std::vector<std::string> const & words_,
        std::vector<int> const & groups_
    ) const;
};

std::vector<std::string> Solution::getLongestSubsequence(
    std::vector<std::string> const & words_,
    std::vector<int> const & groups_
) const {
    auto subseq{std::vector<string>{words_.at(0)}};
    auto const wordsCount{words_.size()};
    subseq.reserve(wordsCount);
    auto const groupsCount{groups_.size()};
    for(auto writerIdx{0}, readerIdx{1};  readerIdx < groupsCount; ++readerIdx
    ) {
        if(groups_[writerIdx] != groups_[readerIdx]) {
            writerIdx = readerIdx;
            subseq.emplace_back(words_[writerIdx]);
        }
    }
    return subseq;
}
