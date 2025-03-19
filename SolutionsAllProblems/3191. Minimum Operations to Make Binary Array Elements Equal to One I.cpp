// problem : https://leetcode.com/problems/minimum-operations-to-make-binary-array-elements-equal-to-one-i/description/
// submission : https://leetcode.com/problems/minimum-operations-to-make-binary-array-elements-equal-to-one-i/
//    submissions/1579099012
// solution post : https://leetcode.com/problems/minimum-operations-to-make-binary-array-elements-equal-to-one-i/
//     solutions/6555794/c-modern-readable-code-beats-100-runtime-fv9o

// #include <vector>

// let 'n' be a length of the given array
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int minOperations(std::vector<int> & nums_) const {
        auto const numsCount{nums_.size()};
        auto minFlipsCount{0};
        for(auto i{0}; i <= numsCount - 3; ++i) {
            if(nums_[i] != 0) {
                continue;
            }
            nums_[i] ^= 1;
            nums_[i + 1] ^= 1;
            nums_[i + 2] ^= 1;
            ++minFlipsCount;
        }
        return nums_[numsCount - 2] & nums_[numsCount - 1] ? minFlipsCount : -1;
    }
};
