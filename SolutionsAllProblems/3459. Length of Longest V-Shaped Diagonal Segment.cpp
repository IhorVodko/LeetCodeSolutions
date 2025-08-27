// problem : https://leetcode.com/problems/length-of-longest-v-shaped-diagonal-segment/description
// submission : https://leetcode.com/problems/length-of-longest-v-shaped-diagonal-segment/submissions/1750363711
// solution post : https://leetcode.com/problems/length-of-longest-v-shaped-diagonal-segment/solutions/7128464/
//    c-modern-readable-code-optimal-time-comp-lgk2

// #include <algorithm>
// #include <array>
// #include <ranges>
// #include <vector>

class Solution {
public:
    using mxT = std::vector<std::vector<int>>;
// let 'r' by 'c' be a size of the given matrix
// time complexity O(r * c)
// space complexity O(r * c)
// runtime 277 ms, beats 82.35 %
    [[nodiscard]]
    int lenOfVDiagonal(mxT const & mx_);
private:
    using moveT = std::pair<int, int>;
    using movesT = std::array<moveT, 4>;
    using arr1dT = std::array<int, 2>;
    using arr2dT = std::array<arr1dT, 4>;
    using arr3dT = std::vector<arr2dT>;
    using arr4dT = std::vector<arr3dT>;
    enum MoveType {forward, turn};
    [[nodiscard]]
    int DoDfs(
        int const r_,
        int const c_,
        int const move_,
        MoveType const moveType_,
        int const targetCellVal_,
        mxT const & mx_
    );
    [[nodiscard]]
    bool IsValidCell(
        mxT const & mx_,
        int const r_,
        int const c_,
        int const targetCellVal_
    ) const;
    static movesT constexpr mMoves{{{1, 1}, {1, -1}, {-1, -1}, {-1, 1}}};
    arr4dT mMemo;

};

int Solution::lenOfVDiagonal(mxT const & mx_) {
    namespace views = std::views;
    auto const rCount{std::ssize(mx_)};
    auto const cCount{std::ssize(mx_.at(0))};
    mMemo = arr4dT(rCount, arr3dT(cCount, arr2dT{{
            {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}
    }}));
    auto maxLength{0};
    for(auto const r: views::iota(0, rCount)) {
        for(auto const c: views::iota(0, cCount)) {
            if(mx_.at(r).at(c) == 1) {
                for(auto const move_: views::iota(0, 4)) {
                    maxLength = std::max(
                        maxLength,
                        DoDfs(r, c, move_, MoveType::turn, 2, mx_) + 1);
                }
            }
        }
    }
    return maxLength;
}

int Solution::DoDfs(
    int const r_,
    int const c_,
    int const move_,
    MoveType const moveType_,
    int const targetCellVal_,
    mxT const & mx_
) {
        auto const rCount{std::ssize(mx_)};
        auto const cCount{std::ssize(mx_.at(0))};
        auto const nextR{r_ + mMoves.at(move_).first};
        auto const nextC{c_ + mMoves.at(move_).second};
        if(!IsValidCell(mx_, nextR, nextC, targetCellVal_)) {
            return 0;
        }
        if(mMemo.at(nextR).at(nextC).at(move_).at(moveType_) != -1) {
            return mMemo.at(nextR).at(nextC).at(move_).at(moveType_);
        }
        auto const nextCellVall{2 - targetCellVal_};
        auto maxStep{DoDfs(
            nextR, nextC, move_, moveType_, nextCellVall, mx_)};
        if(moveType_) {
            auto const nextMoveIdx{(move_ + 1) % 4};
            maxStep = std::max(
                maxStep,
                DoDfs(
                    nextR,
                    nextC,
                    nextMoveIdx,
                    MoveType::forward,
                    nextCellVall,
                    mx_
                )
            );
        }
        auto const maxLength{maxStep + 1};
        mMemo.at(nextR).at(nextC).at(move_).at(moveType_) = maxLength;
        return maxLength;
}

bool Solution::IsValidCell(
    mxT const & mx_,
    int const r_,
    int const c_,
    int const targetCellVal_
) const {
    auto const rCount{std::ssize(mx_)};
    auto const cCount{std::ssize(mx_.at(0))};
    auto isValidCell{
        0 <= r_ && r_ < rCount &&
        0 <= c_ && c_ < cCount};
    if(isValidCell) {
        auto const currCellVal{mx_.at(r_).at(c_)};
        isValidCell = currCellVal == targetCellVal_;
    }
    return isValidCell;
}
