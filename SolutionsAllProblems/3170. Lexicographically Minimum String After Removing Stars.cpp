// problem : https://leetcode.com/problems/lexicographically-minimum-string-after-removing-stars/description/
// submission : https://leetcode.com/problems/lexicographically-minimum-string-after-removing-stars/submissions/
//    1658120064
// solution post : https://leetcode.com/problems/lexicographically-minimum-string-after-removing-stars/
//    solutions/6824624/c-modern-readable-code-beats-100-runtime-rw7i

// #include <set>
// #include <string>
// #include <vector>

namespace Util {
    auto constexpr kStar{'*'};
}

class Solution {
public:
// let 'n' be a length of the given string
// 'c' - given character set size
// time complexity O(n * log2(c))
// space complexity O(n + c)
// runtime  336 ms, beats 17.56 %
    std::string clearStars(std::string str_) const;
};

std::string Solution::clearStars(std::string str_) const {
    using namespace Util;
    auto chrToIdxs{std::vector<std::stack<int>>(26, std::stack<int>{})};
    auto chrs{std::set<char>{}};
    auto const strSz{str_.size()};
    auto isStarFound{false};
    for(auto i{0}; i < strSz; ++i) {
        auto const chr{str_.at(i)};
        if(chr == kStar) {
            isStarFound  = true;
            if(chrs.empty()) {
                continue;
            }
            auto chrMin{*chrs.begin()};
            auto & minCharIdxs{chrToIdxs.at(chrMin - 'a')};
            if(minCharIdxs.empty()) {
                continue;
            }
            str_.at(minCharIdxs.top()) = kStar;
            minCharIdxs.pop();
            if(minCharIdxs.empty()) {
                chrs.erase(chrMin);
            }
        } else {
            chrToIdxs.at(chr - 'a').emplace(i);
            chrs.emplace(chr);
        }
    }
    if(chrs.empty()) {
        return isStarFound ? "" : str_;
    }
    auto strMin{std::string{}};
    for(auto const chr: str_) {
        if(chr != kStar) {
            strMin.push_back(chr);
        }
    }
    return strMin;
}
