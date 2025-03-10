// problem : https://leetcode.com/problems/count-of-substrings-containing-every-vowel-and-k-consonants-ii/description/
// submission : https://leetcode.com/problems/count-of-substrings-containing-every-vowel-and-k-consonants-ii/
//     submissions/1569404483
// solution post : https://leetcode.com/problems/count-of-substrings-containing-every-vowel-and-k-consonants-ii/
//     solutions/6521363/c-modern-readable-code-optimal-time-comp-t103

// #include <string>
// #include <unordered_map>
// #include <unordered_set>

namespace Constants {
    auto const vowels{std::unordered_set<char>{'a', 'e', 'i', 'o', 'u'}}; 
}

// let 'n' be a length of the given string
// time complexity O(n)
// space complexity O(1)
// runtime 278 ms, beats 32.60 %
class Solution {
public:
    long long countOfSubstrings(
        std::string const & str_,
        int const requiredConsonantsCount_
    ) const {
        return countOfSubstringsRelaxed(str_, requiredConsonantsCount_) -
            countOfSubstringsRelaxed(str_, requiredConsonantsCount_ + 1); 
    }
private:
    long long countOfSubstringsRelaxed(
        std::string const & str_,
        int const requiredConsonantsCount_
    ) const {
        auto validSubstrsCount{0LL};
        auto vowelsCount{std::unordered_map<char, int>{}};
        auto consonantsCount{size_t{0}};
        for(auto firstChrIt{str_.begin()}, lastChrIt{str_.begin()},
            strEnd{str_.end()}; lastChrIt < strEnd; ++lastChrIt
        ) {
            if(IsVowel(*lastChrIt)) {
                ++vowelsCount[*lastChrIt];
            } else {
                ++consonantsCount;
            }
            for(;vowelsCount.size() == 5 &&
                consonantsCount >= requiredConsonantsCount_;  ++firstChrIt
            ) {
                validSubstrsCount += strEnd - lastChrIt;
                if(!IsVowel(*firstChrIt)) {
                    --consonantsCount;
                } else if (--vowelsCount[*firstChrIt] == 0) {
                    vowelsCount.erase(*firstChrIt);
                }
            }
        }
        return validSubstrsCount;
    }
    bool IsVowel(char const chr) const {
        using namespace Constants;
        return vowels.contains(chr);
    }
};
