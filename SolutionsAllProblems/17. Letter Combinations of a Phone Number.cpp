// problem : https://leetcode.com/problems/letter-combinations-of-a-phone-number/description/
// submission : https://leetcode.com/problems/letter-combinations-of-a-phone-number/submissions/1758291903
// solution post : https://leetcode.com/problems/letter-combinations-of-a-phone-number/solutions/7151609/
//    c-modern-readable-code-beats-100-runtime-ned3

// #include <string>
// #include <unordered_map>
// #include <vector>

class Solution {
public:
// let 'n' be a count of the given digits
// time complexity O(4^n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    std::vector<std::string> letterCombinations(
        std::string const & digits_
    );
private:
    void BuildComb(
        size_t const digitIdx_,
        std::string & comb_,
        std::string const & digits_
    );
    std::vector<std::string> mCombs;
    static std::unordered_map<char, std::string> const mDigitToChrs;
};

std::vector<std::string> Solution::letterCombinations(
    std::string const & digits_
) {
    mCombs.clear();
    if(digits_.empty()) {
        return {};
    };
    auto comb{std::string{}};
    BuildComb(0, comb, digits_);
    return mCombs;
}

void Solution::BuildComb(
    size_t const digitIdx_,
    std::string & comb_,
    std::string const & digits_
) {
    auto const combSz{comb_.size()};
    auto const digitsSz{digits_.size()};
    if(combSz == digitsSz) {
        mCombs.emplace_back(comb_);
        return;
    }
    for(auto const chr: mDigitToChrs.at(digits_.at(digitIdx_))) {
        comb_ += chr;
        BuildComb(digitIdx_ + 1, comb_, digits_);
        comb_.pop_back();
    }
}

std::unordered_map<char, std::string> const Solution::mDigitToChrs{
    {'2', "abc"},
    {'3', "def"},
    {'4', "ghi"},
    {'5', "jkl"},
    {'6', "mno"},
    {'7', "pqrs"},
    {'8', "tuv"},
    {'9', "wxyz"}  
};
