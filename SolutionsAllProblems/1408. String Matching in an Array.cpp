// problem :  https://leetcode.com/problems/string-matching-in-an-array/description/
// submission : https://leetcode.com/problems/string-matching-in-an-array/submissions/1500950795
// solution post : https://leetcode.com/problems/string-matching-in-an-array/solutions/6245746/c-modern-readable-code-beats-100-runtime-dwy1

// #include <algorithm>
// #include <string>
// #include <vector>

// let 'ws' be a parameter 'words' length
// 'w' - length of the longest word length in 'words'
// time complexity O(ws^2 * w^2)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    using StrsT = std::vector<std::string>;
    StrsT stringMatching(
        StrsT & words
    ) {
        if(words.size() == 1) {
            return {};
        }
        Preprocess(words);
        return FindAllSubstrs(words);
    }
private:
    void Preprocess(StrsT & words) const {
        std::sort(words.begin(), words.end(), [] (
                auto const & lhs,
                auto const & rhs
            ) {
                return lhs.size() <= rhs.size();
        });
    }
    StrsT FindAllSubstrs(StrsT & words) {
        substrs.clear();
        substrs.reserve(words.size());
        for(auto substr{words.begin()}, end{words.end()}; substr < end;
            ++substr
        ) {
            for(auto word{substr + 1}; word < end; ++word) {
                if(word->find(*substr) != std::string::npos) {
                    substrs.emplace_back(std::move(*substr));
                    break;
                }  
            }
        }
        return substrs;
    }
    StrsT substrs;
};
