// problem : https://leetcode.com/problems/n-queens-ii/description/
// submission : https://leetcode.com/problems/n-queens-ii/submissions/1719648926
// solution post : https://leetcode.com/problems/n-queens-ii/solutions/7032813
//    /c-modern-readable-code-beats-100-runtime-shu1

// #include <array>
// #include <bitset>
// #include <ranges>

namespace Util {
    inline auto constexpr kStartRow{0};
    inline auto constexpr kMaxCell{18};
    inline auto constexpr kDiagonalShift{8};
}

class Solution {
public:
// let 'n' be a length(width) of the given board
// time complexity O(n!)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    int totalNQueens(int const boardSz_);
private:
    using cellsT = std::array<int, 3>;
    using uniqueCellsT = std::bitset<Util::kMaxCell>;
    void Initialize(int const boardSz_);
    int CountQueenPlacements(int const currRow_);
    [[nodiscard]]
    bool IsPlacementInvalid(cellsT cellsToValidate_) const;
    void PlaceQueen(cellsT cellsToOccupie_);
    void RemoveQueen(cellsT cellsToFree_);
    int mBoardSz{};
    uniqueCellsT mDiagonalsInvalid;
    uniqueCellsT mAntiDiagonalsInvalid;
    uniqueCellsT mColsInvalid;
};

int Solution::totalNQueens(int const boardSz_) {
    using namespace Util;
    Initialize(boardSz_);
    auto const queenPlacementsCount{CountQueenPlacements(kStartRow)};
    return queenPlacementsCount;
}

void Solution::Initialize(int const boardSz_) {
    mDiagonalsInvalid.reset();
    mAntiDiagonalsInvalid.reset();
    mColsInvalid.reset();
    mBoardSz = boardSz_;
}

int Solution::CountQueenPlacements(int const currRow_) {
    namespace views = std::views;
    using namespace Util;
    if(currRow_ == mBoardSz) {
        return 1;
    }
    auto placementsCount{0};
    for(auto const col: views::iota(0, mBoardSz)) {
        auto const currDiagonal{currRow_ - col + kDiagonalShift};
        auto const currAntiDiagonal{currRow_ + col};
        auto const cellsToProcess{cellsT{col, currDiagonal, currAntiDiagonal}};
        if(IsPlacementInvalid(cellsToProcess)) {
            continue;
        }
        PlaceQueen(cellsToProcess);
        auto const nextRow{currRow_ + 1};
        placementsCount += CountQueenPlacements(nextRow);
        RemoveQueen(cellsToProcess);
    }
    return placementsCount;
}

bool Solution::IsPlacementInvalid(cellsT cellsToValidate_) const {
    auto const [col, currDiagonal, currAntiDiagonal]{cellsToValidate_};
    auto isPlacementInvalid{
        mColsInvalid.test(col) ||
        mDiagonalsInvalid.test(currDiagonal) ||
        mAntiDiagonalsInvalid.test(currAntiDiagonal)
    };
    return isPlacementInvalid;
}

void Solution::PlaceQueen(cellsT cellsToOccupie_) {
    auto const [col, currDiagonal, currAntiDiagonal]{cellsToOccupie_};
    mColsInvalid.set(col);
    mDiagonalsInvalid.set(currDiagonal);
    mAntiDiagonalsInvalid.set(currAntiDiagonal);
}

void Solution::RemoveQueen(cellsT cellsToFree_) {
    auto const [col, currDiagonal, currAntiDiagonal]{cellsToFree_};
    mColsInvalid.reset(col);
    mDiagonalsInvalid.reset(currDiagonal);
    mAntiDiagonalsInvalid.reset(currAntiDiagonal);
}
