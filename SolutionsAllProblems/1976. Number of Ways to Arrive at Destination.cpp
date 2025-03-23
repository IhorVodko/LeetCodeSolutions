// problem : https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/description/
// submission : https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/submissions/1583338901
// solution post : https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/solutions/6570385/
//     c-modern-readable-code-optimal-time-comp-bhn2

// #include <queue>
// #include <limits>
// #include <vector>

namespace Utility{
    auto constexpr kMod{static_cast<int>(1e9 + 7)};
}

// let 'v' be a vertices count
// 'e' - edges count
// time complexity O((v + e) * log2(v))
// space complexity O(v + e)
// runtime 10 ms, beats 57.15 %
class Solution {
public:
    template<typename T_>
    using Arr2T = std::vector<std::vector<T_>>;
    int countPaths(
        int const nodesCount_,
        Arr2T<int> const & roads_
    ) const {
        using namespace Utility;
        using qValeuT_ = std::pair<long long, int>; 
        auto adjList{Arr2T<std::pair<int, int>>(nodesCount_)};
        for(auto const road: roads_) {
            auto const startNode{road.at(0)};
            auto const endNode{road.at(1)};
            auto const travelTime{road.at(2)};
            adjList.at(startNode).emplace_back(endNode, travelTime);
            adjList.at(endNode).emplace_back(startNode, travelTime);
        }
        auto minHeap{std::priority_queue<qValeuT_, std::vector<qValeuT_>,
            std::greater<>>{}};
        auto shortestTimeToNthNodes{std::vector<long long>(nodesCount_,
            std::numeric_limits<long long>::max())};
        auto pathCountToNthNodes{std::vector<int>(nodesCount_, 0)};
        shortestTimeToNthNodes.at(0) = 0;
        pathCountToNthNodes.at(0) = 1;
        minHeap.emplace(0, 0);
        while(!minHeap.empty()) {
            auto const [currTime, currNode]{minHeap.top()};
            minHeap.pop();
            if(currTime > shortestTimeToNthNodes.at(currNode)) {
                continue;
            }
            for(auto const & [neighbourNode, roadTime]: adjList.at(currNode)) {
                if(currTime + roadTime < shortestTimeToNthNodes.at(neighbourNode)
                ) {
                    shortestTimeToNthNodes.at(neighbourNode) = currTime + roadTime;
                    pathCountToNthNodes.at(neighbourNode) =
                        pathCountToNthNodes.at(currNode);
                    minHeap.emplace(shortestTimeToNthNodes.at(neighbourNode),
                        neighbourNode);
                } else if(currTime + roadTime ==
                    shortestTimeToNthNodes.at(neighbourNode)
                ) {
                    pathCountToNthNodes.at(neighbourNode) =
                        (pathCountToNthNodes.at(neighbourNode) +
                        pathCountToNthNodes.at(currNode)) % kMod;
                } 
            }
        } 
        return pathCountToNthNodes.at(nodesCount_ - 1);
    }
};
