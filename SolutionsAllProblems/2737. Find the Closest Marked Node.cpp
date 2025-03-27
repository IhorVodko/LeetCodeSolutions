// problem : https://leetcode.com/problems/find-the-closest-marked-node/description/
// submission : https://leetcode.com/problems/find-the-closest-marked-node/submissions/1588359926
// solution post : https://leetcode.com/problems/find-the-closest-marked-node/solutions/6586941/
//     c-modern-readable-code-beats-99-runtime-9if70

// #include <queue>
// #include <limits>
// #include <vector>
// #include <unordered_map>
// #include <unordered_set>

// let 'v' be a vertices count
// 'e' - edges count
// time complexity O((v + e) * log(v))
// space complexity O(e + v)
// runtime 3 ms, beats 98.53 %
class Solution {
public:
    using Arr2T = std::vector<std::vector<int>>;
    int minimumDistance(
        int const n_,
        Arr2T & edges_,
        int const s_,
        std::vector<int> const & marked_
    ) const {
        using qValueT = std::pair<int, int>;
        auto constexpr kMaxDistance{std::numeric_limits<int>::max()};
        auto adjList{std::unordered_map<int,
            std::vector<std::pair<int, int>>>{}};
        for(auto const & edge: edges_) {
            auto const nodeStart{edge.at(0)};
            auto const nodeDestination{edge.at(1)};
            auto const weight{edge.at(2)};
            adjList[nodeStart].emplace_back(weight, nodeDestination);
        }
        auto minDistances{std::vector<int>(n_, kMaxDistance)};
        auto nodes{std::priority_queue<qValueT, std::vector<qValueT>,
            std::greater<>>{}};
        nodes.emplace(0, s_);
        minDistances.at(s_) = 0;
        auto markedNodesSet{std::unordered_set<int>{marked_.begin(),
            marked_.end()}};
        while(!nodes.empty()) {
            auto const [distance, nodeStart]{nodes.top()};
            nodes.pop();
            if(markedNodesSet.contains(nodeStart)) {
                return minDistances.at(nodeStart);
            }
            for(auto const [weight, nodeDestination]: adjList[nodeStart]
            ) {
                auto const newDistance{distance + weight};
                if(newDistance < minDistances.at(nodeDestination)) {
                    minDistances.at(nodeDestination) = newDistance;
                    nodes.emplace(newDistance, nodeDestination);
                }
            } 
        }
        return -1;
    }
};
