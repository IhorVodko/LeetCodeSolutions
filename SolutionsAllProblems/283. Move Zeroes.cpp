// problem : https://leetcode.com/problems/move-zeroes/description/ 
// submission : https://leetcode.com/problems/move-zeroes/submissions/1465741120
// solution post: https://leetcode.com/problems/move-zeroes/solutions/6094384/c-modern-readable-code-beats-100-runtime

// #include <vector>

class Solution{
public:
    // let 'n' be an input size
    // time complexity O(n)
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
    // for educational purposes no stl algos are used
    void moveZeroes(std::vector<int> & nums) {
        auto reader{nums.begin()};
        auto end{nums.end()};
        while(*reader != 0) {
            if(++reader == end) {
                return;
            }
        }
        auto writer{nums.begin()};
        while(reader < end) {
            while(*writer != 0) {
                if(++writer == end) {
                    return;
                }
            }
            while(*reader == 0) {
                if(++reader == end) {
                    return;
                }
            }
            *writer++ = *reader;
            *reader++ = 0; 
        }
    }
};
