// problem : https://leetcode.com/problems/find-most-frequent-vowel-and-consonant/description
// submission : https://leetcode.com/problems/find-most-frequent-vowel-and-consonant/submissions/1769473410
// solution post : https://leetcode.com/problems/find-most-frequent-vowel-and-consonant/solutions/7186217/
//    c-modern-readable-code-beats-100-runtime-w7h8

// #include <array>
// #include <bitset>
// #include <string>

class Solution {
public:
// let 'n' be a length of the given string
// 's' size of the character set
// time complexity O(n)
// space complexity O(s)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    int maxFreqSum(std::string_view str_);
private:
    [[nodiscard]]
    bool IsVowel(char const chr_) const;
    static int constexpr alphabetSz{26};
    static std::bitset<alphabetSz> constexpr kVowelBitMask{
        0b00000100000100000100010001};
    static char constexpr kChrOffset{'a'};
    std::array<int, alphabetSz> chrCnts;
};

int Solution::maxFreqSum(std::string_view str_) {
    chrCnts.fill(0);
    auto maxVowelCnt{0};
    auto maxConsonentCnt{0};
    for(auto const chr: str_) {
        auto const chrNum{chr - kChrOffset};
        auto const chrCnt{++chrCnts.at(chrNum)};
        auto & chrMaxCnt{IsVowel(chr) ? maxVowelCnt : maxConsonentCnt};
        chrMaxCnt = std::max(chrMaxCnt, chrCnt);
    }
    auto const sum{maxVowelCnt + maxConsonentCnt};
    return sum;
}

bool Solution::IsVowel(char const chr_) const {
    auto const isVowel{kVowelBitMask.test(chr_ - kChrOffset)};
    return isVowel;
}
