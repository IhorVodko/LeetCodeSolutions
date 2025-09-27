// problem : https://leetcode.com/problems/largest-triangle-area/description/
// submission : https://leetcode.com/problems/largest-triangle-area/submissions/1784068450
// solution post : https://leetcode.com/problems/largest-triangle-area/solutions/7227827/
//    c-modern-readable-code-optimal-time-comp-mego

// import std;

class Solution {
public:
    using pointT = std::vector<int>;

// let 'n' be the given points' count
// time complexity O(n^3)
// space complexity O(1)
// runtime 31 ms, beats 7.28 %
    [[nodiscard]] 
    auto largestTriangleArea(
        std::vector<pointT> const & points_
    ) const -> double;

};

auto Solution::largestTriangleArea(
    std::vector<pointT> const & points_
) const -> double {
    namespace views = std::views;    

    auto const unpack{
        [] (std::vector<int> const & point_) -> std::pair<int, int> {
            return {point_.at(0), point_.at(1)};
        }
    };
    auto const calcArea{
        [&unpack] (
            std::vector<int> const & points1_,
            std::vector<int> const & points2_,
            std::vector<int> const & points3_
        ) {
            auto const [x1, y1]{unpack(points1_)};
            auto const [x2, y2]{unpack(points2_)};
            auto const [x3, y3]{unpack(points3_)};
            auto const square{std::abs(
                0.5 * (
                    x1 * (y2 - y3) +
                    x2 * (y3 - y1) +
                    x3 * (y1 - y2)
                )
            )};
            return square;
        }
    };
    auto const pointsCnt{points_.size()};
    auto maxSquare{0.0};
    for(auto const idx1: views::iota(0u, pointsCnt)) {
        for(auto const idx2: views::iota(0u, pointsCnt)) {
            for(auto const idx3: views::iota(0u, pointsCnt)) {
                auto const currSquare{calcArea(
                    points_.at(idx1),
                    points_.at(idx2),
                    points_.at(idx3)
                )};
                maxSquare = std::max(maxSquare, currSquare);
            }
        }
    }
    return maxSquare;
}
