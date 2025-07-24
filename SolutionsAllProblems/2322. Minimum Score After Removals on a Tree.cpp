// problem : https://leetcode.com/problems/minimum-score-after-removals-on-a-tree/description/
// submission : https://leetcode.com/problems/minimum-score-after-removals-on-a-tree/submissions/1710065678
// solution post : https://leetcode.com/problems/minimum-score-after-removals-on-a-tree/solutions/7000173/
//    c-modern-readable-code-optimal-time-comp-44do

// #include <algorithm>
// #include <limits>
// #include <vector>

namespace Util {
    inline auto constexpr kDummyNode{-1};
    inline auto constexpr kRootNode{0};
}

class Solution {
public:
    using nodeT = int;
    using edgeT  = std::vector<nodeT>;
    using edgesT = std::vector<edgeT>;
    using mxT = std::vector<std::vector<nodeT>>;
// let 'n' be a count of nodes in the given tree
// time complexity O(n^2)
// space complexity O(n)
// runtime 203 ms, beats 52.38 %
    int minimumScore(
        std::vector<nodeT> const & nodes_,
        edgesT const & edges_
    );
private:
    void DoDfs(
        std::vector<nodeT> const & nodes_,
        nodeT const currNode_,
        nodeT const nextNode_
    );
    int CalculateScore(
        int const tree1Value_,
        int const tree2Value_,
        int const tree3Value_
    ) const;
    size_t mNodeCounter{0};
    std::vector<size_t> mTreeVals;
    std::vector<nodeT> mStartNodes;
    std::vector<nodeT> mEndNodes;
    mxT mAdjMx;
};

int Solution::minimumScore(
    std::vector<nodeT> const & nodes_,
    edgesT const & edges_
) {
    using namespace Util;
    using sizetT = std::numeric_limits<size_t>; 
    using intT = std::numeric_limits<int>; 
    auto const treeSz{nodes_.size()};
    mNodeCounter = 0;
    mTreeVals = std::vector<size_t>(treeSz, sizetT::min());
    mStartNodes = std::vector<nodeT>(treeSz, intT::min());
    mEndNodes = std::vector<nodeT>(treeSz, intT::min());
    mAdjMx = mxT(treeSz, std::vector<nodeT>{});
    for(auto & edge: edges_) {
        mAdjMx.at(edge.at(0)).emplace_back(edge.at(1));
        mAdjMx.at(edge.at(1)).emplace_back(edge.at(0));
    }
    DoDfs(nodes_, kRootNode, kDummyNode);
    auto minScore{intT::max()};
    for(auto startNode{1}; startNode < treeSz; ++startNode) {
        for(auto endNode{startNode + 1}; endNode < treeSz; ++endNode) {
            auto tree1Val{0};
            auto tree2Val{0};
            auto tree3Val{0};
            if( mStartNodes.at(endNode) > mStartNodes.at(startNode) &&
                mStartNodes.at(endNode) < mEndNodes.at(startNode)
            ) {
                tree1Val = mTreeVals.at(0) ^ mTreeVals.at(startNode);
                tree2Val = mTreeVals.at(startNode) ^ mTreeVals.at(endNode);
                tree3Val = mTreeVals.at(endNode);
            } else if(
                mStartNodes.at(startNode) > mStartNodes.at(endNode) &&
                mStartNodes.at(startNode) < mEndNodes.at(endNode)
            ) {
                tree1Val = mTreeVals.at(0) ^ mTreeVals.at(endNode);
                tree2Val = mTreeVals.at(endNode) ^ mTreeVals.at(startNode);
                tree3Val = mTreeVals.at(startNode);
            } else {
                tree1Val = mTreeVals.at(0) ^ mTreeVals.at(startNode) ^ mTreeVals.at(endNode);
                tree2Val = mTreeVals.at(startNode);
                tree3Val = mTreeVals.at(endNode);
            }
            auto const currScore{CalculateScore(tree1Val, tree2Val, tree3Val)};
            minScore = std::min(minScore, currScore);
        }
    }
    return minScore;
}

void Solution::DoDfs(
    std::vector<nodeT> const & nodes_,
    nodeT const currNode_,
    nodeT const nextNode_
) {
    mStartNodes.at(currNode_) = mNodeCounter++;
    mTreeVals.at(currNode_) = nodes_.at(currNode_);
    for(auto const node: mAdjMx.at(currNode_)) {
        if(node == nextNode_) {
            continue;
        }
        DoDfs(nodes_, node, currNode_);
        mTreeVals.at(currNode_) ^= mTreeVals.at(node);
    }
    mEndNodes.at(currNode_) = mNodeCounter;
}

int Solution::CalculateScore(
    int const tree1Value_,
    int const tree2Value_,
    int const tree3Value_
) const {
    auto const maxTreeVal{std::max({tree1Value_, tree2Value_, tree3Value_})};
    auto const minTreeVal{std::min({tree1Value_, tree2Value_, tree3Value_})};
    auto const score{maxTreeVal - minTreeVal};
    return score;
}
