// problem : https://leetcode.com/problems/graph-valid-tree/description/?envType=weekly-question&envId=2025-01-29
// submission : https://leetcode.com/problems/graph-valid-tree/submissions/1524737858
// solution post : https://leetcode.com/problems/graph-valid-tree/solutions/6345836/c-modern-readable-code-optimal-time-comp-2fj5

// #include <vector>
// #include <unordered_set>

// let 'n' be a nodes count  
// time complexity O(n)
// space complexity O(n)
// runtime 3 ms, beats 52.74 %
class Solution {
public:
    bool validTree(
        int const nodesCount,
        std::vector<std::vector<int>> const & edges
    ) {
        Reset(nodesCount);
        if(edges.size() + 1 != nodesCount) {
            return false;
        }
        for(auto const & edge: edges) {
            adj.at(edge.front()).emplace_back(edge.back());
            adj.at(edge.back()).emplace_back(edge.front());
        }
        DoDfs(0);
        return seenNodes.size() == nodesCount;
    }
private:
    void DoDfs(int const node) {
        if(seenNodes.contains(node)) {
            return;
        }
        seenNodes.emplace(node);
        for(auto const & neighbourNode: adj.at(node)) {
            DoDfs(neighbourNode);
        }
    }
    void Reset(int const nodesCount) {
        adj = std::vector<std::vector<int>>(nodesCount, std::vector<int>{});
        seenNodes.clear();
    }
    std::vector<std::vector<int>> adj;
    std::unordered_set<int> seenNodes;
};
