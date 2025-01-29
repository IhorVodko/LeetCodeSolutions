// problem : https://leetcode.com/problems/redundant-connection/description/
// submission : https://leetcode.com/problems/redundant-connection/submissions/1524353878
// solution post : https://leetcode.com/problems/redundant-connection/solutions/6344415/c-modern-readable-code-beats-100-runtime-0sk1

// #include <limit>
// #include <vector>
// #include <unordered_map>

// let 'n' be a nodes count in the given tree
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    std::vector<int> findRedundantConnection(
        std::vector<vector<int>> const & edges
    ) const {
        auto adjMx{std::unordered_map<int, std::vector<int>>{}};
        for(auto const & edge: edges) {
            adjMx[edge.front()].emplace_back(edge.back());
            adjMx[edge.back()].emplace_back(edge.front());
        }
        auto degreesCounts{std::vector<int>(adjMx.size() + 1)};
        auto leafNodes{std::queue<int>{}};
        for(auto const & [node, neighbours]: adjMx) {
            degreesCounts.at(node) = neighbours.size();
            if(neighbours.size() == 1) {
                leafNodes.push(node);
            }
        }
        if(leafNodes.empty()) {
            return edges.back();
        }
        auto node{std::numeric_limits<int>::min()};
        while(!leafNodes.empty()) {
            node = leafNodes.front();
            leafNodes.pop();
            --degreesCounts.at(node);
            for(auto const neighbourNode: adjMx.at(node)) {
                if(--degreesCounts.at(neighbourNode) == 1) {
                    leafNodes.push(neighbourNode);
                }
            }
            adjMx.erase(node);
        }
        for(auto edge{edges.rbegin()}, end{edges.rend()}; edge < end; ++edge) {
            if(adjMx.contains(edge->front()) &&
                adjMx.contains(edge->back())
            ) {
                return *edge;    
            }
        }
        return {-1, -1};
    }
};
