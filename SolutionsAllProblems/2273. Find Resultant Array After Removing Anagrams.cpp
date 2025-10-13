// problem : https://leetcode.com/problems/find-resultant-array-after-removing-anagrams/description/
// submission : https://leetcode.com/problems/find-resultant-array-after-removing-anagrams/submissions/1800436301
// solution post : https://leetcode.com/problems/find-resultant-array-after-removing-anagrams/solutions/7272390/
//    c-modern-readable-code-beats-100-runtime-sez8

// import std;

class Solution {
public:
// let 'w' be the number of the given words
// 'l' - length of the longest word
// 'c' - give character set size
// time complexity O(w * l)
// space complexity O(c)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto removeAnagrams(
        std::vector<std::string> & words_
    ) -> std::vector<std::string>;

private:
    [[nodiscard]]
    auto IsAnagram(
        std::string_view const word1_,
        std::string_view const word2_
    ) -> bool;

    inline static bool const kIsFastIO{
        [] () {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return true;
        } ()
    };
    inline static int constexpr kChrSetSz{26};
    inline static char constexpr kChrSetFirst{'a'};
    std::array<int, kChrSetSz> mChrCnt{};
};

auto Solution::removeAnagrams(
    std::vector<std::string> & words_
) -> std::vector<std::string> {
    namespace vs = std::views;

    auto const wordsSz{std::ssize(words_)};
    if(wordsSz <= 1) {
        return words_;
    }
    auto wordsLeft{std::vector<std::string>{words_[0]}};
    wordsLeft.reserve(wordsSz);
    auto isWordMoved{false};
    for(auto const [prevIdx, currIdx]:
        vs::zip(vs::iota(0, wordsSz), vs::iota(1, wordsSz))
    ) {
        if(IsAnagram(
            isWordMoved ? wordsLeft.back() : words_[prevIdx],
            words_[currIdx])
        ) {
            isWordMoved = false;
            continue;
        }
        wordsLeft.emplace_back(std::move(words_[currIdx]));
        isWordMoved = true;
    }
    wordsLeft.shrink_to_fit();
    return wordsLeft;
}

auto Solution::IsAnagram(
    std::string_view const word1_,
    std::string_view const word2_
) -> bool {
    namespace rngs = std::ranges;
    
    rngs::fill(mChrCnt, 0);
    if(word1_.size() != word2_.size()) {
        return false;
    }
    for(auto const chr: word1_) {
        ++mChrCnt.at(chr - kChrSetFirst);
    }
    for(auto const chr: word2_) {
        if(--mChrCnt.at(chr - kChrSetFirst) < 0) {
            return false;
        }
    }
    return true;
}
