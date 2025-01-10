// problem : https://leetcode.com/problems/word-subsets/description/
// submission : https://leetcode.com/problems/word-subsets/submissions/1504458779
// solution post : https://leetcode.com/problems/word-subsets/solutions/6261791/c-modern-readable-code-optimal-time-comp-6k54

// #include <algorithm>
// #include <string>
// #include <vector>

namespace Utility {
    auto constexpr alphabetSize{26};
    auto constexpr alphabetStart{'a'};
    auto constexpr minNum{std::numeric_limits<size_t>::min()};
}

// let 'w1' be a count of chars in 'words1' parameter
// 'w2' - count of chars in 'words2' parameter
// time complexity O(w1 + w2)
// space complexity O(1)
// runtime 13 ms, beats 85.71 %
class Solution {
public:
    using WordsT = std::vector<std::string>;
    WordsT wordSubsets(
        WordsT & words1,
        WordsT const & words2
    ) {
        using namespace Utility;
        Reset();
        universalStrs.reserve(words1.size());
        PreprocessSubStrs(words2);
        for(auto & universalStr: words1) {
            if(IsUniversalStr(universalStr)) {
                 universalStrs.emplace_back(std::move(universalStr));
            }
        }
        return universalStrs;
    }
    Solution() :
        subStrsChrMaxCounts(Utility::alphabetSize, Utility::minNum),
        subStrChrCounts(Utility::alphabetSize, Utility::minNum),
        universalStrChrCounts(Utility::alphabetSize, Utility::minNum),
        subStrMaxLength{Utility::minNum}
    {}
private:
    void Reset() {
        using namespace Utility;
        universalStrs.clear();
        std::fill(subStrsChrMaxCounts.begin(), subStrsChrMaxCounts.end(),
            minNum);
        std::fill(subStrChrCounts.begin(), subStrChrCounts.end(),
            minNum);
        std::fill(universalStrChrCounts.begin(), universalStrChrCounts.end(),
            minNum);
        subStrMaxLength = minNum;
    }
    void PreprocessSubStrs(WordsT const & subStrs) {
        using namespace Utility;
        for(auto & subStr: subStrs) {
            std::fill(subStrChrCounts.begin(), subStrChrCounts.end(), minNum);
            for(auto chr: subStr) {
                chr -= alphabetStart;
                subStrsChrMaxCounts.at(chr) = std::max(
                    subStrsChrMaxCounts.at(chr), ++subStrChrCounts.at(chr));
            }
            subStrMaxLength = std::max(subStrMaxLength, subStr.size());
        }
    }
    bool IsUniversalStr(std::string const & str) {
        using namespace Utility;
        if(str.size() < subStrMaxLength) {
            return false;
        }
        std::fill(universalStrChrCounts.begin(), universalStrChrCounts.end(),
            minNum);
        for(auto chr: str) {
            chr -= alphabetStart;
            ++universalStrChrCounts.at(chr);
        }
        for(auto idx{0Z}; idx < alphabetSize; ++idx) {
            if(universalStrChrCounts.at(idx) < subStrsChrMaxCounts.at(idx)) {
                return false;
            }
        }
        return true;
    }
    WordsT universalStrs;
    std::vector<size_t> subStrsChrMaxCounts;
    std::vector<size_t> subStrChrCounts;
    std::vector<size_t> universalStrChrCounts;
    size_t subStrMaxLength;
};
