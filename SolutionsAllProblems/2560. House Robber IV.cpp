// problem : https://leetcode.com/problems/house-robber-iv/description/
// submission : https://leetcode.com/problems/house-robber-iv/submissions/1574280434
// solution post : https://leetcode.com/problems/house-robber-iv/solutions/6538520/
//     c-modern-readable-code-beats-95-runtime-ncefo

// #include <algorithm>
// #include <vector>

// let 'h' be a length of the given array of the amount of money per house
// time complexity O(n + log(max(h) - min(h)))
// space complexity O(1)
// runtime 15 ms, beats 95.45 %
class Solution {
public:
    int minCapability(
        std::vector<int> const & moneysPerHouse_,
        int const minRequiredTheftsCount_
    ) const;
private:
    int DoBinarySearch(
        std::vector<int> const & moneysPerHouse_,
        int const minRequiredTheftsCount_
    ) const;
};


int Solution::minCapability(
    std::vector<int> const & moneysPerHouse_,
    int const minRequiredTheftsCount_
) const {
    auto const minMaxTheftAmount{DoBinarySearch(moneysPerHouse_,
        minRequiredTheftsCount_)};
    return minMaxTheftAmount;
}

int Solution::DoBinarySearch(
    std::vector<int> const & moneysPerHouse_,
    int const minRequiredTheftsCount_
) const {
    auto minTheftAmount{1};
    auto maxTheftAmount{*std::max_element(moneysPerHouse_.begin(),
        moneysPerHouse_.end())};
    auto housesCount{moneysPerHouse_.size()};
    while(minTheftAmount <= maxTheftAmount) {
        auto midTheftAmount{(minTheftAmount + maxTheftAmount) / 2};
        auto achievableTheftsCount{0};
        for(auto houseIdx{0}; houseIdx < housesCount; ++houseIdx) {
            if(moneysPerHouse_[houseIdx] <= midTheftAmount) {
                achievableTheftsCount += 1;
                ++houseIdx;
            }
        }
        if(achievableTheftsCount >= minRequiredTheftsCount_) {
            maxTheftAmount = midTheftAmount - 1;
        } else {
            minTheftAmount = midTheftAmount + 1;
        }
    }
    return minTheftAmount;
}
