// problem : https://leetcode.com/problems/reverse-words-in-a-string/description/
// submission : https://leetcode.com/problems/reverse-words-in-a-string/submissions/1480543832
// solution post : https://leetcode.com/problems/reverse-words-in-a-string/solutions/6154002/c-modern-readable-code-beats-100-runtime-8zaz


// #include <algorithm>
// #include <iterator>
// #include <sstream>
// #incldue <string>


class Solution {
public:
    // let 'n' be a parameter 'str' length
    // time complexity O(n)
    // space complexity O(n)
    // runtime 0 ms, beats 100.00 %
    std::string reverseWords(std::string str) const {
        str.erase(0, str.find_first_not_of(' '));
        str.erase(str.find_last_not_of(' ') + 1);
        auto words{std::vector<std::string>{}};
        auto iss{std::istringstream{std::move(str)}};
        std::move(std::istream_iterator<std::string>{iss},
            std::istream_iterator<std::string>(), std::back_inserter(words));
        std::reverse(words.begin(), words.end());
        auto oss{std::ostringstream{}};
        std::move(words.cbegin(), words.cend() - 1,
            std::ostream_iterator<std::string>(oss, " "));
        oss << std::move(words.back()); 
        return oss.str();
    }
};
