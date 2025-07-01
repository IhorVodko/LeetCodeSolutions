// problem : https://leetcode.com/problems/find-the-original-typed-string-i/description
// submission : https://leetcode.com/problems/find-the-original-typed-string-i/submissions/1682756982
// solution post : https://leetcode.com/problems/find-the-original-typed-string-i/solutions/6907530/
//    c-modern-readable-code-beats-100-runtime-fxqb

// #include <ranges>
// #include <string_view>

class Solution {
public:
// let 'n' be a length of the given string
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    int possibleStringCount(std::string_view const str_) const;
};

int Solution::possibleStringCount(std::string_view const str_) const {
    namespace views = std::views;
    if(str_.empty()) {
        return -1;
    }
    auto strCount{1};
    for(auto && [chr1, chr2]: views::zip(str_, str_ | views::drop(1))) {
        if(chr1 == chr2) {
            ++strCount;
        }
    }
    return strCount;
}
