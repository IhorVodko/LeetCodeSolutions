// problem : https://leetcode.com/problems/special-array-i/description/
// submission : https://leetcode.com/problems/special-array-i/submissions/1527880725
// solution post : https://leetcode.com/problems/special-array-i/solutions/6359076/c-modern-readable-code-beats-100-runtime-6k38

// #include <vector>

// let 'n' be a parameter 'nums' length
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    bool isArraySpecial(std::vector<int> const & nums) const {
        for(auto numCurr{nums.begin()}, numNext{nums.begin() + 1},
            end{nums.end()}; numNext < end; ++numCurr, ++numNext
        ) {
            if(*numCurr % 2 == *numNext % 2) {
                return false;
            }
        }
        return true;
    }
};
