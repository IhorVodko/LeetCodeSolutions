// problem : https://leetcode.com/problems/painting-a-grid-with-three-different-colors/description
// submission : https://leetcode.com/problems/painting-a-grid-with-three-different-colors/submissions/1638584622
// solution post : https://leetcode.com/problems/painting-a-grid-with-three-different-colors/solutions/6760736/
//    c-modern-readable-code-optimal-time-comp-ol1e

// #include <cmath>
// #include <vector>
// #include <unordered_map>

namespace Utility {
    auto constexpr kMod{1'000'000'007};
}

class Solution {
public:
// let 'r' be a rows count given
// 'c' - columns count given
// time complexity O(3 ^ (2 * c) * r)
// space complexity O(3 ^ (2 * c))
// runtime 49 ms, beats 67.03 %
    int colorTheGrid(
        int const colsCount_,
        int const rowsCount_
    ) const;
private:
    std::unordered_map<int, std::vector<int>> GenerateValidColoredRows(
        int const colsCount_,
        int const maskMax_
    ) const;
    std::unordered_map<int, std::vector<int>> GenerateValidColoredAdjacentRows(
        int const colsCount_,
        std::unordered_map<int, std::vector<int>> const &
            maskToValidColoredRow_
    ) const;
    int CountvalidColoredShcemas(
        int const rowsCount_,
        int const maskMax_,
        std::unordered_map<int, std::vector<int>> const &
            maskToValidColoredRow_,
        std::unordered_map<int, std::vector<int>> const & maskCurrToMaskNext_
    ) const;
};

int Solution::colorTheGrid(
    int const colsCount_,
    int const rowsCount_
) const {
    auto const maskMax{static_cast<int>(std::pow(3, colsCount_))};  
    auto maskToValidColoredRow{
        GenerateValidColoredRows(colsCount_, maskMax)};
    auto maskCurrToMaskNext{
        GenerateValidColoredAdjacentRows(colsCount_, maskToValidColoredRow)};
    auto const validColoredShcemasCountTotal{CountvalidColoredShcemas(
        rowsCount_, maskMax, maskToValidColoredRow, maskCurrToMaskNext)};
    return validColoredShcemasCountTotal;
}

std::unordered_map<int, std::vector<int>> Solution::GenerateValidColoredRows(
    int const colsCount_,
    int const maskMax_
) const {
    auto maskToValidColoredRow{std::unordered_map<int, std::vector<int>>{}};
    for(auto mask{0}; mask < maskMax_; ++mask) {
        auto coloredRow{std::vector<int>{}};
        auto maskCopy{mask};
        for(auto c{0}; c < colsCount_; ++c) {
            coloredRow.emplace_back(maskCopy % 3);
            maskCopy /= 3;
        }
        auto isValidColorSchema{true};
        for(auto c{0}; c < colsCount_ - 1; ++c) {
            if(coloredRow.at(c) == coloredRow.at(c + 1)) {
                isValidColorSchema = false;
                break;
            }
        }
        if(isValidColorSchema) {
            maskToValidColoredRow[mask] = std::move(coloredRow);
        }
    }
    return maskToValidColoredRow;
}

std::unordered_map<int, std::vector<int>>
    Solution::GenerateValidColoredAdjacentRows(
    int const colsCount_,
    std::unordered_map<int, std::vector<int>> const & maskToValidColoredRow_
) const {
    auto maskCurrToMaskNext{std::unordered_map<int, std::vector<int>>{}};
    for(auto const & [mask1, row1]: maskToValidColoredRow_) {
        for(auto const & [mask2, row2] : maskToValidColoredRow_) {
            auto noColsSameColor{true};
            for(auto c{0}; c < colsCount_; ++c) {
                if(row1.at(c) == row2.at(c)) {
                    noColsSameColor = false;
                    break;
                }
            } 
            if(noColsSameColor) {
                maskCurrToMaskNext[mask1].emplace_back(mask2);
            }
        }
    }
    return maskCurrToMaskNext;
}

int Solution::CountvalidColoredShcemas(
    int const rowsCount_,
    int const maskMax_,
    std::unordered_map<int, std::vector<int>> const & maskToValidColoredRow_,
    std::unordered_map<int, std::vector<int>> const & maskCurrToMaskNext_
) const {
    using namespace Utility;
    auto dpCurr{std::vector<int>(maskMax_, 0)};
    for(auto const & [mask, _]: maskToValidColoredRow_) {
        dpCurr.at(mask) = 1;
    }
    for(auto r{1}; r < rowsCount_; ++r) {
        auto dpNext{std::vector<int>(maskMax_, 0)};
        for(auto const & [mask2, _]: maskToValidColoredRow_) {
            for(auto const mask1 : maskCurrToMaskNext_.at(mask2)) {
                dpNext.at(mask2) += dpCurr.at(mask1);
                dpNext.at(mask2) %= kMod;
            }
        }
        dpCurr = std::move(dpNext);
    }
    auto validColoredShcemasCountTotal{0};
    for(auto const validColoredShcemasCountCurr: dpCurr) {
        validColoredShcemasCountTotal += validColoredShcemasCountCurr;
        validColoredShcemasCountTotal %= kMod;
    }
    return validColoredShcemasCountTotal;
}
