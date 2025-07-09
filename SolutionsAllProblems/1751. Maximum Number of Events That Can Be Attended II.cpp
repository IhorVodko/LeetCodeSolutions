// problem : https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended-ii/description
// submission : https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended-ii/submissions/1692318165
// solution post : https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended-ii/solutions/6940274/
//    c-modern-readable-code-optimal-time-comp-0ar4

// #include <algorithm>
// #include <functional>
// #include <iterator>
// #include <ranges>
// #include <vector>

class Solution {
public:
    using EventT = std::vector<int>;
    using EventsT = std::vector<EventT>;
// let 'e' be a count of the given events
// 'm' - an given upper limit count of the visited events
// time complexity O(e * (m + log2(e))
// space complexity O(e * m)
// runtime 182 ms, beats 30.16 %
    [[nodiscard]]
    int maxValue(
        EventsT & events_,
        int const visitedEventsCountMax
    ) const;
};

int Solution::maxValue(
    EventsT & events_,
    int const visitedEventsCountMax
) const {
    namespace ranges = std::ranges;
    namespace views = std::views;
    auto const eventsSz{std::ssize(events_)};
    auto maxSumsDp{std::vector<std::vector<int>>(visitedEventsCountMax + 1,
        std::vector<int>(eventsSz + 1, 0))};
    auto const eventProj{[] (auto const & event_) {
        auto const startDay{event_.at(0)};
        return startDay;
    }};
    ranges::sort(events_, std::less{}, eventProj);
    for(auto const currEventIdx: views::iota(0, eventsSz) | views::reverse) {
        auto const currEventEndDay{events_.at(currEventIdx).at(1)};
        auto  const nextVisitedEventIt{ranges::lower_bound(events_,
            currEventEndDay, std::less_equal{}, eventProj)};
        auto const nextVisitedEventIdx{std::distance(events_.begin(),
            nextVisitedEventIt)};
        for(auto const visitedEventsCountCurr:
            views::iota(1, visitedEventsCountMax + 1))
        {
            auto & currSum{maxSumsDp.at(visitedEventsCountCurr).at(
                currEventIdx)};
            auto const nextEventSum{maxSumsDp.at(visitedEventsCountCurr).at(
                currEventIdx + 1)};
            auto const currEventValue{events_.at(currEventIdx).at(2)};
            auto const nextVisitedEventSum{maxSumsDp.at(
                visitedEventsCountCurr - 1).at(nextVisitedEventIdx)};
            currSum = std::max(nextEventSum,
                currEventValue + nextVisitedEventSum);
        }
    }
    auto const maxSum{maxSumsDp.at(visitedEventsCountMax).at(0)};
    return maxSum;
}
