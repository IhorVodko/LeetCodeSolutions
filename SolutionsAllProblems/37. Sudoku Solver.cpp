// problem : https://leetcode.com/problems/sudoku-solver/description/
// submission : https://leetcode.com/problems/sudoku-solver/submissions/1733903540
// solution post : https://leetcode.com/problems/sudoku-solver/solutions/7076379/
//    c-modern-readable-code-optimal-time-comp-dwn3

// #include <array>
// #include <bitset>
// #include <vector>

namespace Util {
    inline auto constexpr kEmptyCell{'.'};
    inline auto constexpr kFirstNumChr{'0'};
    inline auto constexpr kRowColsSz{9};
    inline auto constexpr kMinNum{1};
    inline auto constexpr kMaxNum{9};
    inline auto constexpr kStartR{0};
    inline auto constexpr kStartC{0};
    inline auto constexpr kBoxRowsColsSz{3};
}

class Solution {
public:
    using boardT = vector<vector<char>>;
    void solveSudoku(boardT & board_);
private:
    using mxUniqueNumsT = std::array<
        std::bitset<Util::kRowColsSz + 1>,
        Util::kRowColsSz + 1>;
// let 'r' be a number of rows of the board
// 'c' - nubmer of columns
// time complexity O((c!)^r)
// space complexity O(r * c)
// runtime 103 ms, beats 93.88 %
    [[nodiscard]]
    int CalculateBoxIdx(
        int const r_,
        int const c_
    ) const;
    [[nodiscard]]
    bool IsValidPlacement(
        int const num_,
        int const r_,
        int const c_
    ) const;
    void PlaceNum(
        int const num_,
        int const r_,
        int const c_
    );
    void DisplaceNum(
        int const num_,
        int r_,
        int c_
    );
    void PlaceNextNum(
        int const r_,
        int const c_
    );
    void Backtrack(
        int const r_,
        int const c_
    );
    void Reset(boardT & board_);
    mxUniqueNumsT mRowNumsUnique{};
    mxUniqueNumsT mColNumsUnique{};
    mxUniqueNumsT mBoxNumsUnique{};
    std::optional<std::reference_wrapper<boardT>> mBoard;
    bool mIsSolved{};
};

void Solution::solveSudoku(boardT & board_) {
    using namespace Util;
    namespace views = std::views;
    Reset(board_);
    for(auto const r: views::iota(0, kRowColsSz)) {
        for(auto const c: views::iota(0, kRowColsSz)) {
            auto const numChr = mBoard->get().at(r).at(c);
            if (numChr != kEmptyCell) {
                auto const num{int{numChr - kFirstNumChr}};
                PlaceNum(num, r, c);
            }
        }
    }
    Backtrack(kStartR, kStartC);
}

int Solution::CalculateBoxIdx(
    int const r_,
    int const c_
) const {
    using namespace Util;
    auto const boxIdx{
        (r_ / kBoxRowsColsSz) *
        kBoxRowsColsSz +
        c_ / kBoxRowsColsSz};
    return boxIdx;
}

bool Solution::IsValidPlacement(
    int const num_,
    int const r_,
    int const c_
) const {
    auto const boxIdx{CalculateBoxIdx(r_, c_)};
    auto const isValid{
        !mRowNumsUnique.at(r_).test(num_) &&
        !mColNumsUnique.at(c_).test(num_) &&
        !mBoxNumsUnique.at(boxIdx).test(num_)};
    return isValid;
}

void Solution::PlaceNum(
    int const num_,
    int const r_,
    int const c_
) {
    using namespace Util;
    auto const boxIdx{CalculateBoxIdx(r_, c_)};
    mRowNumsUnique.at(r_).set(num_);
    mColNumsUnique.at(c_).set(num_);
    mBoxNumsUnique.at(boxIdx).set(num_);
    auto const newNumChr{static_cast<char>(num_ + kFirstNumChr)};
    auto & oldNumChr{mBoard->get().at(r_).at(c_)};
    oldNumChr = newNumChr;
}

void Solution::DisplaceNum(
    int const num_,
    int r_,
    int c_
) {
    using namespace Util;
    auto const boxIdx{CalculateBoxIdx(r_, c_)};
    mRowNumsUnique.at(r_).reset(num_);
    mColNumsUnique.at(c_).reset(num_);
    mBoxNumsUnique.at(boxIdx).reset(num_);
    auto & oldNumChr{mBoard->get().at(r_).at(c_)};
    oldNumChr = kEmptyCell;
}

void Solution::PlaceNextNum(
    int const r_,
    int const c_
) {
    using namespace Util;
    if ((c_ == kRowColsSz - 1) && (r_ == kRowColsSz - 1)) {
        mIsSolved = true;
    } else {
        if (c_ == kRowColsSz - 1) {
            auto const nextR{r_ + 1};
            Backtrack(nextR, 0);
        } else {
            auto const nextC{c_ + 1};
            Backtrack(r_, nextC);
        }
    }
}

void Solution::Backtrack(
    int const r_,
    int const c_
) {
    namespace views = std::views;
    using namespace Util;
    if (auto const currCellVal{mBoard->get().at(r_).at(c_)};
        currCellVal == kEmptyCell
    ) {
        for(auto const num: views::iota(kMinNum, kMaxNum + 1)) {
            if (IsValidPlacement(num, r_, c_)) {
                PlaceNum(num, r_, c_);
                PlaceNextNum(r_, c_);
                if (!mIsSolved) {
                    DisplaceNum(num, r_, c_);
                }
            }
        }
    } else {
        PlaceNextNum(r_, c_);
    }
}

void Solution::Reset(boardT & board_) {
    mBoard = board_;
    auto uniqueNumsArr{std::array<
        std::reference_wrapper<mxUniqueNumsT>,
        3>{
            mRowNumsUnique,
            mColNumsUnique,
            mBoxNumsUnique}};
    for(auto uniqueNums: uniqueNumsArr) {
        for(auto & nums: uniqueNums.get()) {
            nums.reset();
        }
    }
};
