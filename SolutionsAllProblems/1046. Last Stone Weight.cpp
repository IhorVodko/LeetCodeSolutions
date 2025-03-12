// problem : https://leetcode.com/problems/last-stone-weight/description/
// submission : https://leetcode.com/problems/last-stone-weight/submissions/1571227153
// solution post : https://leetcode.com/problems/last-stone-weight/solutions/6528154/
//     c-modern-readable-code-beats-100-runtime-757z

// #include <queue>
// #include <vector>
// #include <utility>

// let 'n' be a length of the given array
// time complexity O(n * log(n))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int lastStoneWeight(std::vector<int> & stones_) const;
};

int Solution::lastStoneWeight(std::vector<int> & stones_) const {
    auto priorityQ{std::priority_queue<int>{std::less<int>{},
        std::move(stones_)}};
    while(priorityQ.size() > 1) {
        auto const stoneHeavy{priorityQ.top()};
        priorityQ.pop();
        auto const stoneLight{priorityQ.top()};
        priorityQ.pop();
        if(stoneHeavy > stoneLight) {
            priorityQ.emplace(stoneHeavy - stoneLight);
        }
    }
    return priorityQ.empty() ? 0 : priorityQ.top();
}
