// problem : https://leetcode.com/problems/minimum-time-to-repair-cars/description/
// submission : https://leetcode.com/problems/minimum-time-to-repair-cars/submissions/1576154122 
// solution post : https://leetcode.com/problems/minimum-time-to-repair-cars/solutions/6544686/
//     c-modern-readable-code-by-cyberartist-tqpx

// #include <vectro>

// let 'm' be a mechanics count
// 'c' - cars count
// 'r' - value of the first rank of the given array
// time complexity O(m * log(c * r^2);
// space complexity O(1)
// runtime 54 ms, beats 48.48 %
class Solution {
public:
    long long repairCars(
        std::vector<int> const & ranks_,
        int const carsToFixCount_
    ) const;
};

long long Solution::repairCars(
    std::vector<int> const & ranks_,
    int const carsToFixCount_
) const {
    auto minTime{1LL};
    auto maxTime{1LL * carsToFixCount_ * carsToFixCount_ * ranks_[0]};
    while(minTime <= maxTime) {
        auto const midTime{(minTime + maxTime) / 2};
        auto carsRpairedCount{0LL};
        for(auto const rank: ranks_) {
            carsRpairedCount += std::sqrt(midTime / rank);
        }
        if(carsRpairedCount < carsToFixCount_) {
            minTime = midTime + 1;
        } else {
            maxTime = midTime - 1;
        }
    }
    return minTime;
}
