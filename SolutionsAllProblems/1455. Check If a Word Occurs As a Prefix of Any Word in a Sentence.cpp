// problem : https://leetcode.com/problems/check-if-a-word-occurs-as-a-prefix-of-any-word-in-a-sentence/description/?envType=daily-question&envId=2024-12-02 
// submission : https://leetcode.com/problems/check-if-a-word-occurs-as-a-prefix-of-any-word-in-a-sentence/submissions/1469318548
// solution post : https://leetcode.com/problems/check-if-a-word-occurs-as-a-prefix-of-any-word-in-a-sentence/solutions/6109248/c-modern-readable-code-beats-100-runtime

// #include <string>
// #include <ssteam>


class Solution {
public:
    // let 'n' be an input length,
    //   'w' - total number of words in input,
    //    'k' - length of a search word
    //     'l' - avarage word length in the input
    // time complexity O(n + w * k)
    // space complexity O(l)
    // runtime 0 ms, beats 100.00 %
    int isPrefixOfWord(
        std::string sentence,
        std::string const searchWord
    ) {
        auto iss{std::istringstream{std::move(sentence)}};
        auto word{""s};
        auto index{0};
        while(std::getline(iss, word, ' ')) {
            ++index;
            if(word.starts_with(searchWord)) {
                return index;
            }
        }
        return -1;
    }
};
