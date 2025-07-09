// problem :  https://leetcode.com/problems/reschedule-meetings-for-maximum-free-time-i
// submission : https://leetcode.com/problems/reschedule-meetings-for-maximum-free-time-i/submissions/1692441398
// solution post : https://leetcode.com/problems/reschedule-meetings-for-maximum-free-time-i/solutions/6940598/
//    c-modern-readable-code-optimal-time-comp-3i31

// #include <algorithm>
// #include <ranges>
// #include <vector>

class Solution {
public:
// let 'n' be a count of the given meetings
// time complexity O(n)
// space complexity O(1)
// runtime 1 ms, beats 77.62 %
    using TimesT = std::vector<int>;
    [[nodiscard]]
    int maxFreeTime(
        int const eventEndTime_,
        int const changesCountMax_,
        TimesT const & startTimes_,
        TimesT const & endTimes_
    ) const;
};

int Solution::maxFreeTime(
    int const eventEndTime_,
    int const changesCountMax_,
    TimesT const & startTimes_,
    TimesT const & endTimes_
) const {
    namespace views = std::views;
    auto const meetingsSz{startTimes_.size()};
    auto freeTimeMax{0};
    auto meetingsTime{0};
    for(auto const idx: views::iota(0u, meetingsSz)) {
        auto const currMeetingTime{endTimes_.at(idx) - startTimes_.at(idx)};
        meetingsTime += currMeetingTime;
        auto windowStartTime{(idx <= (changesCountMax_ - 1)) ? 0 :
            endTimes_.at(idx - changesCountMax_)};
        auto windowEndTime{(idx == (meetingsSz - 1)) ? eventEndTime_ :
            startTimes_.at(idx + 1)};
        auto const freeTimeCurr{windowEndTime - windowStartTime - meetingsTime};
        freeTimeMax = std::max(freeTimeMax, freeTimeCurr);
        if(idx >= (changesCountMax_ - 1)) {
            auto const meetingToRemoveFromWindowIdx{idx - changesCountMax_ + 1};
            auto const meetinToRemoveFromWindowTime{
                endTimes_.at(meetingToRemoveFromWindowIdx) -
                startTimes_.at(meetingToRemoveFromWindowIdx)};
            meetingsTime -= meetinToRemoveFromWindowTime;
        }
    } 
    return freeTimeMax;
}
