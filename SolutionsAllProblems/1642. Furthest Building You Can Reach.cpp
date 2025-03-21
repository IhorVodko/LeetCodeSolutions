// problem : https://leetcode.com/problems/furthest-building-you-can-reach/description/
// submission : https://leetcode.com/problems/furthest-building-you-can-reach/submissions/1581606256
// solution post : https://leetcode.com/problems/furthest-building-you-can-reach/solutions/6564132/
//     c-modern-readable-code-optimal-time-comp-hxwi

// #include <functional>
// #include <queue>
// #include <vector>

// let 'h' be a count of heights given
// 'l' - count of ladders given
// time complexity O(h * log2(l))
// space complexity O(l)
// runtime 7 ms, beats 87.44 %
class Solution {
public:
    int furthestBuilding(
        std::vector<int> const & heights_,
        int const bricksAvailable_,
        int const laddersAvailable_
    ) const {
        auto ladderAllocationsTopMin{std::priority_queue<int, std::vector<int>,
            std::greater<int>>{}};
        auto bricksUsed{0};
        for(auto idx{0}; idx < heights_.size() - 1; ++idx) {
            auto const climb{heights_.at(idx + 1) - heights_.at(idx)};
            if(climb <= 0) {
                continue;
            }
            ladderAllocationsTopMin.emplace(climb);
            if(ladderAllocationsTopMin.size() <= laddersAvailable_) {
                continue;
            }
            bricksUsed += ladderAllocationsTopMin.top();
            ladderAllocationsTopMin.pop();
            if(bricksUsed > bricksAvailable_) {
                return idx;
            } 
        }
        return heights_.size() - 1;
    }
};
