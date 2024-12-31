// problem : https://leetcode.com/problems/minimum-cost-for-tickets/description/ 
// submission : https://leetcode.com/problems/minimum-cost-for-tickets/submissions/1493573451
// solution post : https://leetcode.com/problems/minimum-cost-for-tickets/solutions/6210492/c-modern-readable-code-beats-100-runtime-0ley

// #include <algorithm>
// #include <vector>
// #include <unordered_set>

namespace Utility {
    auto constexpr day{1};
    auto constexpr week{7};
    auto constexpr month{30};
    auto constexpr needsToBeCalculated{-1};
    auto constexpr startDay{1};
}

// let 'n' be a parameter 'days' last element value
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int mincostTickets(
        std::vector<int> const & days,
        std::vector<int> const & costs
    ) {
        using namespace Utility;
        totalCosts.assign(days.back() + 1, needsToBeCalculated);
        travelDays = {days.cbegin(), days.cend()};
        return FindLowestTotalCost(days, costs, startDay);
    }
private:
    int FindLowestTotalCost(
        auto const & days,
        auto const & costs,
        auto const currDay
    ) {
        using namespace Utility;
        if(currDay > days.back()) {
            return 0;
        }
        if(!travelDays.contains(currDay)) {
            return FindLowestTotalCost(days, costs, currDay + 1);
        }
        if(totalCosts.at(currDay) != needsToBeCalculated) {
            return totalCosts.at(currDay);
        }
        auto startFromDayCost{costs.at(0) +
            FindLowestTotalCost(days, costs, currDay + day)};
        auto startFromWeekCost{costs.at(1) +
            FindLowestTotalCost(days, costs, currDay + week)};
        auto startFromMonthCost{costs.at(2) +
            FindLowestTotalCost(days, costs, currDay + month)};
        return totalCosts.at(currDay) = std::min(startFromDayCost,
            std::min(startFromWeekCost, startFromMonthCost));
    }
    std::unordered_set<int> travelDays;
    std::vector<int> totalCosts;
};
