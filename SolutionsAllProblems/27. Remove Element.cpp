// problem : https://leetcode.com/problems/remove-element/description/
// submission : https://leetcode.com/problems/remove-element/submissions/1464416758
// solution post: 

// #include <vector>


class Solution{
public:
    // let 'n' be an input size
    // time complexity O(n)
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
    // memory 11.74 mb, beats  37.48 %
    // for educational purposes no stl algos used
    int removeElement(
        std::vector<int> & nums,
        int valToDelete
    ) {
        // for educational purposes no stl algos used
        auto numLast{nums.end()};
        for(auto numFirst{nums.begin()}; numFirst < numLast; ) {
            if(*numFirst != valToDelete) {
                ++numFirst;
                continue;
            }
            *numFirst = *--numLast;
        }
        return std::distance(nums.begin(), numLast);
    }
};
