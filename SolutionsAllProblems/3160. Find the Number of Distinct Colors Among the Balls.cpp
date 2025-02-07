// problem : https://leetcode.com/problems/find-the-number-of-distinct-colors-among-the-balls/description/
// submission : https://leetcode.com/problems/find-the-number-of-distinct-colors-among-the-balls/submissions/1534979713
// solution post : https://leetcode.com/problems/find-the-number-of-distinct-colors-among-the-balls/solutions/6390412/c-modern-readable-code-optimal-time-comp-7nnj

// #include <vector>
// #include <unordered_map>

// let 'n' be a given queries count
// time complexity O(n)
// space complexity O(n)
// runtime 106 ms, beats 82.00 %
class Solution {
public:
    std::vector<int> queryResults(
        int const limit,
        std::vector<std::vector<int>> const & queries
    ) const {
        auto const queriesCount{queries.size()};
        auto distinctColorCounts{std::vector<int>(queriesCount, -1)};
        auto ballToColor{std::unordered_map<int, int>{}};
        auto colorToCount{std::unordered_map<int, int>{}};
        auto ball{-1};
        auto color{-1};
        for(auto queryIdx{size_t{0}}; queryIdx < queriesCount; ++queryIdx) {
            ball = queries.at(queryIdx).at(0);
            color = queries.at(queryIdx).at(1);
            if(ballToColor.contains(ball)) {
                if(--colorToCount.at(ballToColor.at(ball)) == 0) {
                    colorToCount.erase(ballToColor.at(ball));
                }
            }
            ballToColor[ball] = color;
            ++colorToCount[color]; 
            distinctColorCounts.at(queryIdx) = colorToCount.size();
        }
        return distinctColorCounts;
    }
};
