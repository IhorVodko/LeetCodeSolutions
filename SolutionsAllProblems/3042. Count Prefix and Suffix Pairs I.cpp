// problem : https://leetcode.com/problems/count-prefix-and-suffix-pairs-i/description/
// submission : https://leetcode.com/problems/count-prefix-and-suffix-pairs-i/submissions/1502026921
// solution post : https://leetcode.com/problems/count-prefix-and-suffix-pairs-i/solutions/6250413/c-modern-readable-code-beats-100-runtime-etqb

// #include <string>
// #include <vector>

// let 'ws' be a parameter 'words' length
// 'w' - length of the longest word in 'words'
// time complexity O(ws^2 * w)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int countPrefixSuffixPairs(std::vector<std::string> const & words) const {
        auto result{0};
        auto idx{0Z};
        for_each(words.begin(), words.end() - 1, [&] (auto & w1) {
            ++idx;
            for_each(words.begin() + idx, words.end(), [&] (auto & w2) {
                if(w1.size() <= w2.size() && w2.starts_with(w1) &&
                    w2.ends_with(w1)
                ) {
                    ++result;
                }
            });
        });
        return result;
    }
};
