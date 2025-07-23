// problem : https://leetcode.com/problems/delete-characters-to-make-fancy-string/description
// submission : https://leetcode.com/problems/delete-characters-to-make-fancy-string/submissions/1708637016
// solution post : https://leetcode.com/problems/delete-characters-to-make-fancy-string/solutions/6995427
//    /c-modern-readable-code-optimal-time-comp-y8jo

// #include <ranges>
// #include <string>
// #include <string_view>

class Solution {
public:
// let 'n' be a length of the given string
// time complexity O(n)
// space complexity O(1)
// runtime 14 ms, beats 93.92 %
    [[nodiscard]]
    std::string makeFancyString(std::string_view const str_) const;
};


std::string Solution::makeFancyString(std::string_view const str_) const {
    namespace views = std::views;
    auto strFancy{std::string{str_.at(0)}};
    auto prevPrevChr{'?'};
    auto prevChr{strFancy.at(0)};
    for(auto const chr: str_ | views::drop(1)) {
        if(prevPrevChr == prevChr && prevChr == chr) {
            continue;
        }
        prevPrevChr = prevChr;
        prevChr = chr; 
        strFancy += chr;
    }
    return strFancy;
}
