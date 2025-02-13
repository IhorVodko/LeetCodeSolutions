// problem : https://leetcode.com/problems/walls-and-gates/description/
// submission : https://leetcode.com/problems/walls-and-gates/submissions/1542165723
// solution post : https://leetcode.com/problems/walls-and-gates/solutions/6419366/
//     c-modern-readable-code-beats-100-runtime-kec4

// #include <queue>
// #include <vector>

namespace Constants {
    auto constexpr wall{-1};
    auto constexpr gate{0};
    auto constexpr emptyInf{2147483647};
}

// let 'l' by 'w' be a size of the given grid
// time complexity O(l * w)
// space complexity O(l * w)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    using MxT = std::vector<std::vector<int>>;
    using RoomT = std::pair<int, int>;
    void wallsAndGates(MxT & rooms) const {
        using namespace Constants;
        auto qRooms{std::queue<RoomT>{}};
        AddAllGatesToQueue(qRooms, rooms);
        FindShortestPathRoomToGate(qRooms, rooms);
    }
    Solution():
        moves{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}
    {}
private:
    bool IsRoomEmpty(
        MxT const & rooms,
        RoomT const & room
    ) const {
        using namespace Constants;
        auto const rowsCount{rooms.size()};
        auto const colsCount{rooms.at(0).size()};
        auto const [row, col]{room};
        return 0 <= row && row < rowsCount && 0 <= col && col < colsCount &&
            rooms.at(row).at(col) == emptyInf; 
    }
    void AddAllGatesToQueue(
        std::queue<RoomT> & qRooms,
        MxT const & rooms
    ) const {
        using namespace Constants;
        auto const rowsCount{rooms.size()};
        auto const colsCount{rooms.at(0).size()};
        for(auto row{0}; row < rowsCount; ++row) {
            for(auto col{0}; col < colsCount; ++col) {
                if(rooms.at(row).at(col) == gate) {
                    qRooms.emplace(row, col);
                }
            }
        }
    }
    void FindShortestPathRoomToGate(
        std::queue<RoomT> & qRooms,
        MxT & rooms
    ) const {
        while(!qRooms.empty()) {
            auto const [row, col]{qRooms.front()};
            qRooms.pop();
            for(auto const & move: moves) {
                auto const nextRow{row + move.first};
                auto const nextCol{col + move.second};
                if(!IsRoomEmpty(rooms, {nextRow, nextCol})) {
                    continue;
                }
                rooms.at(nextRow).at(nextCol) = rooms.at(row).at(col) + 1; 
                qRooms.emplace(nextRow, nextCol);
            }
        }
    }
    std::vector<std::pair<int, int>> moves;
};
