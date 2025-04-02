// problem : https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-i/description/
// submission : https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-i/submissions/1594562691
// solution post : https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-i/solutions/6607948/
//     c-modern-readable-code-beats-100-runtime-ngm8

// #include <algorithm>
// #include <vector>

// let 'n' be a count of numbers given
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    long long maximumTripletValue(std::vector<int> const & nums_) const {
        auto const numsCount{nums_.size()};
        auto iMax{0LL};
        auto diffMax{0LL};
        auto result{0LL};
        for(auto k{0}; k < numsCount; ++k) {
            result = std::max(result, diffMax * nums_[k]);
            diffMax = std::max(diffMax, iMax - nums_[k]);
            iMax = std::max(iMax, static_cast<long long>(nums_[k]));
        }
        return result;
    }
};
