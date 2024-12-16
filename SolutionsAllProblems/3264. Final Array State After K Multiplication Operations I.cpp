// problem : https://leetcode.com/problems/final-array-state-after-k-multiplication-operations-i/description/
// submission : https://leetcode.com/problems/final-array-state-after-k-multiplication-operations-i/submissions/1480405595
// solution post : https://leetcode.com/problems/final-array-state-after-k-multiplication-operations-i/solutions/6153442/c-modern-readable-code-beats-100-runtime-ybhx


// #include <algorithm>
// #include <queue>
// #include <vector>


class Solution {
public:
    // let 'n' be a parameter 'nums' length
    // 'm' - a parameter 'steps' value
    // time complexity O(n + m * log(n))
    // space complexity O(n)
    // runtime 0 ms, beats 100.00 %
    std::vector<int> getFinalState(
        std::vector<int> & nums,
        int steps,
        int const multiplier
    ) const {
        using ItT = std::remove_cvref<decltype(nums)>::type::iterator;
        auto Compare{[&] (auto const it1, auto const it2) {
            return *it1 == *it2 ? it1 >= it2 : *it1 > *it2; }};
        auto heapMin{std::priority_queue<ItT, std::vector<ItT>,
            decltype(Compare)>{Compare}};        
        for_each(nums.begin(), nums.end(), [&] (auto & num) {
            heapMin.push(ItT{&num}); });
        auto it{nums.end()};
        while(steps-- > 0) {
            it = heapMin.top();
            heapMin.pop();
            *it *= multiplier;
            heapMin.push(it);
        } 
        return nums;
    }   
};
