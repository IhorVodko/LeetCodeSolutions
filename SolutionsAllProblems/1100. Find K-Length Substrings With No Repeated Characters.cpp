// problem : https://leetcode.com/problems/find-k-length-substrings-with-no-repeated-characters/description/
// submission : https://leetcode.com/problems/find-k-length-substrings-with-no-repeated-characters/submissions/
//     1569536611
// solution post : https://leetcode.com/problems/find-k-length-substrings-with-no-repeated-characters/solutions/
//     6521713/c-modern-readable-code-beats-100-runtime-8yqu

// #include <bitset>
// #include <string>

namespace  Utility {
    auto constexpr alphabetSize{26}; 
}

// let 'n' be a length of the given string
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int numKLenSubstrNoRepeats(
        std::string const & str_,
        int const requiredSubstrSz_
    ) const {
        using namespace Utility;
        if(str_.size() < requiredSubstrSz_ ||
            requiredSubstrSz_ > alphabetSize
        ) {
            return 0;
        } 
        auto chrsPresence{std::bitset<alphabetSize>{}};
        auto validSubstrsCount{0};
        for(auto firstChrIt{str_.begin()}, lastChrIt{str_.begin()},
            strEnd{str_.end()}; lastChrIt < strEnd;
        ) {
            auto const chrNumFirst{*firstChrIt - 'a'};  
            auto const chrNumLast{*lastChrIt - 'a'};
            auto const substrSz{lastChrIt - firstChrIt + 1};
            if(!chrsPresence.test(chrNumLast) && substrSz == requiredSubstrSz_
            ) {
                ++validSubstrsCount;
                chrsPresence.set(chrNumLast);
                chrsPresence.reset(chrNumFirst);
                ++firstChrIt;
                ++lastChrIt;
            } else if(chrsPresence.test(chrNumLast)) {
                chrsPresence.reset(chrNumFirst);
                ++firstChrIt;
            } else {
                chrsPresence.set(chrNumLast);
                ++lastChrIt;
            }
        }
        return validSubstrsCount;
    }
};
