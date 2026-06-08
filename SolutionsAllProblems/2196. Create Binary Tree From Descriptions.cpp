// problem : https://leetcode.com/problems/create-binary-tree-from-descriptions/description
// submission : https://leetcode.com/problems/create-binary-tree-from-descriptions/submissions/2026596983
// solution post : https://leetcode.com/problems/create-binary-tree-from-descriptions/solutions/8321865/
//    c-modern-readable-code-optimal-time-comp-366e

// Approach : Hash Map Node Tracking
// Runtime : 163 ms, beats 87.87 %

// Complexity
// let 'n' be the number of node descriptions
// complexity :  O(n)
// complexity : O(n)

// import std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution final {
public:
    using nodeP = TreeNode *;

    [[nodiscard]]
    static auto createBinaryTree(
        std::vector<std::vector<int>> const & treeDescription_
    ) -> nodeP;

private:
    static auto constexpr kParentValIdx{0};
    static auto constexpr kChildValIdx{1};
    static auto constexpr kIsLeftChildIdx{2};
};

auto Solution::createBinaryTree(
    std::vector<std::vector<int>> const & treeDescription_
) -> nodeP {
    namespace vs = std::views;
    namespace rs = std::ranges;

    // Maps values to their corresponding tree nodes.
    auto nodeValToNodeP{std::unordered_map<int, nodeP>{}};
    nodeValToNodeP.reserve(treeDescription_.size() + 1);

    // Helper to fetch an existing node or create a new one.
    auto const ProcessVal{[&] (auto const val_) {
        auto const [nodeValToNodePIt, isInserted]{
            nodeValToNodeP.try_emplace(val_, nullptr)
        };
        auto & NodeP{nodeValToNodePIt->second};

        if(isInserted) {
            NodeP = new TreeNode{val_};
        }

        return NodeP;
    }};

    // Construct the tree structure.
    for(auto const & nodeDesc: treeDescription_) {
        auto const parentNodeP{ProcessVal(nodeDesc[kParentValIdx])};
        auto const childNodeP{ProcessVal(nodeDesc[kChildValIdx])};

        (nodeDesc[kIsLeftChildIdx] ? parentNodeP->left : parentNodeP->right) = childNodeP;
    }

    // Identify all nodes that have parents.
    auto const childVals{
        treeDescription_ |
        vs::transform([] (auto const & nodeDesc_) {return nodeDesc_[kChildValIdx]; }) |
        rs::to<std::unordered_set>()
    };

    // The root is the only node without a parent.
    auto const rootValAndPIt{rs::find_if(
        nodeValToNodeP,
        [&] (auto const & nodeValAndNodeP_) {
            return !childVals.contains(nodeValAndNodeP_.first);
        }
    )};

    return rootValAndPIt->second;
}

namespace {

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace
