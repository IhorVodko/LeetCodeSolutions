// problem : https://leetcode.com/problems/reschedule-meetings-for-maximum-free-time-ii/description/
// submission : https://leetcode.com/problems/reschedule-meetings-for-maximum-free-time-ii/submissions/1693435105
// solution post : https://leetcode.com/problems/reschedule-meetings-for-maximum-free-time-ii/solutions/6943921/
//    c-modern-readable-code-optimal-time-comp-3qyf

// #include <algorithm>
// #include <ranges>
// #include <vector>

class Solution {
public:
// let 'n' be a count of the given events
// time complexity O(n)
// space complexity O(1)
// runtime 11 ms, beats 75.70 %
    [[nodiscard]]
    int maxFreeTime(
        int const eventEndTime_, 
        std::vector<int> const & startTimes_,
        std::vector<int> const & endTimes_
    ) const;
};

int Solution::maxFreeTime(
    int const eventEndTime_, 
    std::vector<int> const & startTimes_,
    std::vector<int> const & endTimes_
) const {
    namespace views = std::ranges::views; 
    auto const eventCount{std::ssize(startTimes_)};
    auto freeTimeSpanMax{0};
    auto vacantTimeSpanMaxToLeft{0};
    auto vacantTimeSpanMaxToRight{0};
    for(auto const eventForwardIdx: views::iota(0, eventCount)) {
        auto freeTimeStart{eventForwardIdx == 0 ? 0 :
            endTimes_.at(eventForwardIdx - 1)};
        auto freeTimeEnd{eventForwardIdx == (eventCount - 1) ?
            eventEndTime_ : startTimes_.at(eventForwardIdx + 1)};
        auto currEventTimeSpan{endTimes_.at(eventForwardIdx) -
            startTimes_.at(eventForwardIdx)};
        auto freeTimeSpanCurr{freeTimeEnd - freeTimeStart};
        if(currEventTimeSpan <= vacantTimeSpanMaxToLeft) {
            auto const freeTimeSpan{freeTimeEnd - freeTimeStart};
            freeTimeSpanMax = std::max(freeTimeSpanMax, freeTimeSpanCurr);
        }
        auto const preEventEndTime{eventForwardIdx == 0 ? 0 :
            endTimes_.at(eventForwardIdx - 1)};
        auto vacantTimeSpanToLeft{startTimes_.at(eventForwardIdx) -
            preEventEndTime};
        vacantTimeSpanMaxToLeft = std::max(vacantTimeSpanMaxToLeft,
            vacantTimeSpanToLeft);
        freeTimeSpanCurr -= currEventTimeSpan;
        freeTimeSpanMax = std::max(freeTimeSpanMax, freeTimeSpanCurr);
        auto const eventBackwardIdx{eventCount - eventForwardIdx};
        freeTimeStart = eventForwardIdx == (eventCount - 1) ? 0 :
            endTimes_.at(eventBackwardIdx - 2);
        freeTimeEnd = eventForwardIdx == 0 ? eventEndTime_ :
            startTimes_.at(eventBackwardIdx);
        currEventTimeSpan = endTimes_.at(eventBackwardIdx - 1) -
            startTimes_.at(eventBackwardIdx - 1);
        freeTimeSpanCurr = freeTimeEnd - freeTimeStart;
        if(currEventTimeSpan <= vacantTimeSpanMaxToRight) {
            freeTimeSpanMax = std::max(freeTimeSpanMax, freeTimeSpanCurr);
        }
        auto const vacantTimeSpanToRightStartTime{endTimes_.at(
            eventBackwardIdx - 1)};
        auto const vacantTimeSpanToRightEndTime{eventForwardIdx == 0 ?
            eventEndTime_ : startTimes_.at(eventBackwardIdx)};
        auto const vacantTimeSpanToRight{vacantTimeSpanToRightEndTime -
            vacantTimeSpanToRightStartTime};
        vacantTimeSpanMaxToRight = std::max(vacantTimeSpanMaxToRight,
            vacantTimeSpanToRight);
    }
    return freeTimeSpanMax;
}
