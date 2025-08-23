// problem : https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-i/submissio
// submission : https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-i/description
// solution post : https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-i/solutions/7113617/
//    c-modern-readable-code-optimal-time-comp-vjuu

// #include <algorithm>
// #include <ranges>
// #include <vector>

class Solution {
public:
    using mxT = std::vector<std::vector<int>>;
// let 'n' by 'm' be a size of the given matrix
// time complexity O(n * m)
// space complexity O(1)
// runtime 242 ms, beats 90.63 %
    [[nodiscard]]
    int minimumArea(mxT const & mx_) const;
};

int Solution::minimumArea(mxT const & mx_) const {
    namespace views = std::views;
    using intT = std::numeric_limits<int>;
    if(mx_.empty() || mx_.at(0).empty()) {
        return 0;
    }
    auto const rowsCount{std::ssize(mx_)};
    auto const colsCount{std::ssize(mx_.at(0))};
    auto leftIdx{intT::max()};
    auto rightIdx{intT::min()};
    auto upperIdx{intT::max()};
    auto lowerIdx{intT::min()};
    for(auto const rowIdx: views::iota(0, rowsCount)) {
        for(auto const colIdx: views::iota(0, colsCount)) {
            if(mx_.at(rowIdx).at(colIdx) == 1) {
                leftIdx = std::min(leftIdx, colIdx);
                rightIdx = std::max(rightIdx, colIdx);
                upperIdx = std::min(upperIdx, rowIdx);
                lowerIdx = std::max(lowerIdx, rowIdx);
            }
        }
    } 
    auto const rectangSide1{rightIdx - leftIdx + 1};
    auto const rectangSide2{lowerIdx - upperIdx + 1};
    auto const rectangSquare{rectangSide1 * rectangSide2};
    return rectangSquare;
}
