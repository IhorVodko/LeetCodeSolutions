// problem : https://leetcode.com/problems/minimum-cost-to-connect-sticks/description/
// submission : https://leetcode.com/problems/minimum-cost-to-connect-sticks/submissions/1580604474
// solution post : https://leetcode.com/problems/minimum-cost-to-connect-sticks/solutions/6560546/
//     c-modern-readable-code-optimal-time-comp-vx8k

// #include <queue>
// #include <vector>

// let 'n' be a count of sticks given
// time complexity O(n * log2(n))
// space complexity O(1)
// runtime 23 ms, beats 82.62 %
class Solution {
public:
    int connectSticks(std::vector<int> & sticks_) const {
        auto sticksShortestTop{std::priority_queue<int, std::vector<int>,
            std::greater<int>>{std::greater<int>{}, std::move(sticks_)}};
        auto costTotal{0};
        while(sticksShortestTop.size() >= 2) {
            auto const stick1{sticksShortestTop.top()};
            sticksShortestTop.pop();
            auto const stick2{sticksShortestTop.top()};
            sticksShortestTop.pop();
            auto const stickNew{stick1 + stick2};
            sticksShortestTop.emplace(stickNew);
            costTotal += stickNew;
        }    
        return costTotal;
    }
};
