// problem : https://leetcode.com/problems/largest-color-value-in-a-directed-graph/description
// submission : https://leetcode.com/problems/largest-color-value-in-a-directed-graph/submissions/1645219250
// solution post : https://leetcode.com/problems/largest-color-value-in-a-directed-graph/solutions/6783823/
//    c-modern-readable-code-optimal-time-comp-otf1

// #include <algorithm>
// #include <queue>
// #include <vector>

namespace Utility {
    auto constexpr kAlphabetStart{'a'};
    auto constexpr kAlphabetSize{26};
}

class Solution {
public:
    template<typename T_>
    using Arr2T = std::vector<std::vector<T_>>;
// let 'e' be a count of edges given
// time complexity O(e)
// space complexity O(e)
// runtime 407 ms, beats 39.47 %
    int largestPathValue(
        std::string const & colors_,
        Arr2T<int> const & edges_
    ) const;
};

int Solution::largestPathValue(
    std::string const & colors_,
    Arr2T<int> const & edges_
) const {
    using namespace Utility;
    auto nodesCount{colors_.size()};
    auto nodeToNeighbors{Arr2T<int>(nodesCount)};
    auto indegrees{std::vector<int>(nodesCount, 0)};
    for(auto const & edge: edges_) {
        nodeToNeighbors.at(edge.at(0)).emplace_back(edge.at(1));
        ++indegrees.at(edge.at(1));
    }
    auto colorsCounts{Arr2T<int>(nodesCount,
        std::vector<int>(kAlphabetSize, 0))};
    auto qNodes{std::queue<int>{}};
    for(auto i{0}; i < nodesCount; ++i) {
        if(indegrees.at(i) == 0) {
            qNodes.emplace(i);
        }
    }
    auto sameColorCountMax{0};
    auto nodesSeen{0};
    while(!qNodes.empty()) {
        auto const node{qNodes.front()};
        qNodes.pop();
        sameColorCountMax = std::max(sameColorCountMax,
            ++colorsCounts.at(node).at(colors_.at(node) - kAlphabetStart));
        ++nodesSeen;
        for(auto const neighbor: nodeToNeighbors.at(node)) {
            for(auto i{0}; i < kAlphabetSize; ++i) {
                colorsCounts.at(neighbor).at(i) =
                    std::max(colorsCounts.at(neighbor).at(i),
                        colorsCounts.at(node).at(i));
            }
            if(--indegrees.at(neighbor) == 0) {
                qNodes.emplace(neighbor);
            }
        }
    }
    sameColorCountMax = nodesSeen < nodesCount ? -1 : sameColorCountMax;
    return sameColorCountMax;
}
