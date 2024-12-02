// problem : https://leetcode.com/problems/remove-duplicates-from-sorted-array/description/
// submission : https://leetcode.com/problems/remove-duplicates-from-sorted-array/submissions/1464483771
// solution post : https://leetcode.com/problems/remove-duplicates-from-sorted-array/solutions/6089835/c-modern-readable-code-beats-100-runtime 

// #include <vector>

class Solution{
public:
    // let 'n' be an input length
    // time complexity O(n)
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
    // for educational purposes no stl algos used
    int removeDuplicates(std::vector<int> & nums){
        if(nums.size() == 1){
            return 1;
        }
        auto first{nums.begin()};
        for(auto second{nums.begin() + 1}, end{nums.end()}; second < end;){
            if(*first == *second) {
                ++second;
                continue;
            }
            *++first = *second++;
        }
        return std::distance(nums.begin(), first + 1);
    }
};
