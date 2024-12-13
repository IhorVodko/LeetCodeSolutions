// problem : https://leetcode.com/problems/rotate-array/description/ 
// submission : https://leetcode.com/problems/rotate-array/submissions/1477899658
// solution post : https://leetcode.com/problems/rotate-array/solutions/6143302/c-modern-readable-code-beats-100-runtime-f19g


// #include <vector>


class Solution {
public:
    // let 'n' be a parameter 'nums' length
    // time complexity O(n)
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
    void rotate(
        std::vector<int> & nums,
        int steps
    ) const {
        steps %= nums.size();
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + steps);
        reverse(nums.begin() + steps, nums.end());
    }
private:
    void reverse(
        auto first,
        auto last
    ) const {
        auto temp{0};
        --last;
        while(first < last) {
            temp = *first;
            *first++ = *last;
            *last-- = temp; 
        }
    }
};
