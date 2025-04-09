// problem : https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/description/
// submission : https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/submissions/
//     601933199
// solution post : https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/
//    solutions/6634030/c-modern-readable-code-optimal-time-comp-2zqt

// #include <queue>
// #include <vector>
// #include <unordered_map>

// let 'v' be a count of vertices of the given graph
// 'e' - count of edges
// time complexity O(e + v)
// space complexity O(e + v)
// runtime 4 ms, beats 56.68 %
class Solution {
public:
    using Arr2T = std::vector<std::vector<int>>;
    int countComponents(
        int const n_,
        Arr2T const & edges
    ) const;
};

int Solution::countComponents(
    int const n_,
    Arr2T const & edges
) const {
    auto adjList{std::unordered_map<int, std::vector<int>>{}}; 
    for(auto const & edge: edges) {
        adjList[edge[0]].emplace_back(edge[1]);
        adjList[edge[1]].emplace_back(edge[0]);
    }
    auto const singleNodeComponentsCount{n_ - adjList.size()};
    auto nodesVisited{std::vector<bool>(n_, false)};
    auto componentsCount{0};
    auto nodesQ{std::queue<int>{}};
    while(!adjList.empty()) {
        ++componentsCount;
        auto const nodeStart{adjList.begin()->first};
        nodesQ.emplace(nodeStart);
        nodesVisited[nodeStart] = true;
        while(!nodesQ.empty()) {
            auto const nodeCurr{nodesQ.front()};
            nodesQ.pop();
            for(auto const nodeNext: adjList[nodeCurr]) {
                if(nodesVisited[nodeNext]) {
                    continue;
                }
                nodesVisited[nodeNext] = true;
                nodesQ.emplace(nodeNext);
            }    
            adjList.erase(nodeCurr);
        }
    }
    return componentsCount + singleNodeComponentsCount;
}
