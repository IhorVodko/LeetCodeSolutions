// problem : https://leetcode.com/problems/count-the-number-of-complete-components/description/
// submission : https://leetcode.com/problems/count-the-number-of-complete-components/submissions/1583288472
// solution post : https://leetcode.com/problems/count-the-number-of-complete-components/solutions/6570206/
//     c-modern-readable-code-optimal-time-comp-or0w

// #include <queue>
// #include <vector>
// #include <unordered_set>

// let 'v' be a count of vertices
// let 'e' - count of edges
// time complexity O(e + v)
// space complexity O(e + v)
// runtime 60 ms, beats 47.69 %
class Solution {
public:
    int countCompleteComponents(
        int const verticesCount_,
        std::vector<std::vector<int>> const & edges_
    ) const {
        auto adjMx{std::vector<std::vector<int>>(verticesCount_,
            std::vector<int>{})};
        auto connectedVerticesUnique{std::unordered_set<int>{}};
        for(auto const & edge: edges_) {
            adjMx.at(edge.at(0)).emplace_back(edge.at(1));
            adjMx.at(edge.at(1)).emplace_back(edge.at(0));
            connectedVerticesUnique.insert(edge.begin(), edge.end());
        }
        auto const connectedVerticesCount{connectedVerticesUnique.size()};
        auto visitedVertices{std::vector<bool>(verticesCount_,
            false)};
        auto connectedVerticesQueue{std::queue<int>{}};
        auto completeConnectedComponentsCount{0};
        while(!connectedVerticesUnique.empty()) {
            connectedVerticesQueue.emplace(*connectedVerticesUnique.begin());
            visitedVertices.at(connectedVerticesQueue.front()) = true;
            connectedVerticesUnique.erase(connectedVerticesQueue.front());
            auto componentEdgesDoubleCount{0};
            auto componentVerticesCount{1};
            while(!connectedVerticesQueue.empty()) {
                auto const vertex{connectedVerticesQueue.front()};
                connectedVerticesQueue.pop();
                for(auto const & neighbour: adjMx.at(vertex)) {
                    if(visitedVertices.at(neighbour)) {
                        ++componentEdgesDoubleCount;
                        continue;
                    }
                    visitedVertices.at(neighbour) = true;
                    connectedVerticesUnique.erase(neighbour);
                    ++componentVerticesCount;
                    ++componentEdgesDoubleCount;
                    connectedVerticesQueue.emplace(neighbour);
                }
            }

            if((componentVerticesCount - 1) * componentVerticesCount ==
                componentEdgesDoubleCount
            ) {
                ++completeConnectedComponentsCount;
            }
        }
        completeConnectedComponentsCount += verticesCount_ -
            connectedVerticesCount;    
        return completeConnectedComponentsCount;
    }
};
