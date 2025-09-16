// problem : https://leetcode.com/problems/vowel-spellchecker/description/
// submission : https://leetcode.com/problems/vowel-spellchecker/submissions/1772727665
// solution post : https://leetcode.com/problems/vowel-spellchecker/solutions/7196289/
//    c-modern-readable-code-optimal-time-comp-co8z

// import std;

class Solution {
public:
// let 'l' be a word count of the given list
// 'q' - query count
// time complexity O(l + q)
// space complexity O(l)
// runtime 35 ms, beats 77.94 %
    [[nodiscard]]
    auto spellchecker(
        std::vector<std::string> const & wordList_,
        std::vector<std::string> const & queries_
    ) const -> std::vector<std::string>;
private:
    [[nodiscard]]
    auto IsVowel(char const chr_) const -> bool;
    auto ToLowerStr(std::string const & str_) const -> std::string;
    auto HideVowelsStr(std::string const & str_) const -> std::string;
    static std::unordered_set<char> const kVowels;
};

auto Solution::spellchecker(
    std::vector<std::string> const & wordList_,
    std::vector<std::string> const & queries_
) const -> std::vector<std::string> {
    namespace ranges = std::ranges;
    namespace veiws = std::views;
    auto const wordListSz{std::ssize(wordList_)};
    auto dictOriginal{std::unordered_set<std::string>{}};
    dictOriginal.reserve(wordListSz);
    auto dictLowerToOriginal{std::unordered_map<std::string, int>{}};
    dictLowerToOriginal.reserve(wordListSz);
    auto dictNoVowelToOriginal{std::unordered_map<std::string, int>{}};
    dictNoVowelToOriginal.reserve(wordListSz);
    for(auto const idx: views::iota(0, wordListSz)) {
        auto const wordOriginal{wordList_.at(idx)};
        dictOriginal.emplace(wordOriginal);
        auto const wordLower{ToLowerStr(wordOriginal)};
        dictLowerToOriginal.emplace(wordLower, idx);
        dictNoVowelToOriginal.emplace(HideVowelsStr(wordLower), idx);
    }
    auto matchedWords{std::vector<std::string>{}};
    for(auto const & query: queries_) {
        if( auto const matchedIt{dictOriginal.find(query)};
            matchedIt != dictOriginal.cend()
        ) {
            matchedWords.emplace_back(*matchedIt);
        } else {
            auto const lowerStr{ToLowerStr(query)};
            if( auto const matchedIt{dictLowerToOriginal.find(lowerStr)};
                matchedIt != dictLowerToOriginal.cend()
            ) {
                auto const wordIdx{matchedIt->second};
                matchedWords.emplace_back(wordList_.at(wordIdx));
            } else if (
                auto const matchedIt{dictNoVowelToOriginal.find(
                    HideVowelsStr(lowerStr)
                )};
                matchedIt != dictNoVowelToOriginal.cend()
            ) {
                auto const wordIdx{matchedIt->second};
                matchedWords.emplace_back(wordList_.at(wordIdx));   
            } else {
                matchedWords.emplace_back("");
            }
        }
    }
    return matchedWords;
}

auto Solution::IsVowel(char const chr_) const -> bool {
    auto const isVowel{kVowels.contains(chr_)};
    return isVowel;
}

auto Solution::ToLowerStr(std::string const & str_) const -> std::string {
    auto strLower{std::string{}};
    ranges::transform(
        str_, 
        std::back_inserter(strLower),
        [] (auto const chr_) { return std::tolower(chr_); }
    );
    return strLower;
}

auto Solution::HideVowelsStr(std::string const & str_) const -> std::string {
    auto noVowelStr{std::string{}};
    ranges::replace_copy_if(
        str_,
        std::back_inserter(noVowelStr),
        [this] (auto const chr_) {
            return IsVowel(chr_);
        },
        '*' 
    );
    return noVowelStr;
}

std::unordered_set<char> const Solution::kVowels{
    'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u'
};
