// problem : https://leetcode.com/problems/minimum-limit-of-balls-in-a-bag/description/
// submission : https://leetcode.com/problems/minimum-limit-of-balls-in-a-bag/submissions/1474431097
// solution post : https://leetcode.com/problems/minimum-limit-of-balls-in-a-bag/solutions/6129528/c-modern-readable-code


// #include <algorithm>
// #include <vector>


class Solution {
public:
    // let 'n' be an input length,
      'm' - a greatest number inputed
    // time complexity O(n * log(m))
    // space complexity O(1)
    // runtime 27 ms, beats 84.41 %
    int minimumSize(
        std::vector<int> const & nums,
        int const maxOperations
    ) {
        maxBallsInBag = *std::max_element(nums.cbegin(), nums.cend());
        while(minBallsInBag < maxBallsInBag) {
            maxBallsInBagAchievable = (minBallsInBag + maxBallsInBag) / 2;
            if(isAchievableBallsDistribution(nums, maxBallsInBagAchievable,
                maxOperations)
            ) {
                maxBallsInBag = maxBallsInBagAchievable;
            } else {
                minBallsInBag = maxBallsInBagAchievable + 1;
            }
        }
        return minBallsInBag;
    }
private:
    bool isAchievableBallsDistribution(
        std::vector<int> const & nums,
        int const maxBallsInBagToAchive,
        int const maxOperations
    ) const {
        auto operations{0};
        for(auto const num : nums) {
            if((operations += (num - 1) / maxBallsInBagToAchive) >
                maxOperations
            ) {
                return false;
            }
        }
        return true;
    }
    int minBallsInBag{1};
    int maxBallsInBag{0};
    int maxBallsInBagAchievable{1};
};
