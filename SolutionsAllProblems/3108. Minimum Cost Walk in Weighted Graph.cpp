// problem : https://leetcode.com/problems/minimum-cost-walk-in-weighted-graph/description/
// submission : https://leetcode.com/problems/minimum-cost-walk-in-weighted-graph/submissions/1581275084
// solution post : https://leetcode.com/problems/minimum-cost-walk-in-weighted-graph/solutions/6562909/
//     c-modern-readable-code-optimal-time-comp-dghe

// #include <limits>
// #include <vector>

// let 'n' be a nodes count
// 'e' - edges count
// 'q' - queries count
// time complexity O(n + e + q)
// space complexity O(n + e)
// runtime 131 ms, beats 40.41 %
class Solution {
public:
    template<typename T>
    using Arr2T = std::vector<std::vector<T>>;
    std::vector<int> minimumCost(
        int const n_,
        Arr2T<int> const & edges_,
        Arr2T<int> const & queries_
    ) const {
        auto adjList{Arr2T<std::pair<int, int>>(n_)};
        for(auto const & edge: edges_) {
            adjList.at(edge.at(0)).push_back({edge.at(1), edge.at(2)});
            adjList.at(edge.at(1)).push_back({edge.at(0), edge.at(2)});
        }
        auto visitedNodes{std::vector<bool>(n_, false)};
        auto components{std::vector<int>(n_, 0)};
        auto componentsCost{std::vector<int>{}};
        auto componentId{0};
        for(auto node{0}; node < n_; ++node) {
            if(!visitedNodes.at(node)) {
                componentsCost.emplace_back(GetComponentCost(node, adjList,
                    visitedNodes, components, componentId));
                ++componentId;
            }
        }
        auto results{std::vector<int>{}};
        for(auto const & query: queries_) {
            auto const start{query.at(0)};
            auto const end{query.at(1)};
            if(components[start] == components[end]) {
                results.emplace_back(componentsCost[components[start]]);
            } else {
                results.emplace_back(-1);
            }
        }
        return results;
    }
private:
    int GetComponentCost(
        int const source_,
        Arr2T<std::pair<int, int>> const & adjList_,
        std::vector<bool> & visited_,
        std::vector<int> & components,
        int const componentId_
    ) const {
        auto nodes{std::queue<int>{}};
        auto componentsCost{std::numeric_limits<int>::max()};
        nodes.push(source_);
        visited_.at(source_) = true;
        while(!nodes.empty()) {
            auto node{nodes.front()};
            nodes.pop();
            components.at(node) = componentId_;
            for(auto const [neighbour, weight]: adjList_.at(node)) {
                componentsCost &= weight;
                if(!visited_.at(neighbour)) {
                    visited_.at(neighbour) = true;
                    nodes.emplace(neighbour); 
                }
            }
        }
        return componentsCost;
    }
};
