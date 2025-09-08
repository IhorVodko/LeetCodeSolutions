// problem : https://leetcode.com/problems/find-n-unique-integers-sum-up-to-zero/description
// submission : https://leetcode.com/problems/find-n-unique-integers-sum-up-to-zero/submissions/1763847688
// solution post : https://leetcode.com/problems/find-n-unique-integers-sum-up-to-zero/solutions/7169368/
//    c-modern-readable-code-beats-100-runtime-9lqo

// #include <ranges>
// #include <vector>

class Solution {
public:
// let 'n' be a given count of numbers
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    std::vector<int> sumZero(int numCount_) const;
};

std::vector<int> Solution::sumZero(int numCount_) const {
    namespace views = std::views;
    auto nums{std::vector<int>{}};
    nums.reserve(numCount_);
    if(numCount_ % 2 != 0) {
        nums.emplace_back(0);
    } 
    auto const numPairCount{numCount_ / 2}; 
    for(auto const num: views::iota(1, numPairCount + 1)) {
        nums.emplace_back(num * -1);
        nums.emplace_back(num);
    }
    return nums;
}
