// problem : https://leetcode.com/problems/count-vowel-strings-in-ranges/description/
// submission : https://leetcode.com/problems/count-vowel-strings-in-ranges/submissions/1495533171
// solution post : https://leetcode.com/problems/count-vowel-strings-in-ranges/solutions/6220327/c-modern-readable-code-beats-100-runtime-7rgv

// #include <algorithm>
// #include <limits>
// #include <string>
// #include <vector>
// #include <unordered_set>

// let 'w' be a parameter 'words' length
// 'q' - a parameter 'query' length
// time complexity O(w +q)
// space complexity O(w)
// runtime 0 ms, beats 100.00 %
namespace Utility {
    auto const vowels{std::unordered_set<char>{'a', 'e', 'i', 'o', 'u'}};    
}

class Solution {
public:
    std::vector<int> vowelStrings(
        std::vector<std::string> const & words,
        std::vector<std::vector<int>> const & queries
    ) const {
        using namespace Utility;
        auto vowelStrsPrefixSum{std::vector<size_t>(words.size(), 0)};
        vowelStrsPrefixSum.front() = isVowelStr(words.front());
        std::transform(words.cbegin() + 1, words.cend(),
            vowelStrsPrefixSum.cbegin(), vowelStrsPrefixSum.begin() + 1, [&] (
                auto const & str,
                auto const count
            ) {
                return count + isVowelStr(str); 
        });
        auto vowelStrsCounts{std::vector<int>{}};
        vowelStrsCounts.reserve(queries.size());
        auto start{std::numeric_limits<int>::min()};
        auto end{std::numeric_limits<int>::min()};
        for(auto const & query: queries) {
            start = query.front();
            end = query.back();
            vowelStrsCounts.emplace_back(vowelStrsPrefixSum.at(end) -
                (start == 0 ? 0 : vowelStrsPrefixSum.at(start - 1)));
        }
        return vowelStrsCounts;
    }
private:
    size_t isVowelStr(
        std::string const & str
    ) const {
        using Utility::vowels;
        return vowels.contains(str.front()) && vowels.contains(str.back()) ?
            1 : 0;
    }
};
