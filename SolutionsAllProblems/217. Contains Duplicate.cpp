// problem :  https://leetcode.com/problems/contains-duplicate/description/
// submission : https://leetcode.com/problems/contains-duplicate/submissions/1483038157
// solution post : https://leetcode.com/problems/contains-duplicate/solutions/6164655/c-modern-readable-code-by-cyberartist-8zrh


// #include <algorithm>
// #include <vector>


class Solution {
public:
    // let 'n' be a parameter 'nums' length
    // time complexity O(n * log(n))
    // space complexity O(1)
    // runtime 18 ms, beats 93.87 %
    bool containsDuplicate(std::vector<int> & nums) const {
        std::sort(nums.begin(), nums.end());
        for(auto num{nums.cbegin()}, end{nums.cend() - 1}; num < end; ++num) {
            if(*num == *(num + 1)) {
                return true;
            }
        }
        return false;
    }
};
