// problem : https://leetcode.com/problems/k-empty-slots/description
// submission : https://leetcode.com/problems/k-empty-slots/submissions/1676176312
// solution post : https://leetcode.com/problems/k-empty-slots/solutions/6884767/
//    c-modern-readable-code-optimal-time-comp-imll

// #include <algorithm>
// #include <limits>
// #include <ranges>
// #include <vector>

class Solution {
public:
// let 'n' be a count of the given bulbs
// time complexity O(n)
// space complexity O(n)
// runtime 8 ms, beats 76.11 %
    [[nodiscard]]
    int kEmptySlots(
        std::vector<int> const & bulbs_,
        int bulbsCountRequired_
    ) const;
};

int Solution::kEmptySlots(
    std::vector<int> const & bulbs_,
    int const bulbsCountRequired_
) const {
    using intT = std::numeric_limits<int>;
    namespace views = std::views;
    auto const bulbsCount{bulbs_.size()};
    auto daysTurnedOn{std::vector<int>(bulbsCount, 0)};
    for(auto const idx: views::iota(0u, bulbsCount)) {
        daysTurnedOn.at(bulbs_.at(idx) - 1) = idx + 1;
    }
    auto daysMinCount{intT::max()};
    auto leftDay{0};
    auto rightDay{bulbsCountRequired_ + 1};
    while(rightDay < bulbsCount) {
        auto isPossibleResult{true};
        for(auto const idx: views::iota(leftDay + 1, rightDay)) {
            if(daysTurnedOn.at(idx) < daysTurnedOn.at(leftDay) ||
                daysTurnedOn.at(idx) < daysTurnedOn.at(rightDay)
            ) {
                leftDay = idx;
                rightDay = idx + bulbsCountRequired_ + 1;
                isPossibleResult = false;
                break;
            }
        }
        if(!isPossibleResult) {
            continue;
        }
        daysMinCount = std::min(daysMinCount,
            std::max(daysTurnedOn.at(leftDay), daysTurnedOn.at(rightDay)));
        leftDay = rightDay;
        rightDay = leftDay + bulbsCountRequired_ + 1;
    }
    return daysMinCount < intT::max() ? daysMinCount : -1;
}
