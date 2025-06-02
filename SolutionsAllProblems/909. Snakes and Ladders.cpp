// problem : https://leetcode.com/problems/snakes-and-ladders/description
// submission : https://leetcode.com/problems/snakes-and-ladders/submissions/1652085500
// solution post : https://leetcode.com/problems/snakes-and-ladders/solutions/6805682/
//    c-modern-readable-code-beats-100-runtime-ngls

// #include <algorithm>
// #include <queue>
// #include <vector>
// #include <utility>

namespace Utils {
    auto constexpr kRegularCellVal{-1};
}

class Solution {
public:
    template<typename T_>
    using Arr2T = std::vector<std::vector<T_>>;
// let 'n' by 'n' be a size of the board given
// time complexity O(n^2)
// space complexity O(n^2)
// runtime 0 ms, beats 100.00 %
    int snakesAndLadders(Arr2T<int> const & board_) const;
private:
    std::pair<int, int> FindRowColOfCellVal(
        int const cellVal_,
        int const boardLengthWidth_
    ) const;
};

int Solution::snakesAndLadders(Arr2T<int> const & board_) const {
    using namespace Utils;
    auto const boardLengthWidth{static_cast<int>(board_.size())};
    auto const cellsCount{boardLengthWidth * boardLengthWidth};
    auto minDistances{std::vector<int>(cellsCount + 1, - 1)};
    auto cellValsQ{std::queue<int>{}};
    minDistances.at(1) = 0;
    cellValsQ.emplace(1);
    while(!cellValsQ.empty()) {
        auto const cellValCurr{cellValsQ.front()};
        cellValsQ.pop();
        for(auto cellValNext{cellValCurr + 1};
            cellValNext <= std::min(cellValCurr + 6, cellsCount); ++cellValNext
        ) {
            auto const [rNext, cNext]{FindRowColOfCellVal(cellValNext,
                boardLengthWidth)};
            auto cellValDestination{
                board_.at(rNext).at(cNext) == kRegularCellVal ?
                    cellValNext : board_.at(rNext).at(cNext)};
            if(cellValDestination == cellsCount) {
                return minDistances.at(cellValCurr) + 1;
            }
            if (minDistances.at(cellValDestination) == -1) {
                minDistances.at(cellValDestination) =
                    minDistances.at(cellValCurr) + 1;
                cellValsQ.emplace(cellValDestination);
            }
        }
    }
    return minDistances.at(cellsCount);
}

std::pair<int, int> Solution::FindRowColOfCellVal(
    int const cellVal_,
    int const boardLengthWidth_
) const {
    auto const r{boardLengthWidth_ - 1 -
        ((cellVal_ - 1) / boardLengthWidth_)};
    auto c{0};
    if((boardLengthWidth_ % 2 == 0 && r % 2 == 1) ||
        (boardLengthWidth_ % 2 == 1 && r % 2 == 0)
    ) {
        c = (cellVal_ - 1) % boardLengthWidth_;
    } else {
        c = boardLengthWidth_ - 1 - ((cellVal_ - 1) % boardLengthWidth_);
    }
    return {r, c};
}
