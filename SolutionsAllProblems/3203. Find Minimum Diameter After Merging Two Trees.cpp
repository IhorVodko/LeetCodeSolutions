// problem : https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees/description/
// submission : https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees/submissions/1488128300
// solution post : https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees/solutions/6186044/c-modern-readable-code-by-cyberartist-w5yb

// #include <algorithm>
// #include <queue>
// #include <vector>
// #include <unordered_map>

class Solution {
    using EdgesT = std::vector<std::vector<int>>;
    using AdjMxT = std::unordered_map<int, std::vector<int>>;
public:
    // let 'e1' be a parameter 'edges1' length
    // 'e2' - a parameter 'edges2' length
    // time complexity O(e1 + e2)
    // space complexity O(e1 + e2)
    // runtime 642 ms, beats 22.78 %
    int minimumDiameterAfterMerge(
        EdgesT const & edges1,
        EdgesT const & edges2
    ) const { 
        auto const adjMx1{buildAdjMx(edges1)};
        auto const adjMx2{buildAdjMx(edges2)};
        auto diameter1{calculateDiameter(adjMx1)};
        auto diameter2{calculateDiameter(adjMx2)};
        auto diameterMerged{static_cast<int>(std::ceil(diameter1 / 2.0) +
            std::ceil(diameter2 / 2.0) + 1)};
        return std::max({diameter1, diameter2, diameterMerged});
    }
private:
    AdjMxT buildAdjMx(EdgesT const & edges) const {
        auto adjMx{AdjMxT{}};
        for(auto const edge: edges) {
           adjMx[edge.front()].emplace_back(edge.back()); 
           adjMx[edge.back()].emplace_back(edge.front()); 
        }
        return adjMx;
    }
    int calculateDiameter(AdjMxT const & adjMx) const {
        return findFarthestNodeAndDistance(adjMx,
            findFarthestNodeAndDistance(adjMx, 0).first).second; 
    }
    std::pair<int, int> findFarthestNodeAndDistance(
        AdjMxT const &  adjMx,
        int const startNode
    ) const {
        if(adjMx.empty()) {
            return {0, 0};
        }
        auto nodesQ{std::queue<int>{}};
        auto visitedNodes{std::vector<bool>(adjMx.size(), false)};
        nodesQ.push(startNode);
        visitedNodes.at(startNode) = true;
        auto maxDistance{0};
        auto levelSize{0};
        auto farthestNode{0};
        while(!nodesQ.empty()) {
            levelSize = nodesQ.size();
            while(levelSize-- > 0) {
                farthestNode = nodesQ.front();
                nodesQ.pop();
                for(auto const neighbourNode: adjMx.at(farthestNode)) {
                    if(!visitedNodes.at(neighbourNode)) {
                        nodesQ.push(neighbourNode);
                        visitedNodes.at(neighbourNode) = true;
                    }
                }
            }
            if(!nodesQ.empty()) {
                ++maxDistance;
            }
        }
        return {farthestNode, maxDistance};
    }
};
