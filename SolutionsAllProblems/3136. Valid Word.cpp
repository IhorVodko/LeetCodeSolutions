// problem : https://leetcode.com/problems/valid-word/description/?envType=daily-question&envId=2025-07-15
// submission : https://leetcode.com/problems/valid-word/submissions/1699763346
// solution post : https://leetcode.com/problems/valid-word/solutions/6965532/
//    c-modern-readable-code-beats-100-runtime-j5cg

// #include <cctype>
// #include <string>

namespace Util {
    inline auto constexpr kRequiredMinChrsCount{3u};
    inline auto const kVowels{std::unordered_set{'a', 'e', 'i', 'o', 'u'}};

}

class Solution {
public:
    [[nodiscard]]
    bool isValid(std::string_view const word_) const;
};

bool Solution::isValid(std::string_view const word_) const {
    using namespace Util;
    if(word_.size() < kRequiredMinChrsCount) {
        return false;
    }
    auto doesContainAtLeastOneVowel{false};
    auto doesContainAtLeastOneConsonent{false};
    for(auto const chr: word_) {
        if(!std::isalnum(chr)) {
            return false;
        }
        if(std::isalpha(chr)) {
            if(kVowels.contains(std::tolower(chr))) {
                doesContainAtLeastOneVowel = true;
            } else {
                doesContainAtLeastOneConsonent = true;
            }
        }
    }
    auto const isValidWord{
            doesContainAtLeastOneVowel
        &&  doesContainAtLeastOneConsonent};
    return isValidWord;
}
