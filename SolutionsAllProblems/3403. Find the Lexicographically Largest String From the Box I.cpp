// problem : https://leetcode.com/problems/find-the-lexicographically-largest-string-from-the-box-i/description/ 
// submission : https://leetcode.com/problems/find-the-lexicographically-largest-string-from-the-box-i/submissions/
//    1653789814
// solution post : https://leetcode.com/problems/find-the-lexicographically-largest-string-from-the-box-i/solutions/
//    6810858/c-modern-readable-code-beats-100-runtime-ncp0

// #include <algorithm>
// #include <string>

class Solution {
public:
// let 'n' be a length of the given string
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    std::string answerString(
        std::string const & str_,
        int const splitCount_ 
    ) const;
private:
    std::pair<int, int> FindLastSubstrFirstLast(
        std::string const & str_
    ) const;
};

std::string Solution::answerString(
    std::string const & str_,
    int const splitCount_ 
) const {
    if(splitCount_ == 1) {
        return str_;
    }
    auto const [first, last]{FindLastSubstrFirstLast(str_)};
    auto strSz{str_.size()};
    auto lastSubstrSz{last - first};
    auto const substrSzUpperLimit{strSz - (splitCount_ - 1)};
    auto const substrMaxSz{std::min(lastSubstrSz,
        static_cast<int>(substrSzUpperLimit))};
    auto const substrMax{str_.substr(first, substrMaxSz)};
    return substrMax;
}

std::pair<int, int> Solution::FindLastSubstrFirstLast(
    std::string const & str_
) const {
    auto i1{0};
    auto i2{1};
    auto const strSz{str_.size()};
    while(i2 < strSz) {
        auto i3{0};
        while(i2 + i3 < strSz && str_.at(i1 + i3) == str_.at(i2 + i3)) {
            ++i3;
        }
        if(i2 + i3 < strSz && str_.at(i1 + i3) < str_.at(i2 +i3)) {
            auto i4{i1};
            i1 = i2;
            i2 = std::max(i2 + 1, i4 + i3 + 1);
        } else {
            i2 = i2 + i3 + 1;
        }
    }
    return {i1, i1 + (strSz - i1)};
}
