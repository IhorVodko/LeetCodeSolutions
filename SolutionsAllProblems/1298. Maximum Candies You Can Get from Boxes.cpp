// problem : https://leetcode.com/problems/maximum-candies-you-can-get-from-boxes/description
// submission : https://leetcode.com/problems/maximum-candies-you-can-get-from-boxes/submissions/1652965726
// solution post : https://leetcode.com/problems/maximum-candies-you-can-get-from-boxes/solutions/6808442/
//    c-modern-readable-code-optimal-time-comp-r7ui

// #include <algorithm>
// #include <queue>
// #include <vector>
// #include <unordered_set>

class Solution {
public:
    template<typename T_>
    using Arr2T = std::vector<std::vector<T_>>;
// let 'n' be a count of the boxes given
// time complexity O(n)
// space complexity O(n)
// runtime 3 ms, beats 68.75 %
    int maxCandies(
        std::vector<int> const & boxStatuses_,
        std::vector<int> const & candyCounts_,
        Arr2T<int> const & keys_,
        Arr2T<int> const & boxesContained_,
        std::vector<int> const & boxesInitial_
    ) const;
};

int Solution::maxCandies(
    std::vector<int> const & boxStatuses_,
    std::vector<int> const & candyCounts_,
    Arr2T<int> const & keys_,
    Arr2T<int> const & boxesContained_,
    std::vector<int> const & boxesInitial_
) const {
    auto isBoxOpen{std::vector<bool>{}};
    std::transform(boxStatuses_.cbegin(), boxStatuses_.cend(),
        std::back_inserter(isBoxOpen), [] (auto const isOpen) {
            return isOpen == 1 ? true : false; });
    auto boxesAvailable{std::queue<int>{boxesInitial_.begin(),
        boxesInitial_.end()}};
    auto boxesClosed{std::unordered_set<int>{}};
    auto candyCount{0};
    while(!boxesAvailable.empty()) {
        auto boxCurr{boxesAvailable.front()};
        boxesAvailable.pop();
        if(!isBoxOpen.at(boxCurr)) {
            boxesClosed.emplace(boxCurr);
            continue;
        }
        candyCount += candyCounts_.at(boxCurr);
        for(auto const key: keys_.at(boxCurr)) {
            isBoxOpen.at(key) = true; 
            if(boxesClosed.contains(key)) {
                boxesAvailable.emplace(key);
                boxesClosed.erase(key);
            }
        }
        for(auto const boxNext: boxesContained_.at(boxCurr)) {
            boxesAvailable.emplace(boxNext);
        }
    }
    return candyCount;
}
