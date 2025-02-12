// problem : https://leetcode.com/problems/max-sum-of-a-pair-with-equal-sum-of-digits/description/
// submission : https://leetcode.com/problems/max-sum-of-a-pair-with-equal-sum-of-digits/submissions/1540406569
// solution post : https://leetcode.com/problems/max-sum-of-a-pair-with-equal-sum-of-digits/solutions/6412612/
//     c-modern-readable-code-beats-97-runtime-9nx36

// #include <algorithm>
// #include <limits>
// #include <vector>

// let 'n' be a length of the given array
// time complexity O(n)
// space complexity O(n)
// runtime 4 ms, beats 97.45 %
namespace Utility {
    auto constexpr radix{10};
}

class Solution {
public:
    int maximumSum(std::vector<int> const & nums) const {
        auto sumOfDigitsToNums{std::unordered_map<size_t,
            std::pair<int, int>>{}};
        auto maxSum{-1};
        for(auto const num: nums) {
            auto & nums{sumOfDigitsToNums[
                CalculateSumOfDigits(num)]};
            if(emplaceIfTwoMaxNums(nums, num)) {
                maxSum = std::max(maxSum, nums.first + nums.second);
            }
        }
        return maxSum;
    }
private:
    size_t CalculateSumOfDigits(size_t num) const {
        using namespace Utility;
        auto sumOfDigits{size_t{0}};
        while(num > 0) {
            sumOfDigits += num % radix;
            num /= radix;
        }
        return sumOfDigits;
    }
    bool emplaceIfTwoMaxNums(
        std::pair<int, int> & nums,
        int const num
    ) const {
        auto changed{false};
        if(num > nums.first) {
            nums.second = nums.first;
            nums.first = num; 
            changed = true;
        } else if(num > nums.second) {
            nums.second  = num;
            changed = true;
        }
        return nums.second != 0 && changed;
    }
};
