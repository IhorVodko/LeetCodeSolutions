// problem : https://leetcode.com/problems/single-number/description/
// submission : https://leetcode.com/problems/single-number/submissions/1483053210
// solution post : https://leetcode.com/problems/single-number/solutions/6164714/c-modern-readable-code-beats-100-runtime-dao7


// #include <vector>


class Solution {
public:
    // let 'n' be a parameter 'nums' length
    // time complexity O(n)
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
    int singleNumber(vector<int> const & nums) const {
        auto single{0};
        for(auto const num: nums) {
            single ^= num;
        }
        return single;
    }
};
