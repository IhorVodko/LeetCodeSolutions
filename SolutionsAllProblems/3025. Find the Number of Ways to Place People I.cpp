// problem : https://leetcode.com/problems/find-the-number-of-ways-to-place-people-i/description
// submission : https://leetcode.com/problems/find-the-number-of-ways-to-place-people-i/submissions/1757115541
// solution post : https://leetcode.com/problems/find-the-number-of-ways-to-place-people-i/solutions/7148342/
//    c-modern-readable-code-by-cyberartist-0zud

// #include <ranges>
// #include <vector>

// let 'n' be a count of the given points
// time complexity O(n^3)
// space complexity O(1)
// runtime 145 ms, beats 8.89 %

class Solution {
public:
    using pointT = std::vector<int>;
    using pointsT = std::vector<pointT>;
// let 'n' be a count of the given points
// time complexity O(n^3)
// space complexity O(1)
// runtime 145 ms, beats 8.89 %
    [[nodiscard]]
    int numberOfPairs(pointsT const & points_) const;
private:
    [[nodiscard]]
    bool IsPointsValid(
        pointT const & point1_,
        pointT const & point2_
    ) const;
    [[nodiscard]]
    bool IsPointInside(
        pointT const & point1_,
        pointT const & point2_,
        pointT const & pointToTest_
    ) const;
};

int Solution::numberOfPairs(pointsT const & points_) const {
    namespace views = std::views;
    auto pairsCount{0};
    auto const pointsSz{points_.size()};
    if(pointsSz == 2) {
        if( IsPointsValid(points_.at(0), points_.at(1)) ||
            IsPointsValid(points_.at(1), points_.at(0))
        ) {
            ++pairsCount;
        }
        return pairsCount;
    }
    for(auto const idx1: views::iota(0u, pointsSz)) {
        auto const & point1{points_.at(idx1)};
        auto const x1{point1.at(0)};
        auto const y1{point1.at(1)};
        for(auto const idx2: views::iota(0u, pointsSz)) {
            auto const point2{points_.at(idx2)};
            auto const x2{point2.at(0)};
            auto const y2{point2.at(1)};
            if( idx1 == idx2 || !IsPointsValid(point1, point2)) {
                continue;
            }
            auto isPointInside{false};
            for(auto const idx3: views::iota(0u, pointsSz)) {
                if(idx3 == idx1 || idx3 == idx2) {
                    continue;
                }
                if(IsPointInside(point1, point2, points_.at(idx3))) {
                    isPointInside = true;
                    break;
                }
            }
            if(!isPointInside) {
                ++pairsCount;
            }
        }
    }
    return pairsCount;
}

bool Solution::IsPointInside(
    pointT const & point1_,
    pointT const & point2_,
    pointT const & pointToTest_
) const {
    auto const x1{point1_.at(0)};
    auto const y1{point1_.at(1)};
    auto const x2{point2_.at(0)};
    auto const y2{point2_.at(1)};
    auto const xToTest{pointToTest_.at(0)};
    auto const yToTest{pointToTest_.at(1)};
    auto const isXInside{xToTest >= x1 && xToTest <= x2};
    auto const isYInside{yToTest <= y1 && yToTest >= y2};
    auto const  isPointInside{isXInside && isYInside};
    return isPointInside; 
}

bool Solution::IsPointsValid(
    pointT const & point1_,
    pointT const & point2_
) const {
    auto const x1{point1_.at(0)};
    auto const y1{point1_.at(1)};
    auto const x2{point2_.at(0)};
    auto const y2{point2_.at(1)};
    auto const isPointsValid{x1 <= x2 && y1 >= y2};
    return isPointsValid;
}
