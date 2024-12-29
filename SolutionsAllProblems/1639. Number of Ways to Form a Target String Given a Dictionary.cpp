// problem : https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/description/?envType=daily-question&envId=2024-12-29
// submission : https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/submissions/1491797525
// solution post : https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/solutions/6202449/c-modern-readable-code-by-cyberartist-ei66

// #include <string>
// #include <vector>

// let 'WsL' be a parameter 'words' length
// 'TL' - a parameter 'target' length
// 'WL' - the longest 'word' length at 'words'
// time complexity O(WL * TL + WL * WsL)
// space complexity O(WL + TL)
// runtime 107 ms, beats 23.11 %

namespace Util {
    auto constexpr mod{1'000'000'007};
    auto constexpr alphabetSize{26};
    auto constexpr alphabetStart{'a'};
}

class Solution {
public:
    int numWays(
        std::vector<std::string> const & words,
        std::string const target
    ) const {
        using namespace Util;
        auto wordLength{words.at(0).size()};
        auto targetLength{target.size()};
        auto charFrequenciesByIdx{std::vector<std::vector<size_t>>(
            wordLength, std::vector<size_t>(alphabetSize, 0))};
        for(auto const & word: words) {
            for(auto idx{0z}; idx < word.size(); ++idx) {
                ++charFrequenciesByIdx.at(idx).at(word.at(idx) -
                alphabetStart);
            }
        }
        auto prevCount{std::vector<long>(targetLength + 1, 0)};
        auto currCount{std::vector<long>(targetLength + 1, 0)};
        prevCount.at(0) = 1;
        auto currCharIdx{0z};
        for(auto currWordIdx{1z}; currWordIdx <= wordLength;
            ++currWordIdx
        ) {
            currCount = prevCount;
            for(auto currTargetIdx{1z}; currTargetIdx <= targetLength;
                ++currTargetIdx
            ) {
                currCharIdx = target.at(currTargetIdx - 1) - alphabetStart;
                currCount.at(currTargetIdx) +=
                    (charFrequenciesByIdx.at(currWordIdx - 1).at(currCharIdx) *
                    prevCount.at(currTargetIdx - 1)) % mod;
                    currCount.at(currTargetIdx) %= mod;
            }
            prevCount = currCount;
        }
        return currCount.at(targetLength);
    }
};
