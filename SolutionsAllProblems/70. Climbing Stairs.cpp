// problem : https://leetcode.com/problems/climbing-stairs/description/
// submission : https://leetcode.com/problems/climbing-stairs/submissions/1511287989 
// solution post : https://leetcode.com/problems/climbing-stairs/solutions/6293220/c-modern-readable-code-beats-100-runtime-udaw

// let 'n' be a parameter 'n' val
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int climbStairs(int n) const {
        if(n == 1) {
            return 1;
        }
        auto first{1};
        auto second{2};
        auto third{0};
        for(auto stairs{3}; stairs <= n; ++stairs) {
            third = first + second;
            first = second;
            second = third;
        }
        return second;
    }
};
