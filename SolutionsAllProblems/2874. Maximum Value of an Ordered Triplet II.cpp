// problem : https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-ii/description/
// submission : https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-ii/submissions/1595800970
// solution post : https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-ii/solutions/6612090/
//     c-modern-readable-code-beats-100-runtime-tqiu

// #include <algorithm>

// let 'n' be a count of given numbers
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    long long maximumTripletValue(std::vector<int> const & nums_) const {
        auto maxVal{0LL};
        auto maxFirstNum{static_cast<long long>(std::max(nums_.at(0),
            nums_.at(1)))};
        auto maxDiff{static_cast<long long>(std::max(
            nums_.at(0) - nums_.at(1), 0))};
        for(auto k{2}; k < nums_.size(); ++k) {
            auto const thirdNum{nums_[k]};
            maxVal = std::max(maxVal, maxDiff * thirdNum);
            maxDiff = std::max(maxDiff, maxFirstNum - thirdNum);
            maxFirstNum = std::max(maxFirstNum,
                static_cast<long long>(thirdNum));
        }
        return maxVal;
    }
};
