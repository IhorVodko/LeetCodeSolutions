// problem : https://leetcode.com/problems/house-robber/description/
// submission : https://leetcode.com/problems/house-robber/submissions/1768230251
// solution post : https://leetcode.com/problems/house-robber/solutions/7182343/
//    c-modern-readable-code-beats-100-runtime-4zcu

// #include <algorithms>
// #include <vector>

class Solution {
public:
// let 'n' be a count of the houses given
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    int rob(std::vector<int> const & rewardsByHouse_) const;
};

int Solution::rob(std::vector<int> const & rewardsByHouse_) const {
    namespace views = std::views;
    namespace ranges = std::ranges;
    auto const houseCnt{std::ssize(rewardsByHouse_)};
    if(houseCnt <= 2) {
        auto const maxRob{*ranges::max_element(rewardsByHouse_)};
        return maxRob;
    }
    auto maxRobPrev{rewardsByHouse_.at(0)};
    auto maxRobCurr{std::max(rewardsByHouse_.at(0), rewardsByHouse_.at(1))};
    for(auto const idx: views::iota(2, houseCnt)) {
        auto const maxRobTemp{maxRobCurr};
        maxRobCurr = std::max(maxRobPrev + rewardsByHouse_.at(idx), maxRobCurr);
        maxRobPrev = maxRobTemp; 
    }
    return  maxRobCurr;
}
