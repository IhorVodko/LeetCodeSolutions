// problem : https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-ii/description
// submission : https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-ii/submissions/1745599879
// solution post : https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-ii/solutions/7113895/
//    c-modern-readable-code-by-cyberartist-d5cg

// #include <algorithm>
// #include <limits>
// #include <ranges>
// #include <vector>

class Solution {
public:
    using mxT = std::vector<std::vector<int>>;
// let 'n' by 'm' be a size of the given matrix
// time complexity O(n^2 * m^2)
// space complexity O(n * m)
// runtime 277 ms, beats 8.33 %
    [[nodiscard]]
    int minimumSum(mxT const & mx_) const;
private:
    [[nodiscard]]
    int FindMinRectSquare(
        mxT const & mx_,
        int const minRowIdx_,
        int const maxRowIdx_,
        int const minColIdx_,
        int const maxColIdx_
    ) const;
    [[nodiscard]]
    mxT RotateMx(mxT const & mx_) const;
    [[nodiscard]]
    int FindMinSumOf3RectSquares(mxT const & mx_) const;
};

int Solution::minimumSum(mxT const & mx_) const {
    auto const rotatedMx{RotateMx(mx_)};
    auto minSumOf3RectSquares{FindMinSumOf3RectSquares(mx_)};
    auto minSumOf3RectSquaresRotated{FindMinSumOf3RectSquares(rotatedMx)};
    minSumOf3RectSquares = std::min(
        minSumOf3RectSquares,
        minSumOf3RectSquaresRotated
    );
    return minSumOf3RectSquares;
}

int Solution::FindMinRectSquare(
    mxT const & mx_,
    int const minRowIdx_,
    int const maxRowIdx_,
    int const minColIdx_,
    int const maxColIdx_
) const {
    namespace views = std::views;
    using intT = std::numeric_limits<int>;
    auto rectUpperIdx{static_cast<int>(mx_.size())};
    auto rectLowerIdx{0};
    auto rectLeftIdx{static_cast<int>(mx_.at(0).size())};
    auto recRighttIdx{0};
    for(auto const rowIdx: views::iota(minRowIdx_, maxRowIdx_ + 1)) {
        for(auto const colIdx: views::iota(minColIdx_, maxColIdx_ + 1)) {
            if(mx_.at(rowIdx).at(colIdx) == 1) {
                rectUpperIdx = std::min(rectUpperIdx, rowIdx);
                rectLeftIdx = std::min(rectLeftIdx, colIdx);
                rectLowerIdx = std::max(rectLowerIdx, rowIdx);
                recRighttIdx = std::max(recRighttIdx, colIdx);
            }
        }
    }
    if(rectUpperIdx <= rectLowerIdx) {
        auto const rectSide1{rectLowerIdx - rectUpperIdx + 1};
        auto const rectSide2{recRighttIdx - rectLeftIdx + 1};
        auto const rectMinSquare{rectSide1 * rectSide2};
        return rectMinSquare;
    }
    auto const rectMinSquare{intT::max() / 3};
    return rectMinSquare;
}

Solution::mxT Solution::RotateMx(mxT const & mx_) const {
    namespace views = std::views;
    auto const rowsCount{static_cast<int>(mx_.size())};
    auto const colsCount{static_cast<int>(mx_.at(0).size())};
    auto rotatedMx{mxT(colsCount, std::vector<int>(rowsCount, 0))};
    for(auto const rowIdx: views::iota(0, rowsCount)) {
        for(auto const colIdx: views::iota(0, colsCount)) {
            rotatedMx.at(colsCount - colIdx - 1).at(rowIdx) =
                mx_.at(rowIdx).at(colIdx);
        }
    }
    return rotatedMx;
}

int Solution::FindMinSumOf3RectSquares(mxT const & mx_) const {
    auto const rowsCount{static_cast<int>(mx_.size())};
    auto const colsCount{static_cast<int>(mx_.at(0).size())};
    auto minSumOf3RectSquares{rowsCount * colsCount};
    for(auto const rowIdx: views::iota(0, rowsCount - 1)) {
        for(auto const colIdx: views::iota(0, colsCount - 1)) {
            auto rectSqaure1{FindMinRectSquare(
                mx_,
                0,
                rowIdx,
                0,
                colsCount - 1
            )};
            auto rectSqaure2{FindMinRectSquare(
                mx_,
                rowIdx + 1,
                rowsCount - 1,
                0,
                colIdx
            )};
            auto rectSqaure3{FindMinRectSquare(
                mx_,
                rowIdx + 1,
                rowsCount - 1,
                colIdx + 1,
                colsCount - 1
            )};
            auto sumOf3RectSquares{
                rectSqaure1 +
                rectSqaure2 +
                rectSqaure3
            };
            minSumOf3RectSquares = std::min(
                minSumOf3RectSquares,
                sumOf3RectSquares
            );
            rectSqaure1 = FindMinRectSquare(mx_, 0, rowIdx, 0, colIdx);
            rectSqaure2 = FindMinRectSquare(
                mx_, 0, rowIdx, colIdx + 1, colsCount - 1);
            rectSqaure3 = FindMinRectSquare(
                mx_, rowIdx + 1, rowsCount - 1, 0, colsCount - 1);
            sumOf3RectSquares = rectSqaure1 + rectSqaure2 + rectSqaure3;
            minSumOf3RectSquares = std::min(
                minSumOf3RectSquares,
                sumOf3RectSquares
            );
        }
    }
    for(auto const rowIdx: views::iota(0, rowsCount - 2)) {
        for(auto const colIdx: views::iota(rowIdx + 1, rowsCount - 1)) {
            auto const rectSquare1{FindMinRectSquare(
                mx_, 0, rowIdx, 0, colsCount - 1)};
            auto const rectSquare2{FindMinRectSquare(
                mx_, rowIdx + 1, colIdx, 0, colsCount - 1)};
            auto const rectSquare3{FindMinRectSquare(
                mx_, colIdx + 1, rowsCount - 1, 0, colsCount - 1)};
            auto const sumOf3RectSquares{
                rectSquare1 +
                rectSquare2 +
                rectSquare3
            };
            minSumOf3RectSquares = std::min(
                minSumOf3RectSquares,
                sumOf3RectSquares
            );
        }
    } 
    return minSumOf3RectSquares;
}
