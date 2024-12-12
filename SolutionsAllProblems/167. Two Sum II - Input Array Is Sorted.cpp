// problem : https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/description/
// submission : https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/submissions/1477195700
// solution post : https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/solutions/6140333/c-modern-readable-code-beats-100-runtime

// #include <iterator>
// #include <vector>


class Solution {
public:
    // let 'n' be a parameter 'nums' length
    // time complexity O(n)
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
    std::vector<int> twoSum(
        std::vector<int> const & nums,
        int const target
    ) const {
        auto sum{0};
        for(auto num1{nums.cbegin()}, num2{nums.cend() - 1}; num1 < num2;) {
            sum = *num1 + *num2;
            if(sum < target) {
                ++num1;
            } else if(sum > target) {
                --num2;
            } else {
                return {
                    static_cast<int>(std::distance(nums.cbegin(), num1)) +1,
                    static_cast<int>(std::distance(nums.cbegin(), num2)) + 1};
            }
        } 
        return {-1, -1};
    }
};
