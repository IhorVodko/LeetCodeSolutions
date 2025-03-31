// problem : https://leetcode.com/problems/maximum-number-of-points-from-grid-queries/description
// submission : https://leetcode.com/problems/maximum-number-of-points-from-grid-queries/submissions/1592196629
// solution post : https://leetcode.com/problems/maximum-number-of-points-from-grid-queries/solutions/6600537/
//     c-modern-readable-code-optimal-time-comp-qwdx

// #include <algorithm>
// #include <functional>
// #include <queue>
// #include <vector>
// #include <utility>

namespace Utility {
    auto constexpr kMoves{std::array<std::pair<int, int>, 4>{{
        {-1, 0}, {0, -1}, {0, 1}, {1, 0}
    }}};
}

// let 'r' be a number of rows in a given grid
// 'c' - number of columns
// 'q' a number of given queries
// time complexity O(q * log(q) + r * c * log(r * c))
// space complexity O(r * c + q)
// runtime 99 ms, beats 44.01 %
class Solution {
public:
    using Arr2T = std::vector<std::vector<int>>;
    std::vector<int> maxPoints(
        Arr2T const & grid_,
        std::vector<int> const & queries_
    ) const {
        using namespace Utility;
        using PQValueT = std::pair<int, std::pair<int, int>>;
        auto const rowsCount(grid_.size());
        auto const colsCount(grid_.at(0).size());    
        auto maxPointsAchieved{std::vector<int>(queries_.size(), 0)};
        auto queriesSorted{std::vector<std::pair<int, int>>{}};
        for(auto idx{0}; idx < queries_.size(); ++idx) {
            queriesSorted.push_back({queries_[idx], idx});
        } 
        std::sort(queriesSorted.begin(), queriesSorted.end());
        auto minHeap{std::priority_queue<PQValueT, std::vector<PQValueT>,
            std::greater<>>{}};
        auto cellsVisited{std::vector<std::vector<bool>>(rowsCount,
            std::vector<bool>(colsCount, false))}; 
        auto pointsTotalCount{0};
        minHeap.push({grid_.at(0).at(0), {0, 0}});
        cellsVisited.at(0).at(0) = true;
        for(auto const [queryVal, queryIdx]: queriesSorted) {
            while(!minHeap.empty() && minHeap.top().first < queryVal) {
                auto const [_, rowCol]{minHeap.top()};
                minHeap.pop();
                auto const [rowCurr, colCurr]{rowCol};
                ++pointsTotalCount;
                for(auto const [rowOffset, colOffset]: kMoves) {
                    auto const rowNext{rowCurr + rowOffset}; 
                    auto const colNext{colCurr + colOffset};
                    if(IsCellWithinGrid({rowNext, colNext}, grid_) &&
                        !cellsVisited.at(rowNext).at(colNext)
                    ) {
                        minHeap.push({grid_.at(rowNext).at(colNext),
                            {rowNext, colNext}});
                        cellsVisited.at(rowNext).at(colNext) = true;
                    }
                }
            }
            maxPointsAchieved.at(queryIdx) = pointsTotalCount;
        }
        return maxPointsAchieved;
    }
private:
    bool IsCellWithinGrid(
        std::pair<int, int> const rowCol,
        Arr2T const & greed
    ) const {
        auto const [row, col]{rowCol};
        auto const rowsCount{greed.size()};
        auto const colsCount{greed.at(0).size()};
        return 0 <= row && row < rowsCount && 0 <= col && col < colsCount;
    }
};
