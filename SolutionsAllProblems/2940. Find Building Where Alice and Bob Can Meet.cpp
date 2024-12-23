// problem : https://leetcode.com/problems/find-building-where-alice-and-bob-can-meet/description/
// submission : https://leetcode.com/problems/find-building-where-alice-and-bob-can-meet/submissions/1486414250
// solution post : https://leetcode.com/problems/find-building-where-alice-and-bob-can-meet/solutions/6178251/c-modern-readable-code-by-cyberartist-emlk


// #include <algorithm>
// #include <queue>
// #icnlude <vector>


class Solution {
public:
    // let 'h' be a parameter 'heights' length
    // 'q' - parameter 'queries' length
    // time complexity O(q * log(q))
    // space complexity O(h + q)
    // runtime 91 ms, beats 73.08 %
    std::vector<int> leftmostBuildingQueries(
        std::vector<int> const & heights,
        std::vector<std::vector<int>> const & queries
    ) const {
        using itQueryT = std::vector<std::vector<int>>::const_iterator;
        auto result{std::vector<int>(queries.size(), -1)};
        auto queriesLeft{std::vector<std::vector<std::pair<int, itQueryT>>>(
            heights.size())};
        for(auto query{queries.cbegin()}, begin{queries.cbegin()},
            end{queries.cend()}; query < end; ++query
        ) {
            auto heightA{heights.cbegin() + query->front()};
            auto heightB{heights.cbegin() + query->back()};
            if(heightA < heightB && *heightA < *heightB) {
                result.at(query - begin) = heightB - heights.cbegin();
            } else if ((heightA > heightB && *heightA > *heightB) ||
                heightA == heightB
            ) {
                result.at(query - begin) = heightA - heights.cbegin();
            } else {
                queriesLeft.at(std::max(query->front(), query->back())).
                    push_back({std::max(*heightA, *heightB), query});
            }
        }
        auto maxHeights{std::priority_queue<std::pair<int, itQueryT>,
            std::vector<std::pair<int, itQueryT>>,
            std::greater<std::pair<int, itQueryT>>>{}};
        for(auto height{heights.cbegin()}, end{heights.cend()}; height < end;
            ++height
        ) {
            while(!maxHeights.empty() && maxHeights.top().first < *height) {
                result.at(maxHeights.top().second - queries.cbegin()) =
                    height - heights.cbegin();
                maxHeights.pop();
            }
            for(auto const & heightAndQuery:
                queriesLeft.at(height - heights.cbegin())
            ) {
                maxHeights.push(heightAndQuery);
            }
        }
        return result;
    }
};
