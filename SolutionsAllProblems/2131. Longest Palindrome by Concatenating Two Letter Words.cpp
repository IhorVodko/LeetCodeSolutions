// problem : https://leetcode.com/problems/longest-palindrome-by-concatenating-two-letter-words/description
// submission : https://leetcode.com/problems/longest-palindrome-by-concatenating-two-letter-words/submissions/1645155878
// solution post : https://leetcode.com/problems/longest-palindrome-by-concatenating-two-letter-words/solutions/6783626/
//    c-modern-readable-code-beats-100-by-cybe-8m2p

// #include <algorithm>
// #include <array>

namespace Utility {
    auto constexpr kAlphabetSize{26};
    auto constexpr kAlphabetStart{'a'};
}

class Solution {
public:
// let 'w' be a count of the given words
// 'a' - the alphabet size used 
// time complexity O(w + a ^ 2)
// space complexity O(a ^ 2)
// runtime 0 ms, beats 100.00 %
    int longestPalindrome(std::vector<std::string> const & words_) const;
};

int Solution::longestPalindrome(
    std::vector<std::string> const & words_
) const {
    using namespace Utility;
    auto wordsCounts{std::array<std::array<int, kAlphabetSize>,
        kAlphabetSize>{}};
    for(auto & arr: wordsCounts) {
        arr.fill(0);
    }
    for(auto const & word: words_) {
        ++wordsCounts.at(word.at(0) - kAlphabetStart).
            at(word.at(1) - kAlphabetStart);
    }
    auto wordsInPalindormeCount{0};
    auto isCentralWordPresent{false};
    for(auto i1{0}; i1 < kAlphabetSize; ++i1) {
        if(wordsCounts.at(i1).at(i1) % 2 == 0) {
            wordsInPalindormeCount += wordsCounts.at(i1).at(i1);
        } else {
            wordsInPalindormeCount += wordsCounts.at(i1).at(i1) - 1;
            isCentralWordPresent = true;
        }
        for(auto i2{i1 + 1}; i2 < kAlphabetSize; ++i2) {
            wordsInPalindormeCount += 2 *
                std::min(wordsCounts.at(i1).at(i2), wordsCounts.at(i2).at(i1));
        }
    }
    if(isCentralWordPresent) {
        ++wordsInPalindormeCount;
    }
    auto const palindromeLength{2 * wordsInPalindormeCount};
    return palindromeLength;
}
