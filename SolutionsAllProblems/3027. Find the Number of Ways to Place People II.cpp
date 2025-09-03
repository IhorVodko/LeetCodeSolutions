// problem : https://leetcode.com/problems/find-the-number-of-ways-to-place-people-ii/description
// submission : https://leetcode.com/problems/find-the-number-of-ways-to-place-people-ii/submissions/1758343865
// solution post : https://leetcode.com/problems/find-the-number-of-ways-to-place-people-ii/solutions/7151798/
//    c-modern-readable-code-optimal-time-comp-58pv

// #include <limits>
// #include <ranges>
// #include <vector>

class Solution {
public:
    using pointT = std::vector<int>;
    using pointsT = std::vector<pointT>;
// let 'n' be a count of the given points
// time complexity O(n^2)
// space complexity O(n)
// runtime 327 ms, beats 14.89 %
    [[nodiscard]]
    int numberOfPairs(pointsT & points_) const;
};

int Solution::numberOfPairs(pointsT & points_) const {
    namespace views = std::views;
    namespace ranges = std::ranges;
    using intT = std::numeric_limits<int>;
    auto pairsCount{0};
    ranges::sort(
        points_,
        [] (
            auto const & lhs_,
            auto const & rhs_
        ) {
            auto const lhsX{lhs_.at(0)};
            auto const lhsY{lhs_.at(1)};
            auto const rhsX{rhs_.at(0)};
            auto const rhsY{rhs_.at(1)};
            auto const isLess{
                lhsX < rhsX ||
                (lhsX == rhsX && lhsY > rhsY)
            };
            return isLess;
        }
    );
    auto const pointsSz{points_.size()};
    for(auto const idx1: views::iota(0u, pointsSz - 1)) {
        auto const & point1{points_.at(idx1)};
        auto const x1{point1.at(0)};
        auto const y1{point1.at(1)};
        auto xMin{x1 - 1};
        auto xMax{intT::max()};
        auto yMin{intT::min()};
        auto yMax{y1 + 1};
        for(auto const idx2: views::iota(idx1 + 1, pointsSz)) {
            auto const & point2{points_.at(idx2)};
            auto const x2{point2.at(0)};
            auto const y2{point2.at(1)};
            if( xMin < x2 && x2 < xMax &&
                yMin < y2 && y2 < yMax
            ) {
                ++pairsCount;
                xMin = x2;
                yMin = y2;
            }
        }
    }
    return pairsCount;
}
