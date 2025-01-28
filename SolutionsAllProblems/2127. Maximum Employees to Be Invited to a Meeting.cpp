// problem : https://leetcode.com/problems/maximum-employees-to-be-invited-to-a-meeting/description/
// submission : https://leetcode.com/problems/maximum-employees-to-be-invited-to-a-meeting/submissions/1523266860
// solution post : https://leetcode.com/problems/maximum-employees-to-be-invited-to-a-meeting/solutions/6339928/c-modern-readable-code-optimal-time-comp-duyx

// #include <algorithm>
// #include <limit>
// #include <queue>
// #include <vector>

// let 'n' be a parameter 'favorite' length
// time complexity O(n)
// space complexity O(n)
// runtime 19 ms, beats 63.33 %
class Solution {
public:
    int maximumInvitations(std::vector<int> const & favorite) const {
        auto n{favorite.size()}; 
        auto inDegree{std::vector<size_t>(n, 0)};    
        for(auto const person: favorite) {
            ++inDegree[person];
        }
        auto q{std::queue<size_t>{}};
        for(auto person{size_t{0}}; person < n; ++person) {
            if(inDegree.at(person) == 0) {
                q.push(person);
            }
        }
        auto depth{std::vector<size_t>(n, 1)};
        auto currentNode{std::numeric_limits<size_t>::max()};
        auto nextNode{std::numeric_limits<size_t>::max()};
        while(!q.empty()) {
            currentNode = q.front();
            q.pop();
            nextNode = favorite.at(currentNode);
            depth.at(nextNode) = std::max(depth.at(nextNode),
                depth.at(currentNode) + 1);
            if(--inDegree.at(nextNode) == 0) {
                q.push(nextNode);
            }
        }
        auto longestCycle{std::numeric_limits<size_t>::min()};
        auto twoCycleInvitations{std::numeric_limits<size_t>::min()};
        auto cycleLength{std::numeric_limits<size_t>::max()};
        auto current{std::numeric_limits<size_t>::max()};
        for(auto person{size_t{0}}; person < n; ++person) {
            if(inDegree.at(person) == 0) {
                continue;
            }
            cycleLength = 0;
            current = person;
            while(inDegree.at(current) != 0) {
                inDegree.at(current) = 0;
                ++cycleLength;
                current = favorite.at(current);
            }
            if(cycleLength == 2) {
                twoCycleInvitations += depth.at(person) +
                    depth.at(favorite.at(person));
            } else {
                longestCycle = std::max(longestCycle, cycleLength);
            }
        }
        return  std::max(longestCycle, twoCycleInvitations);
    }
};
