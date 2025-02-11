// problem : https://leetcode.com/problems/make-the-prefix-sum-non-negative/description/
// submission : https://leetcode.com/problems/make-the-prefix-sum-non-negative/submissions/1539571063
// solution post : https://leetcode.com/problems/make-the-prefix-sum-non-negative/solutions/6409143/
//     c-modern-readable-code-optimal-time-comp-hnlo

// #include <algorithm>
// #include <queue>
// #include <vector>

// let 'n' be a length of the given array
// time complexity O(n * log(n))
// space complexity O(n)
// runtime 3 ms, beats 86.38 %
class Solution {
public:
    int makePrefSumNonNegative(std::vector<int> & nums) const {
        auto prefixSum{0LL};
        auto opsCount{0};
        auto minHeapOfNegNums{std::priority_queue<int, std::vector<int>,
            std::greater<int>>{}};
        for(auto const num: nums) {
            if(num < 0) {
                minHeapOfNegNums.push(num);
            };
            if((prefixSum += num) < 0) {
                prefixSum -= minHeapOfNegNums.top();
                minHeapOfNegNums.pop();
                ++opsCount;
            } 
        }
        return opsCount;
    }
};
