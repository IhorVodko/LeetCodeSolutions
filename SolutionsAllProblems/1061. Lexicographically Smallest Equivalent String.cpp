// problem : https://leetcode.com/problems/lexicographically-smallest-equivalent-string/description
// submission : https://leetcode.com/problems/lexicographically-smallest-equivalent-string/submissions/1655729432
// solution post : https://leetcode.com/problems/lexicographically-smallest-equivalent-string/solutions/6817230/
//    c-modern-readable-code-beats-100-runtime-xlae

// #include <array>
// #include <string>

namespace Util {
    auto constexpr kAlphabetSize{26};
    auto constexpr kAlphabetBegin{'a'};
}

class Solution {
public:
// let 's' be a length of each of the string1 and string2 given
// 'bs' - length of the base string given
// 'a' - length of the alphabet
// time complexity O((s + bs) * log(a))
// space complexity O(a)
// runtime 0 ms, beats 100.00 %
    std::string smallestEquivalentString(
        std::string const & str1_,
        std::string const & str2_,
        std::string const & strBase_
    );
private:
    int FindChrMin(int const chrAsInt_);
    void DoUnion(
        int chr1AsInt_,
        int chr2AsInt_
    );
    std::array<int, Util::kAlphabetSize> mCharToCharMin;
};

std::string Solution::smallestEquivalentString(
    std::string const & str1_,
    std::string const & str2_,
    std::string const & strBase_
) {
    using namespace Util;
    for(auto i{0}; i < 26 ; ++i) {
        mCharToCharMin.at(i) = i;
    }
    auto const strSz{str1_.size()};
    for(auto i{0}; i < strSz; ++i) {
        DoUnion(str1_.at(i) - kAlphabetBegin, str2_.at(i) - kAlphabetBegin);
    }
    auto strMin{std::string{}};
    for(auto const chr: strBase_) {
        strMin += static_cast<char>((FindChrMin(chr - kAlphabetBegin) +
            kAlphabetBegin));
    }
    return strMin;
}

int Solution::FindChrMin(int const chrAsInt_) {
    if(mCharToCharMin.at(chrAsInt_) == chrAsInt_) {
        return chrAsInt_;
    }
    return mCharToCharMin.at(chrAsInt_) =
        FindChrMin(mCharToCharMin.at(chrAsInt_));
}
void Solution::DoUnion(
    int chr1AsInt_,
    int chr2AsInt_
) {
    chr1AsInt_ = FindChrMin(chr1AsInt_);
    chr2AsInt_ = FindChrMin(chr2AsInt_);
    if(chr1AsInt_ < chr2AsInt_) {
        mCharToCharMin.at(chr2AsInt_) = chr1AsInt_;
    } else {
        mCharToCharMin.at(chr1AsInt_) = chr2AsInt_;
    }
}
