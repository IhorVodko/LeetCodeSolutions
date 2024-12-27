// problem : https://leetcode.com/problems/best-sightseeing-pair/description/
// submission : https://leetcode.com/problems/best-sightseeing-pair/submissions/1490177623
// solution post : https://leetcode.com/problems/best-sightseeing-pair/solutions/6195179/c-modern-readable-code-beats-100-runtime-l2fs

// #include <algorithm>
// #include <limits>
// #include <vector>

// let 'n' be a parameter 'vals' length
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int maxScoreSightseeingPair(
        std::vector<int> & values
    ) const {
        auto maxScore{std::numeric_limits<int>::min()};
        auto distance{0};
        for(auto val{values.begin() + 1}, begin{values.begin()},
            end(values.end()); val < end; ++val
        ) {
            distance = val - begin;
            maxScore = std::max(maxScore, *(val - 1) + *val - distance);
            *val = std::max(*(val - 1), *val + distance);            
        }    
        return maxScore;
    } 
};
