// problem : https://leetcode.com/problems/trapping-rain-water-ii/description/
// submission : https://leetcode.com/problems/trapping-rain-water-ii/submissions/1514550885
// solution post : https://leetcode.com/problems/trapping-rain-water-ii/solutions/6306508/c-modern-readable-code-optimal-time-comp-e228

// #include <algorithm>
// #include <array>
// #include <priority_queue>
// #include <vector>

// let 'l' be a length of the given matrix 'heightMap'
// 'w' be a width of the given matrix 'heightMap'
// time complexity O(l * w * log(l * w))
// space complexity O(l * w)
// runtime 42 ms, beats 48.07 %
class Solution {
public:
    template<typename T>
    using D1 = std::vector<T>;
    template<typename T>
    using D2 = std::vector<D1<T>>;
    int trapRainWater(D2<int> const & heightMap) {
        Reset();
        rowsCount = heightMap.size();
        colsCount = heightMap.at(0).size();
        visitedCells = D2<bool>(rowsCount, D1<bool>(colsCount, false));
        bounderyCells = std::priority_queue{std::greater{},
            std::vector<std::array<int, 3>>{}};
        InsertFirstAndLastRow(heightMap);
        InsertFirstAndLastCol(heightMap);
        auto totalWaterVolume{0};
        auto cell{decltype(bounderyCells)::value_type{}};
        auto minHeight{-1};
        auto row{-1};
        auto col{-1};
        auto neighbourRow{-1};
        auto neighbourCol{-1};
        auto neighbourHeight{-1};
        while(!bounderyCells.empty()) {
            cell = std::move(bounderyCells.top());
            bounderyCells.pop(); 
            minHeight = cell.at(0);
            row = cell.at(1);
            col = cell.at(2);
            for(auto const & move: moves) {
                neighbourRow = row + move.first;
                neighbourCol = col + move.second;
                if(!IsCellWithinBorders({neighbourRow, neighbourCol}) || 
                    visitedCells.at(neighbourRow).at(neighbourCol)
                ) {
                    continue;
                }
                neighbourHeight = heightMap.at(neighbourRow).at(neighbourCol);
                if(neighbourHeight < minHeight) {
                    totalWaterVolume += minHeight - neighbourHeight;
                    bounderyCells.push({minHeight, neighbourRow, neighbourCol});
                } else {
                    bounderyCells.push({neighbourHeight, neighbourRow, neighbourCol});
                }
                visitedCells.at(neighbourRow).at(neighbourCol) = true;
            }
        }
        return totalWaterVolume; 
    }
    Solution() :
        moves{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}
    {
        Reset();
    }
private:
    bool IsCellWithinBorders(std::pair<int, int> const cell) const {
        return 0 <= cell.first && cell.first < rowsCount &&
            0 <= cell.second && cell.second < colsCount;
    }
    void InsertFirstAndLastRow(D2<int> const & heightMap) {
        for(auto col{0}; col < colsCount; ++col) {
            bounderyCells.push({heightMap.at(0).at(col), 0, col});
            bounderyCells.push({heightMap.at(rowsCount - 1).at(col),
                static_cast<int>(rowsCount - 1), col});
            visitedCells.at(0).at(col) = true;
            visitedCells.at(rowsCount - 1).at(col) = true;
        }
    }
    void InsertFirstAndLastCol(D2<int> const & heightMap) {
        for(auto row{0}; row < rowsCount; ++row) {
            bounderyCells.push({heightMap.at(row).at(0), row, 0});
            bounderyCells.push({heightMap.at(row).at(colsCount - 1), row,
                static_cast<int>(colsCount - 1)});
            visitedCells.at(row).at(0) = true;
            visitedCells.at(row).at(colsCount - 1) = true;
        }
    }
    void Reset() {
        rowsCount = 0;
        colsCount = 0;
        visitedCells.clear();
    }
    int rowsCount;
    int colsCount;
    D1<std::pair<int, int>> moves;
    D2<bool> visitedCells;
    std::priority_queue<std::array<int, 3>, std::vector<std::array<int, 3>>, std::greater<>>
        bounderyCells;
};
