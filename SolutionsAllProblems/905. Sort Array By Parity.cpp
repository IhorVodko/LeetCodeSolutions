// problem : https://leetcode.com/problems/sort-array-by-parity/description/
// submission : https://leetcode.com/problems/sort-array-by-parity/submissions/1468496217
// solution post: https://leetcode.com/problems/sort-array-by-parity/solutions/6105427/c-modern-readable-code-beats-100-runtime

// #include <vector>
// #incluede <utility>


class Solution{
public:
    // let 'n' be an input size
    // time complexity O(n)
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
    std::vector<int> sortArrayByParity(std::vector<int> & nums) {
        if(nums.size() == 1) {
            return nums;
        }    
        for(auto odd{nums.begin()}, even{nums.begin() + 1}, end{nums.end()};
            even < end; ++even
        ) {
            while(*odd % 2 == 0) {
                if(++odd >= end) {
                    return nums;
                }
            }
            while(*even % 2 != 0) {
                if(++even >= end) {
                    return nums;
                }
            }
            if(odd < even) {
                std::swap(*odd, *even);
            }
        }
        return nums;
    }
};
