// problem : https://leetcode.com/problems/search-insert-position/description/
// submission : https://leetcode.com/problems/search-insert-position/submissions/1510576952
// solution post : https://leetcode.com/problems/search-insert-position/solutions/6290029/c-modern-readable-code-beats-100-runtime-45m6

// #include <vector>

// let 'n' be a parameter 'nums' length
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int searchInsert(
        std::vector<int> const & nums,
        int const target
    ) const {
        for(auto num{nums.begin()}, end{nums.end()};
            num < end; ++num
        ) {
            if(*num >= target) {
                return num - nums.begin(); 
            }; 
        }
        return nums.size();
    }
};
