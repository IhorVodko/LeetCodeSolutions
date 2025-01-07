// problem : https://leetcode.com/problems/valid-sudoku/submissions/1501098875/
// submission : https://leetcode.com/problems/valid-sudoku/submissions/1501098875
// solution post : https://leetcode.com/problems/valid-sudoku/solutions/6246257/c-modern-readable-code-beats-100-runtime-f746

// #include <bitset>
// #include <vector>

namespace Utility {
    auto constexpr sizeBoard{9Z};
    auto constexpr squaresHorizontalCount{sizeBoard / 3};
    auto constexpr mod{squaresHorizontalCount - 1};
    auto base{'0'};
    auto emptyCellVal{'.'};
}

// since all input parameters have fixed values
// time complexity O(1)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    using BoardT = std::vector<std::vector<char>>;
    bool isValidSudoku(
        BoardT const & board
    ) {
        using namespace Utility;
        Reset();
        for(auto r{0Z}; r < sizeBoard; ++r) {
            rowSet.reset();
            for(auto c{0Z}; c < sizeBoard; ++c) {
                if(!IsValidCellValue(c, board.at(r).at(c))) {
                    return false;
                }
            }
            if(r % squaresHorizontalCount == mod) {
                for(auto & set: squareSets) {
                    set.reset();
                }
            }
        }
        return true;
    }
private:
    using SetT = std::bitset<Utility::sizeBoard + 1>;
    using ArrSetsT = std::array<SetT, Utility::sizeBoard>;
    void Reset() {
        rowSet.reset();
        for(auto & set: colSets) {
            set.reset();
        }
        for(auto & set: squareSets) {
            set.reset();
        }
    }
    bool IsValidCellValue(
        size_t const col,
        char val
    ) {
        using namespace Utility;
        if(val == emptyCellVal) {
            return true;
        }
        val -= base;
        if(squareSets.at(col / squaresHorizontalCount).test(val) ||
            colSets.at(col).test(val) ||
            rowSet.test(val)
        ) {
            return false;
        }
        squareSets.at(col / squaresHorizontalCount).set(val);
        colSets.at(col).set(val);
        rowSet.set(val);
        return true;
    }
    SetT rowSet;
    ArrSetsT colSets;
    ArrSetsT squareSets;
};
