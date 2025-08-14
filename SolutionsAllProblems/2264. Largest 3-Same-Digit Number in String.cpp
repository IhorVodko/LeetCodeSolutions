// problem : https://leetcode.com/problems/largest-3-same-digit-number-in-string/description
// submission : https://leetcode.com/problems/largest-3-same-digit-number-in-string/submissions/1735008761
// solution post : https://leetcode.com/problems/largest-3-same-digit-number-in-string/solutions/7080413/
//    c-modern-readable-code-beats-100-runtime-2r1k

// #include <algorithm>
// #include <ranges>
// #include <string>

namespace Util {
    inline auto constexpr kNumSz{3};
}

class Solution {
public:
// let 'n' be a length of the given string
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    std::string largestGoodInteger(std::string_view digits_) const;
};

std::string Solution::largestGoodInteger(std::string_view digits_) const {
    namespace views = std::views;
    namespace ranges = std::ranges;
    using namespace Util;
    auto validNums{
        digits_ |
        views::slide(kNumSz) |
        views::filter([] (auto const num_) {
            return num_[0] == num_[1] && num_[1] == num_[2];})
    };
    auto maxNumIt{ranges::max_element(
        validNums,
        ranges::less{},
        [] (auto const num_) {return num_[0];}
    )};
    auto const maxNum{
        maxNumIt == validNums.end() ?
        std::string{} :
        std::string(kNumSz, (*maxNumIt)[0])};
    return maxNum;
}
