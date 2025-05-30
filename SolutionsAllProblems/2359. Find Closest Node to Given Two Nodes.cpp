// problem : https://leetcode.com/problems/find-closest-node-to-given-two-nodes/description/
// submission : https://leetcode.com/problems/find-closest-node-to-given-two-nodes/submissions/1649153171
// solution post : https://leetcode.com/problems/find-closest-node-to-given-two-nodes/solutions/6796763/
//    c-modern-readable-code-beats-99-by-cyber-vdcr

// #include <algorithm>
// #include <limits>
// #include <vector>

class Solution {
public:
// let 'n' be a count of the given nodes
// time complexity O(n)
// space complexity O(n)
// runtime 3 ms, beats 99.00 %
    int closestMeetingNode(
        std::vector<int> const & edges_,
        int const nodeStart1_,
        int const nodeStart2_
    ) const;
};

int Solution::closestMeetingNode(
    std::vector<int> const & edges_,
    int const nodeStart1_,
    int const nodeStart2_
) const {
    using intT = std::numeric_limits<int>;
    if(nodeStart1_ == nodeStart2_) {
        return nodeStart1_;
    }
    auto const nodesCount{edges_.size()};
    auto distances{std::vector<int>(nodesCount, -1)};
    auto nodesVisited{std::vector<bool>(nodesCount, false)};
    auto nodeCurr{nodeStart1_};
    auto distance{0};
    do{
        distances.at(nodeCurr) = distance;
        ++distance;
        nodesVisited.at(nodeCurr) = true;
        nodeCurr = edges_.at(nodeCurr);
    } while(nodeCurr != -1 && !nodesVisited.at(nodeCurr));
    distance = 0;
    std::fill(nodesVisited.begin(), nodesVisited.end(), false);
    nodeCurr = nodeStart2_;
    auto minMaxDistance{intT::max()};
    auto minMaxNode{intT::max()};
    do{
        if(distances.at(nodeCurr) != -1) {
            auto const distanceMax{std::max(distances.at(nodeCurr), distance)};
            if(minMaxDistance > distanceMax) {
                minMaxDistance = distanceMax;
                minMaxNode = nodeCurr; 
            } else if(minMaxDistance == distanceMax) {
                minMaxNode = std::min(minMaxNode, nodeCurr);
            } 
        }
        ++distance;
        nodesVisited.at(nodeCurr) = true;
        nodeCurr = edges_.at(nodeCurr);
    } while(nodeCurr != -1 && !nodesVisited.at(nodeCurr));
    return minMaxNode == intT::max() ? -1 : minMaxNode;
}
