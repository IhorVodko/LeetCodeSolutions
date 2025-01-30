// problem :  https://leetcode.com/problems/divide-nodes-into-the-maximum-number-of-groups/description/
// submission : https://leetcode.com/problems/divide-nodes-into-the-maximum-number-of-groups/submissions/1525746375
// solution post : https://leetcode.com/problems/divide-nodes-into-the-maximum-number-of-groups/solutions/6349761/c-modern-readable-code-optimal-time-comp-sva5

// #include <algorithm>
// #include <queue>
// #include <vector>

// let 'n' be a nodes count in the given graph
// 'e' - edges count in the given graph
// time complexity O(n * (n + e))
// space complexity O(n)
// runtime 212 ms, beats 24.79 %
class Solution {
public:
    int magnificentSets(
        int const n,
        std::vector<std::vector<int>> const & edges
    ) const {
        auto adjList{std::vector<std::vector<int>>(n, std::vector<int>{})};
        for(auto const & edge: edges) {
            adjList.at(edge.at(0) - 1).push_back(edge.at(1) - 1);
            adjList.at(edge.at(1) - 1).push_back(edge.at(0) - 1);
        } 
        auto colors{std::vector<int>(n, -1)};
        for(auto node{0}; node < n; ++node) {
            if(colors.at(node) != -1) {
                continue;
            }
            colors.at(node) = 0;
            if(!IsBipartie(adjList, node, colors)) {
                return -1;
            }
        }
        auto distances{std::vector<int>(n, -1)};
        for(auto node{0}; node < n; ++node) {
            distances.at(node) = GetLongestShortestPath(adjList, node, n); 
        }
        auto maxNumberOfGroups{0};
        auto visited{std::vector<bool>(n, false)};
        for(auto node{0}; node < n; ++node) {
            if(visited.at(node)) {
                continue;
            }
            maxNumberOfGroups += GetNumberOfGroupsForComponent(adjList, node,
                distances, visited);
        }
        return maxNumberOfGroups;
    }
private:
    bool IsBipartie(
        std::vector<std::vector<int>> const & adjList,
        int const node,
        std::vector<int> & colors 
    ) const {
        for(auto const neighbour: adjList.at(node)) {
            if(colors.at(neighbour) == colors.at(node)) {
                return false;
            }
            if(colors.at(neighbour) != -1) {
                continue;
            }
            colors.at(neighbour) = (colors.at(node) + 1) % 2;
            if(!IsBipartie(adjList, neighbour, colors)) {
                return false;
            }
        }
        return true;
    }
    int GetLongestShortestPath(
        std::vector<std::vector<int>> const & adjList,
        int const srcNode,
        int const n
    ) const {
        auto nodesQueue{std::queue<int>{}};
        auto visited{std::vector<bool>(n, false)};
        nodesQueue.push(srcNode);
        visited.at(srcNode) = true;
        auto distance{0};
        auto numOfNodesInLayer{-1};
        auto currentNode{-1};
        while(!nodesQueue.empty()) {
            numOfNodesInLayer = nodesQueue.size();
            for(auto i{0}; i < numOfNodesInLayer; ++i) {
                currentNode = nodesQueue.front(); 
                nodesQueue.pop();
                for(auto const neighbour: adjList.at(currentNode)) {
                    if(visited.at(neighbour)) {
                        continue;
                    }
                    visited.at(neighbour) = true;
                    nodesQueue.push(neighbour);
                }
            }
            ++distance;
        }
        return distance;
    }
    int GetNumberOfGroupsForComponent(
        std::vector<std::vector<int>> const & adjList,
        int const node,
        std::vector<int> const & distances,
        std::vector<bool> & visited
    ) const {
        auto maxNumberOfGroups{distances.at(node)};
        visited.at(node) = true;
        for(auto const neighbour: adjList.at(node)) {
            if(visited.at(neighbour)) {
                continue;
            }
            maxNumberOfGroups = std::max(maxNumberOfGroups,
                GetNumberOfGroupsForComponent(adjList, neighbour, distances,
                    visited));
        }
        return maxNumberOfGroups;
    }
};
