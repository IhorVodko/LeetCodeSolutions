// problem : https://leetcode.com/problems/minimum-index-of-a-valid-split/editorial/
// submission : https://leetcode.com/problems/minimum-index-of-a-valid-split/submissions/1588172580
// solution post : https://leetcode.com/problems/minimum-index-of-a-valid-split/solutions/6586308/
//     c-modern-readable-code-beats-100-runtime-lijs

// #include <algorithm>
// #include <vector>

// let 'n' be a numbers count given
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int minimumIndex(std::vector<int> const & nums_) const {
        auto dominant{nums_.at(0)};
        auto countNum{0};
        for(auto const num: nums_) {
            countNum += num == dominant ? 1 : -1;
            if(countNum == 0) {
                dominant = num;
                countNum = 1;
            }
        }
        auto countDominant{std::count(nums_.begin(), nums_.end(), dominant)};
        auto countDominantLeft{0};
        auto const countNums{nums_.size()};
        for(auto i{0}; i < countNums; ++i) {
            if(nums_[i] == dominant) {
                ++countDominantLeft;
            }
            if(countDominantLeft * 2 > i + 1 &&
                (countDominant - countDominantLeft) * 2 > nums_.size() - i - 1
            ) {
                return i;
            }

        }
        return -1;
    }
};
