// problem : https://leetcode.com/problems/find-the-maximum-sum-of-node-values/description/
// submission : https://leetcode.com/problems/find-the-maximum-sum-of-node-values/submissions/1644288202
// solution post : https://leetcode.com/problems/find-the-maximum-sum-of-node-values/solutions/6780787/
//    c-modern-readable-code-beats-100-by-cybe-8aqv

// #include <algorithm>
// #include <limits>
// #include <vector>

class Solution {
public:
    template<typename T_>
    using Arr2T = std::vector<std::vector<T_>>;
// let 'n' be a given nodes count
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    long long maximumValueSum(
        std::vector<int> const & nodeVals_,
        int const num_,
        Arr2T<int> const & edges_
    ) const;
};

long long Solution::maximumValueSum(
    std::vector<int> const & nodeVals_,
    int const num_,
    Arr2T<int> const & edges_
) const {
    using intT = std::numeric_limits<int>;
    auto nudeValsSum{0ll};
    auto nodesModifiedCount{0};
    auto nodesValPositiveMin{intT::max()};
    auto nodesValNegativeMax{intT::min()}; 
    for(auto const nodeValue: nodeVals_) {
        auto const nodeValModified{nodeValue ^ num_};
        nudeValsSum += nodeValue;
        auto const nodeValDiff{nodeValModified - nodeValue};
        if(nodeValDiff > 0) {
            nodesValPositiveMin = std::min(nodesValPositiveMin, nodeValDiff);
            nudeValsSum += nodeValDiff;
            ++nodesModifiedCount;
        } else {
            nodesValNegativeMax = std::max(nodesValNegativeMax, nodeValDiff);
        }
    }
    auto const nodesValSumMax{nodesModifiedCount % 2 == 0 ? nudeValsSum :
        std::max(nudeValsSum - nodesValPositiveMin,
            nudeValsSum + nodesValNegativeMax)};
    return nodesValSumMax;
}
