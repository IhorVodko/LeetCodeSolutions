// problem : https://leetcode.com/problems/minimum-operations-to-exceed-threshold-value-ii/description/
// submission : https://leetcode.com/problems/minimum-operations-to-exceed-threshold-value-ii/submissions/1542238689
// solution post : https://leetcode.com/problems/minimum-operations-to-exceed-threshold-value-ii/solutions/6419564/
//     c-modern-readable-code-beats-95-runtime-3wlp4

// #include <queue>
// #include <vector>

// let 'n' be a length of the given array
// time complexity O(n * log(n))
// space complexity O(n)
// runtime 80 ms, beats 95.21 %
class Solution {
public:
    int minOperations(
        std::vector<int> & nums,
        int const thresholdVal
    ) const {
        if(nums.size() == 1) {
            return 0;
        }
        auto minOpsCount{0};
        auto minHeap{std::priority_queue<int, std::vector<int>,
            std::greater<int>>{nums.begin(), nums.end()}};
        while(minHeap.size() >= 2 && minHeap.top() < thresholdVal) {
            auto const minNum{minHeap.top()}; 
            minHeap.pop();
            auto const minNumNext{minHeap.top()};
            minHeap.pop();
            if(auto const newNum{minNum * 2LL + minNumNext};
                newNum < thresholdVal
            ) {
                minHeap.emplace(newNum);
            }
            ++minOpsCount;
        }
        return minOpsCount + (!minHeap.empty() && minHeap.top() < thresholdVal
            ? 1 : 0);
    }
};
