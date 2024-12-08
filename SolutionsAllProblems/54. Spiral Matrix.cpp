// problem : https://leetcode.com/problems/spiral-matrix/description/
// submission : https://leetcode.com/problems/spiral-matrix/submissions/1473496390
// solution post : https://leetcode.com/problems/spiral-matrix/solutions/6125922/c-modern-readable-code-beats-100-runtime


// #include <vector>
// #include <unordered_map>


class Solution {
public:
    // let 'n' by 'm' be dimensions of an input 2-D array
    // time complexity O(n * m)
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
public:
    std::vector<int> spiralOrder(
        std::vector<std::vector<int>> & matrix
    ) {
        mx = std::move(matrix);
        rows = mx.size();
        cols = mx.front().size();
        mxSize = rows * cols;
        result.reserve(rows * cols);
        result.emplace_back(mx.at(row).at(col));
        mx.at(row).at(col) = visited; 
        while(result.size() < mxSize) {
            move(Right);
            move(Down);
            move(Left);
            move(Up);
        }
        return result;
    }
private:
    enum class Direction {Right, Down, Left, Up};
    using enum Direction;
    void move(
        Direction const direction
    ) {
        rowDelta = directions.at(direction).first;
        colDelta = directions.at(direction).second;
        while(0 <= row + rowDelta && row + rowDelta < rows && 
            0 <= col + colDelta && col + colDelta < cols && 
            mx.at(row + rowDelta).at(col + colDelta) != visited
        ) {
            row += rowDelta;
            col += colDelta;
            result.emplace_back(mx.at(row).at(col));
            mx.at(row).at(col) = visited;
        }
    }
    static int visited;
    int row{0};
    int col{0};
    int rowDelta{0};
    int colDelta{0};
    int rows{0};
    int cols{0};
    int mxSize{0};
    std::vector<int> result;
    std::vector<std::vector<int>> mx;
    std::unordered_map<Direction, std::pair<int, int>> directions{
        {Right, {0, 1}}, {Down, {1, 0}}, {Left, {0, -1}}, {Up, {-1, 0}}
    };

};

int Solution::visited{101};
};
