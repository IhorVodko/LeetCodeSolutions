// problem : https://leetcode.com/problems/find-words-containing-character/description/
// submission : https://leetcode.com/problems/find-words-containing-character/submissions/1644226936
// solution post : https://leetcode.com/problems/find-words-containing-character/solutions/6780550/
//    c-modern-readable-code-beats-100-by-cybe-m7vz

// #include <string>
// #include <vector>

class Solution {
public:
// let 'w' be a words count given
// 's' - average length of the words given
// time complexity O(w * s)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    std::vector<int> findWordsContaining(
        std::vector<std::string> const & words_,
        char const chr_
    ) const;
};

std::vector<int> Solution::findWordsContaining(
    std::vector<std::string> const & words_,
    char const chr_
) const {
    auto idxs{std::vector<int>{}};
    idxs.reserve(words_.size());
    for(auto word{words_.begin()}, end{words_.end()}; word < end; ++word) {
        if(word->find(chr_) != std::string::npos) {
            idxs.emplace_back(word - words_.begin());
        } 
    }
    return idxs;
}
