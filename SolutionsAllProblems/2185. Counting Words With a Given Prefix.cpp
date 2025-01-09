// problem : https://leetcode.com/problems/counting-words-with-a-given-prefix/description/
// submission : https://leetcode.com/problems/counting-words-with-a-given-prefix/submissions/1503231853
// solution post : https://leetcode.com/problems/counting-words-with-a-given-prefix/solutions/6256598/c-modern-readable-code-beats-100-runtime-71wv

// #include <algorithm>
// #include <string>
// #include <vector>

// let 'w' be a parameter 'words' length
// 'p' - parameter 'pref' length
// time complexity O(w * p)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int prefixCount(
        std::vector<std::string> const & words,
        std::string const & pref
    ) const {
        return std::count_if(words.begin(), words.end(), [&] (auto & word) {
            return word.starts_with(pref); }); 
    }
};
