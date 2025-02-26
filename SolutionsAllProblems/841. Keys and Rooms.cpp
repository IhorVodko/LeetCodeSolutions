// problem : https://leetcode.com/problems/keys-and-rooms/description/
// submission : https://leetcode.com/problems/keys-and-rooms/submissions/1556417074
// solution post : https://leetcode.com/problems/keys-and-rooms/solutions/6471896/
//     c-modern-readable-code-beats-100-runtime-ll1v

// #include <algorithm>
// #include <vector>

// let 'n' be a number of rooms
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    bool canVisitAllRooms(std::vector<std::vector<int>> const & rooms) const {
        auto roomsQ{std::queue<int>{rooms.front().begin(),
            rooms.front().end()}};
        auto visitedRooms{std::vector<bool>(rooms.size(), false)};
        visitedRooms.front() = true;
        for(auto const room: rooms.front()) {
            visitedRooms[room] = true;
        }
        while(!roomsQ.empty()) {
            auto room{roomsQ.front()};
            roomsQ.pop();
            for(auto const roomNext: rooms[room]) {
                if(!visitedRooms[roomNext]) {
                    roomsQ.emplace(roomNext);
                    visitedRooms[roomNext] = true;
                }
            }
        }
        return std::all_of(visitedRooms.cbegin(), visitedRooms.cend(),
            [] (auto const isRoomVisited) {return isRoomVisited == true;}); 
    }
};
