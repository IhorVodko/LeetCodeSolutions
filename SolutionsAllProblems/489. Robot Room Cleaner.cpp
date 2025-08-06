// problem : https://leetcode.com/problems/robot-room-cleaner/description/
// submission : https://leetcode.com/problems/robot-room-cleaner/submissions/1725518608
// solution post : https://leetcode.com/problems/robot-room-cleaner/solutions/7050880/
//    c-modern-readable-code-optimal-time-comp-o5bm

// #include <functional>
// #include <vector>
// #include <optional>
// #include <unordered_set>
// #include <utility>

/**
 * // This is the robot's control interface.
 * // You should not implement it, or speculate about its implementation
 * class Robot {
 *   public:
 *     // Returns true if the cell in front is open and robot moves into the cell.
 *     // Returns false if the cell in front is blocked and robot stays in the current cell.
 *     bool move();
 *
 *     // Robot will stay in the same cell after calling turnLeft/turnRight.
 *     // Each turn will be 90 degrees.
 *     void turnLeft();
 *     void turnRight();
 *
 *     // Clean the current cell.
 *     void clean();
 * };
 */

namespace Util {

using moveT = std::pair<int, int>;
using movesT = std::array<moveT, 4>;
inline auto constexpr kDirsCount{4u};
inline auto constexpr kMoves{movesT{{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}}};

class Cell {
public:
    Cell(
        int const currRow_,
        int const currCol_
    );
    bool operator==(Cell const other_) const;
    int GetRow() const {
        return mRow;
    }
    int GetCol() const {
        return mCol;
    }
private:
    int mRow;
    int mCol;
};

Cell::Cell(
    int const currRow_,
    int const currCol_
):
    mRow{currRow_},
    mCol{currCol_}
{}

bool Cell::operator==(Cell const other_) const {
    auto const row{other_.GetRow()};
    auto const col{other_.GetCol()};
    auto const isEqual{mRow == row && mCol == col};
    return isEqual; 
}

}

namespace std {
    using Util::Cell;
    template<>
    struct hash<Cell> {
        std::size_t operator()(Cell const & cell_) const {
            auto const rowHashVal{std::hash<int>()(cell_.GetRow())};
            auto const colHashVal{std::hash<int>()(cell_.GetCol()) << 1};
            auto const hashVal{rowHashVal ^ colHashVal};
            return hashVal;
        }
    };
}

class Solution {
public:
// let 'l' be a length of the given room
// 'w' - given width
// time complexity O(l * m)
// space complexity O(l * m)
// runtime 5 ms, beats 82.28 %
    void cleanRoom(Robot & robot_);
private:
    using RobotT = std::optional<std::reference_wrapper<Robot>>;
    void MoveBack();
    void Backtrack(
        int const currRow_,
        int const currCol_,
        int const d_
    );
    std::unordered_set<Util::Cell> mVisitedCells;
    RobotT mRobot;
};

void Solution::cleanRoom(Robot & robot_) {
    mRobot = robot_;
    Backtrack(0, 0, 0);
}

void Solution::MoveBack() {
    auto & robot{mRobot->get()};
    robot.turnRight();
    robot.turnRight();
    robot.move();
    robot.turnRight();
    robot.turnRight();
}

void Solution::Backtrack(
    int const currRow_,
    int const currCol_,
    int const currMoveIdx_
) {
    using namespace Util;
    mVisitedCells.emplace(currRow_, currCol_);
    auto & robot{mRobot->get()};
    robot.clean();
    for(auto currMoveIdx{0}; currMoveIdx < kDirsCount; ++currMoveIdx) {
        auto const nextcurrMoveIdx{(currMoveIdx_ + currMoveIdx) % kDirsCount};
        auto const & nextMove{kMoves.at(nextcurrMoveIdx)};
        auto const [rowShift, colShift]{nextMove};
        auto const nextRow{currRow_ + rowShift};
        auto const nextCol{currCol_ + colShift};
        if(!mVisitedCells.contains(Cell{nextRow, nextCol}) && robot.move()) {
            Backtrack(nextRow, nextCol, nextcurrMoveIdx);
            MoveBack();
        }
        robot.turnRight();
    }
}
