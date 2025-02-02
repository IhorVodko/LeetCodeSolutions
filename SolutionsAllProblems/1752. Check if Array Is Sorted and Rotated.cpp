// problem : https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/description/
// submission : https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/submissions/1528732138
// solution post : https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/solutions/6362990/c-modern-readable-code-beats-100-runtime-v8ql

// #include <vector>

// let 'n' be a parameter 'nums' length
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    bool check(std::vector<int> const & nums) const {
        auto changeCount{0};
        for(auto num{nums.begin() + 1}, end{nums.end()}; num < end;
            ++num
        ) {
            if(*(num - 1) > *num && ++changeCount > 1) {
                return false;
            } 
        }
        if(changeCount == 1) {
            return nums.front() >= nums.back();
        }
        return true;
    }
};
