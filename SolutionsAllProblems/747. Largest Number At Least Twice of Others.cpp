// problem : https://leetcode.com/problems/largest-number-at-least-twice-of-others/submissions/1470291228/
// submission : https://leetcode.com/problems/largest-number-at-least-twice-of-others/submissions/1470291228
// solution post : https://leetcode.com/problems/largest-number-at-least-twice-of-others/solutions/6113469/c-modern-readable-code-beats-100-runtime


// #include <vector>


class Solution {
public:
    // let 'n' be an input length
    // time complexity O(n)
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
    int dominantIndex(
        std::vector<int> const & nums
    ) const {
        auto max{int{0}};
        auto maxBefore{int{0}};
        auto indxMax{size_t{0}};
        for(auto indx{size_t{0}}; indx < nums.size(); ++indx) {
            if(nums.at(indx) > max) {
                indxMax = indx;
                maxBefore = max;
                max = nums.at(indx);
            } else {
                maxBefore = std::max(maxBefore, nums.at(indx));
            }
        }
        return  maxBefore * 2 <= max ? indxMax : -1;
    }
};
