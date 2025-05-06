// problem : https://leetcode.com/problems/build-array-from-permutation/description/
// submission : https://leetcode.com/problems/build-array-from-permutation/submissions/1627126703
// solution post : https://leetcode.com/problems/build-array-from-permutation/solutions/6720712/
//    c-modern-readable-code-beats-100-runtime-ps27

// #include <vector>

namespace Utility {
    auto constexpr kNumMax{1'000};
}

class Solution {
public:
// let 'n' be a lenght of the given array
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    std::vector<int> buildArray(std::vector<int> & nums_) const;
};

std::vector<int> Solution::buildArray(std::vector<int> & nums_) const {
    using namespace Utility;
    auto const numsCount{nums_.size()};
    for(auto i{0}; i < numsCount; ++i) {
        nums_[i] += kNumMax * (nums_.at(nums_[i]) % kNumMax);
    }
    for(auto i{0}; i < numsCount; ++i) {
        nums_[i] /= kNumMax;
    }
    return nums_;
}
