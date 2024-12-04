// problem : https://leetcode.com/problems/diagonal-traverse/description/
// submission : https://leetcode.com/problems/diagonal-traverse/submissions/1470415299 
// solution post : https://leetcode.com/problems/diagonal-traverse/solutions/6114016/c-modern-readable-code-beats-100-runtime


// #include <vector>


class Solution {
public:
    using mxT = std::vector<std::vector<int>>;
    // let 'n' and 'm' be a given matrix dimensions
    // time complexity O(n * m)
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
    std::vector<int> findDiagonalOrder(
        mxT const & mx
    ) {
        using D = Direction;
        auto rows{mx.size()};
        auto cols{mx.front().size()};
        if(rows == 1 && cols == 1) {
            return mx.front(); 
        }
        result.reserve(rows * cols);
        for(auto r{int{0}}, c{int{0}}; r < rows && c < cols;) {
            if(direction == Direction::UP) {
                moveUpDiagonal(r, c, result, mx, cols);
            } else {
                moveDownDiagonal(r, c, result, mx, rows);
            }
            direction = direction == D::DOWN ? D::UP : D::DOWN;
        }
        return result;
    }
private:
    void moveUpDiagonal(
        int & r,
        int & c,
        std::vector<int> & result,
        mxT const & mx,
        int const cols
    ) {
        do{
            result.emplace_back(mx.at(r).at(c));
            if(r - 1 < 0 || c + 1 >= cols) {
                break;
            }
            --r;
            ++c;
        } while(true);
        c < cols - 1 ? ++c : ++r; 
    }
    void moveDownDiagonal(
        int & r,
        int & c,
        std::vector<int> & result,
        mxT const & mx,
        int const rows
    ) {
        do{
            result.emplace_back(mx.at(r).at(c));
            if(r + 1 >= rows || c - 1 < 0) {
                break;
            }
            ++r;
            --c;
        } while(true);
        r < rows - 1 ? ++r : ++c;
    }
    enum class Direction { UP, DOWN };
    Direction direction;
    std::vector<int> result;
};
