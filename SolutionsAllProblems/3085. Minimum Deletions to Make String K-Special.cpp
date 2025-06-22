// problem : https://leetcode.com/problems/minimum-deletions-to-make-string-k-special/description
// submission : https://leetcode.com/problems/minimum-deletions-to-make-string-k-special/submissions/1672800215
// solution post : https://leetcode.com/problems/minimum-deletions-to-make-string-k-special/solutions/6873408/
//    c-modern-readable-code-beats-100-runtime-a8yh

// #include <algorithm>
// #include <array>
// #include <string>
// #include <ranges>

namespace Util {
    inline auto constexpr kChrSetSz{26};
    inline auto constexpr kChrSetStart{'a'};
    inline auto isNumPositive{[] (auto const num_) {return num_ > 0;}};
}

class Solution {
public:
    Solution():
        mChrCounts{std::array<int, Util::kChrSetSz>{}}
    {}
// let 's' be a length of the given string
// 'c' - size of the characte set given
// time complexity O(s + c^2)
// space complexity O(c)
// runtime 0 ms, beats 100.00 %
    int minimumDeletions(
        std::string const & str_,
        int const diffCountMax_
    );
private:
    std::array<int, Util::kChrSetSz> mChrCounts;
};

int Solution::minimumDeletions(
    std::string const & str_,
    int const diffCountMax_
) {
    using namespace Util;
    namespace views = std::views;
    using intT = std::numeric_limits<int>;
    mChrCounts.fill(0);
    for(auto const chr: str_) {
        ++mChrCounts.at(chr - kChrSetStart);
    }
    auto chrDeletedMinCount{intT::max()};
    auto chrCountsPositive{mChrCounts | views::filter(isNumPositive)};
    for(auto const chrCountMin: chrCountsPositive) {
        auto chrDeletedCount{0};
        for(auto const chrCount: chrCountsPositive) {
            if(chrCount < chrCountMin) {
                chrDeletedCount += chrCount;
            } else if(chrCount - chrCountMin > diffCountMax_) {
                chrDeletedCount += chrCount - chrCountMin - diffCountMax_;
            }
        }
        chrDeletedMinCount = std::min(chrDeletedMinCount, chrDeletedCount);
    }
    return chrDeletedMinCount;
}
