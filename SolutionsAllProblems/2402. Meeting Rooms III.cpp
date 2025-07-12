// problem : https://leetcode.com/problems/meeting-rooms-iii/description
// submission : https://leetcode.com/problems/meeting-rooms-iii/submissions/1695639118
// solution post : https://leetcode.com/problems/meeting-rooms-iii/solutions/6950990/
//    c-modern-readable-code-optimal-time-comp-hkd1

// #include <limits>
// #include <ranges>
// #include <vector>

#include <ranges>

class Solution {
public:
    using meetingT = std::vector<int>;
    using meetingsT = std::vector<meetingT>;
// let 'm' be a count of the given meetings
// let 'r' - of the given rooms
// time complexity O(m * (log2(m) + log2(r))
// space complexity O(r + O(sort))
// runtime 71 ms, beats 67.66 %
    [[nodiscard]]
    int mostBooked(
        int const roomCount_,
        meetingsT & meetings_
    ) const;
};

int Solution::mostBooked(
    int const roomCount_,
    meetingsT & meetings_
) const {
    namespace views = std::ranges::views;
    namespace ranges = std::ranges;
    using intT = std::numeric_limits<size_t>;
    using endTimeAndRoomT = std::pair<size_t, size_t>;
    auto meetingCountsPerRoom{std::vector<size_t>(roomCount_, 0)};
    auto occupiedRooms{std::priority_queue<
            endTimeAndRoomT
        ,   std::vector<endTimeAndRoomT>
        ,   std::greater<>
        >{}};
    auto freeRooms{std::priority_queue<
            int
        ,   std::vector<int>
        ,   std::greater<>
        >{}};
    for(auto const room: views::iota(0, roomCount_)) {
        freeRooms.emplace(room);
    }
    ranges::sort(meetings_);
    for(auto const & meeting: meetings_) {
        auto const meeitngStartTime{meeting.at(0)};
        auto const meeitngEndTime{meeting.at(1)};
        while(
                !occupiedRooms.empty()
            &&  occupiedRooms.top().first <= meeitngStartTime
        ) {
            auto const room{occupiedRooms.top().second};
            occupiedRooms.pop();
            freeRooms.emplace(room);
        }
        if(freeRooms.empty()) {
            auto [roomEndTime, room]{occupiedRooms.top()};
            occupiedRooms.pop();
            auto const meetingDuration{meeitngEndTime - meeitngStartTime};
            auto const roomNewEndTime{roomEndTime + meetingDuration};
            occupiedRooms.emplace(roomNewEndTime, room);
            ++meetingCountsPerRoom[room];
        } else {
            auto const room{freeRooms.top()};
            freeRooms.pop();
            occupiedRooms.emplace(meeitngEndTime, room);
            ++meetingCountsPerRoom[room];
        }
    }
    auto maxMeetingCountPerRoom{intT::min()};
    auto mostBusyRoom{intT::max()};
    for(auto const room: views::iota(0, roomCount_)) {
        auto const meetingCountPerRoom{meetingCountsPerRoom.at(room)};
        if(meetingCountPerRoom > maxMeetingCountPerRoom) {
            maxMeetingCountPerRoom = meetingCountPerRoom;
            mostBusyRoom = room;
        } 
    }
    return mostBusyRoom;
}
