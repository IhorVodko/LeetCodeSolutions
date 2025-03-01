// problem : https://leetcode.com/problems/apply-operations-to-an-array/description/
// submission : https://leetcode.com/problems/apply-operations-to-an-array/submissions/1559625428
// solution post : https://leetcode.com/problems/apply-operations-to-an-array/solutions/6483200/
//     c-modern-readable-code-beats-100-runtime-t4gv

// #include <vector>
// #include <utility>

// let 'n' be a length of the given array
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    std::vector<int> applyOperations(std::vector<int> & nums) const {
        auto writeIdx{0};
        auto const numsCount{nums.size()};
        for(auto idx{0}; idx < numsCount; ++idx) {
            if(idx < numsCount - 1 && nums[idx] == nums[idx + 1] &&
                nums[idx] != 0
            ) {
                nums[idx] *= 2;
                nums[idx + 1] = 0;
            }
            if(nums[idx] != 0) {
                if(idx != writeIdx) {
                    std::swap(nums[idx], nums[writeIdx]);
                }
                ++writeIdx;
            }
        }
        return nums;
    }
};
