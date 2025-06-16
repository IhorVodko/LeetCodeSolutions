// problem : https://leetcode.com/problems/maximum-difference-between-increasing-elements/description/
// submission : https://leetcode.com/problems/maximum-difference-between-increasing-elements/submissions/1666014913
// solution post : https://leetcode.com/problems/maximum-difference-between-increasing-elements/solutions/6850435/
//    c-modern-readable-code-beats-100-runtime-m87h

// #include <algorithm>
// #include <ranges>
// #include <vector>

class Solution {
public:
// let 'n' be a length of a given array
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    int maximumDifference(std::vector<int> & nums_) const;
};

int Solution::maximumDifference(std::vector<int> & nums_) const {
    auto prefNumMin{nums_.at(0)};
    auto diffMax{-1};
    for(auto num: nums_ | std::views::drop(1)) {
        if(num > prefNumMin) {
            diffMax = std::max(diffMax, num - prefNumMin);
        } else {
            prefNumMin = num;
        }
    }
    return diffMax;
}
