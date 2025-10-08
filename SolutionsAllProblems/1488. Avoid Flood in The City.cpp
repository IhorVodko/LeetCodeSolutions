// problem : https://leetcode.com/problems/avoid-flood-in-the-city/description/
// submission : https://leetcode.com/problems/avoid-flood-in-the-city/submissions/1795595080
// solution post : https://leetcode.com/problems/avoid-flood-in-the-city/solutions/7260182/
//    c-modern-readable-code-optimal-time-comp-t77q

// import std;

class Solution {
public:
// let 'n' be the length of the given rainy days array
// time complexity O(n * log(n))
// space complexity O(n)
// runtime 97 ms, beats 91.17 %
    [[nodiscard]]
    auto avoidFlood(std::vector<int> const & days_) const -> std::vector<int>;

private:
    inline static int constexpr kRainDay{-1};
    inline static int constexpr kNoRainDay{0};
    inline static int constexpr kDummyDay{1};
    inline static bool const kIsFastIO{
        [] () {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return true;
        } ()
    };
};

auto Solution::avoidFlood(
    std::vector<int> const & days_
) const -> std::vector<int> {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto const daysSz{std::ssize(days_)};
    auto drenageDays{std::vector<int>(daysSz, kDummyDay)};
    auto dryDays{std::set<int>{}};
    auto dayToLake{std::unordered_map<int, int>{}};
    dayToLake.reserve(daysSz); 
    for(auto const day: vs::iota(0, daysSz)) {
        auto const lake{days_.at(day)};
        if(lake == kNoRainDay) {
            dryDays.emplace(day);
            continue;
        }
        drenageDays.at(day) = kRainDay;
        if( auto const dayAndLakeIt{dayToLake.find(lake)};
            dayAndLakeIt != dayToLake.cend()
        ) {
            auto const dryDayIt{dryDays.lower_bound(dayAndLakeIt->second)};
            if(dryDayIt == dryDays.cend()) {
                return {};
            }
            drenageDays.at(*dryDayIt) = lake;
            dryDays.erase(dryDayIt);
        }
        dayToLake[lake] = day;
    }
    return drenageDays;
}
