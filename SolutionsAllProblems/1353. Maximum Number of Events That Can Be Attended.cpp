// problem : https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/description
// submission : https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/submissions/1691284388
// solution post : https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/solutions/6936747/
//    c-modern-readable-code-optimal-time-comp-rk78

// #include <ranges>
// #include <vector>

class Solution {
public:
    using EventT = std::vector<int>;
    using EventsT = std::vector<EventT>;
// let 'e' be count of the events given
// 'd' - maximum end day among those events
// time complexity O((e + d) * log2(e))
// space complexity O(e)
// runtime 62 ms, beats 51.18 %
    [[nodiscard]]
    int maxEvents(EventsT & events_) const;
};

int Solution::maxEvents(EventsT & events_) const {
    namespace ranges = std::ranges;
    namespace views = std::views;
    auto const eventsSz{events_.size()};
    if(events_.empty()) {
        return 0;
    }
    auto dayMax{ranges::max(events_ | views::transform([] (auto const & event_) {
        auto const endDay{event_.at(1)};
        return endDay;
    }))};
    auto pqEndDays{std::priority_queue<int, std::vector<int>, greater<>>{}};
    ranges::sort(events_);
    auto eventsVisitedCount{0};
    auto eventIdx{0};
    for(auto const dayIdx: views::iota(0, dayMax + 1)) {
        while(eventIdx < eventsSz && events_.at(eventIdx).at(0) <= dayIdx) {
            auto const endDay{events_.at(eventIdx).at(1)};
            pqEndDays.emplace(endDay);
            ++eventIdx;
        }
        while(!pqEndDays.empty() && pqEndDays.top() < dayIdx) {
            pqEndDays.pop();
        }
        if(!pqEndDays.empty()) {
            pqEndDays.pop();
            ++eventsVisitedCount;
        }
    }
    return eventsVisitedCount;
}
