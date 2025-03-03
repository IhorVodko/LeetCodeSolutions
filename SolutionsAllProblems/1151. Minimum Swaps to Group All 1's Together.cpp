// problem : https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together/description/
// submission : https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together/submissions/1561813763
// solution post : https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together/solutions/6492010/
//     c-modern-readable-code-beats-100-runtime-inhq

// #include <algorithm>
// #include <vector>

// let 'n' be a length of the given array
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int minSwaps(std::vector<int> const & nums) const {
        auto onesCountTotal{std::count(nums.begin(), nums.end(), 1)};
        auto onesCountCurrent{std::count(nums.begin(),
            nums.begin() + onesCountTotal, 1)};
        auto onesCountCurrentMax{onesCountCurrent};
        for(auto firstNum{nums.begin()},
            lastNum{nums.begin() + onesCountTotal}, end{nums.end()};
            lastNum < end; ++firstNum, ++lastNum
        ) {
            onesCountCurrent += -*firstNum + *lastNum;
            onesCountCurrentMax = std::max(onesCountCurrentMax,
                onesCountCurrent);
        }
        return onesCountTotal - onesCountCurrentMax;
    }
};
