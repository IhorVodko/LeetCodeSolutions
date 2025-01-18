// problem : https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/description/
// submission : https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/submissions/1512863442
// solution post : https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/solutions/6300005/c-modern-readable-code-optimal-time-comp-td5d

// #include <deque>
// #include <limits>
// #include <vector>
// #include <unordered_map>

// let 'r' be a rows count in the given grid
// 'c' - columns count in the given grid
// time complexity O(r * c)
// space complexity O(r * c)
// runtime 15 ms, beats 78.06 %
class Solution {
public:
    using MxT = std::vector<std::vector<int>>;
    int minCost(MxT const & grid) const {
        auto const rows{grid.size()};
        auto const cols{grid.at(0).size()};
        auto minCosts{MxT{rows, std::vector<int>(cols,
            std::numeric_limits<int>::max())}};
        auto positions{std::deque<std::pair<size_t, size_t>>{}};
        positions.push_front({0, 0});
        minCosts.at(0).at(0) = 0;
        auto row{0};
        auto col{0};
        auto nextRow{-1};
        auto nextCol{-1};
        auto newCost{0};
        auto moveCost{0};
        while(!positions.empty()) {
            row = positions.front().first;
            col = positions.front().second;
            positions.pop_front();
            for(auto const & [dir, rowCol] : dirs) {
                nextRow = row + rowCol.first;
                nextCol = col + rowCol.second;
                if(!IsValidPosition(nextRow, nextCol, rows, cols)) {
                    continue;
                }
                auto & oldCost{minCosts.at(nextRow).at(nextCol)};
                moveCost = (grid.at(row).at(col) == dir) ? 0 : 1;
                newCost = minCosts.at(row).at(col) + moveCost;
                if(newCost < oldCost) {
                    oldCost = newCost;
                    moveCost == 0 ? positions.push_front({nextRow, nextCol}) :
                        positions.push_back({nextRow, nextCol}); 
                } 
            }
        }
        return minCosts.at(rows - 1).at(cols - 1); 
    }
    Solution() : 
        dirs{{1, {0, 1}}, {2, {0, -1}}, {3, {1, 0}}, {4, {-1, 0}}}
    {} 
private:
    bool IsValidPosition(
        int const row,
        int const col,
        size_t const rows,
        size_t const cols
    ) const {
        return 0 <= row && row < rows && 0 <= col && col < cols;
    }
    std::unordered_map<size_t, std::pair<int, int>> dirs;
};
