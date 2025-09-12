// problem : https://leetcode.com/problems/vowels-game-in-a-string/description/
// submission : https://leetcode.com/problems/vowels-game-in-a-string/submissions/1768249051
// solution post : https://leetcode.com/problems/vowels-game-in-a-string/solutions/7182418/
//    c-modern-readable-code-optimal-time-comp-zu71

// #include <algorithms>
// #include <string>
// #include <unordered_set>

class Solution {
public:
// let 'n' be a length of the given string
// time complexity O(n)
// space complexity O(1)
// runtime 7 ms, beats 28.96 %
    [[nodiscard]]
    bool doesAliceWin(std::string & str_) const;
private:
    static std::unordered_set<char> const mkVowels;
};

bool Solution::doesAliceWin(std::string & str_) const {
    namespace ranges = std::ranges;
    auto isAliceWinner{ranges::any_of(
        str_,
        [] (auto const chr_) {
            return mkVowels.contains(chr_);
        }
    )};
    return isAliceWinner;
}

const std::unordered_set<char> Solution::mkVowels{'a', 'e', 'i', 'o', 'u'};
