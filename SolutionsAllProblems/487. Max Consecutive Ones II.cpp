// problem : https://leetcode.com/problems/max-consecutive-ones-ii/description/
// submission : https://leetcode.com/problems/max-consecutive-ones-ii/submissions/1468653347
// solution post : https://leetcode.com/problems/max-consecutive-ones-ii/solutions/6106064/c-modern-readable-code-beats-100-runtime 

// #include <algorithm>
// #include <type_traits>
// #include <vector>


class Solution{
public:
    // let 'n' be an input size
    // time complexity O(n)
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
    int findMaxConsecutiveOnes(std::vector<int> const & nums) const {
        if(nums.size() == 1) {
            return 1;
        } 
        auto maxOnes{std::remove_cvref<decltype(nums)>::type::
            difference_type{0}};
        auto const halfLength{nums.size() / 2};
        auto const end{nums.cend()};
        auto zerosPresent{size_t(0)};
        for(auto first{nums.cbegin()}, last{nums.cbegin()}; last < end; ++last) {
            if(*last == 0){
                ++zerosPresent;
            }
            while(zerosPresent >= 2) {
                if(*first++ == 0){
                    --zerosPresent;
                }
            }
            maxOnes = std::max(maxOnes, last - first + 1);
        }
        return maxOnes;
    }
};
