// problem :  https://leetcode.com/problems/maximum-number-of-k-divisible-components/description/
// submission : https://leetcode.com/problems/maximum-number-of-k-divisible-components/submissions/1484793309
// solution post : https://leetcode.com/problems/maximum-number-of-k-divisible-components/solutions/6171786/c-modern-readable-code-by-cyberartist-5voc


// #include <vector>
// #include <unordered_map>


// let 'n' be a number of nodes
// time complexity O(n)
// space complexity O(n)
// runtime 217 ms, beats 24.05 %
class Solution {
using EdgeT = std::vector<int>;
using EdgesT = std::vector<EdgeT>;
using AdjMxT = std::unordered_map<int, std::vector<int>>;
public:
    int maxKDivisibleComponents(
        int nodesTotal,
        EdgesT const & edges,
        std::vector<int> const & nodeValues,
        int const divisor
    ) {
        reset(nodesTotal, divisor, nodeValues, edges);
        creatAdjMx();
        DoDfsRecursion(nodeRoot, nodeDummy);
        return nodesCountMax;
    }
    Solution() :
        nodesCountMax{0},
        divisor{1}
    {}
private:
    void reset(
        int const nodesTotal,
        int const divisor,
        std::vector<int> const & nodeValues,
        EdgesT const & edges
    ) {
        adjMx.clear();
        this->divisor = divisor;
        nodesCountMax = 0;
        this->nodeValues = nodeValues;
        this->edges = edges;
    }
    void creatAdjMx() {
        for(auto const & edge: edges) {
            adjMx[edge.front()].emplace_back(edge.back());
            adjMx[edge.back()].emplace_back(edge.front());
        }
    }
    int DoDfsRecursion(
        int const nodeThis,
        int const nodeParent
    ) {
        auto sum{0};
        for(auto const nodeConnected: adjMx[nodeThis]) {
            if(nodeConnected != nodeParent) {
                sum += DoDfsRecursion(nodeConnected, nodeThis);
            }
            sum %= divisor;
        }
        sum += nodeValues.at(nodeThis);
        if((sum %= divisor) == 0) {
            ++nodesCountMax;
        }
        return sum;
    }
    auto static constexpr nodeRoot{0};
    auto static constexpr nodeDummy{-1};
    int nodesCountMax;
    int divisor;
    AdjMxT adjMx;
    std::vector<int> nodeValues;
    EdgesT edges;
};
