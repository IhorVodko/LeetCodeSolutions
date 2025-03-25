// problem : https://leetcode.com/problems/count-days-without-meetings/description/
// submission : https://leetcode.com/problems/count-days-without-meetings/submissions/1585623966
// solution post : https://leetcode.com/problems/count-days-without-meetings/solutions/6578108/
//     c-modern-readable-code-optimal-time-comp-gbi2

// #include <algorithm>
// #include <vector>

// let 'n' be a count of meetings given
// time complexity O(n * log2(n))
// space complexity O(1)
// runtime 67 ms, beats 69.72 %
class Solution {
public:
    int countDays(
        int const days_,
        std::vector<std::vector<int>> & meetings_
    ) const {
        if(meetings_.size() == 1) {
            auto const thisStart{meetings_.at(0).at(0)};
            auto const thisEnd{meetings_.at(0).at(1)};
            return days_ - (thisEnd - thisStart + 1);
        }
        std::sort(meetings_.begin(), meetings_.end());
        auto availableDaysCount{meetings_.front().front() - 1};
        auto lastMeetingDay{0};
        for(auto meetingThis{meetings_.begin()},
            meetingNext{meetings_.begin() + 1}, end{meetings_.end()};
            meetingNext < end; ++meetingThis, ++meetingNext
        ) {
            auto const thisEnd{meetingThis->at(1)};
            auto const nextStart{meetingNext->at(0)};
            lastMeetingDay = std::max(lastMeetingDay, thisEnd);
            auto const availableDaysTempCount{nextStart - lastMeetingDay -1};
            if(availableDaysTempCount > 0) {
                availableDaysCount += availableDaysTempCount;
            } 
        } 
        availableDaysCount += days_ - std::max(lastMeetingDay,
            meetings_.back().back());
        return availableDaysCount;
    }
};
