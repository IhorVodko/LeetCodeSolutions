// problem : https://leetcode.com/problems/max-consecutive-ones/description/
// submission : https://leetcode.com/problems/max-consecutive-ones/submissions/1462682946
// solution post: https://leetcode.com/problems/max-consecutive-ones/solutions/6082886/c-modern-readable-code-beats-100-runtime

// #include <algorithm>
// #include <vector>

class Solution {
public:
    // let n be an input length
    // time complexity O(n)
    // space complexity O(1)
    // runtime 0 ms, beats 100 %
    // memory 49.17 mb, beats 27.20 %
    int findMaxConsecutiveOnes(std::vector<int> const & nums) const {
        int maxOnes{0};
        int currentOnes{0};
        for(auto num: nums){
            if(num == 1){
                ++currentOnes; 
                continue;
            }
            if(num == 0){
                maxOnes = std::max(maxOnes, currentOnes);
                currentOnes = 0;
                continue;    
            }    
        }
        return std::max(maxOnes, currentOnes);
    }    
};
