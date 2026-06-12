// problem : https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-ii/description
// submission : https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-ii/submissions/2031136190
// solution post : https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-ii/solutions/8330277/
//    c-modern-readable-code-beats-100-runtime-4ddk

// Approach : DFS-Free Heavy-Light Decomposition with XOR Leaf Peeling & Combinatorics
// Runtime :  47 ms, beats 100.00 %

// Complexity
// let 'n' be the number of edges
// 'm' - number of queries
// Time :  O(n + m * log(n))
// Space : O(n)

// import std;

class Solution final {
public:
    [[nodiscard]]
    static auto assignEdgeWeights(
        std::vector<std::vector<int>> const & edges_,
        std::vector<std::vector<int>> const & queries_
    ) -> std::vector<int>;

private:
    static auto constexpr kMod{1'000'000'007};
    static auto constexpr kRoot{0};
    static auto constexpr kLeave{1};
    static auto constexpr kNotHeavy{-1};
};

auto Solution::assignEdgeWeights(
    std::vector<std::vector<int>> const & edges_,
    std::vector<std::vector<int>> const & queries_
) -> std::vector<int> {
    namespace rs = std::ranges;
    namespace vs = std::views;

    auto const nodesTot{static_cast<int>(edges_.size()) + 1};

    // 1. Precompute powers of 2 for O(1) query lookups
    auto powsOf2{std::vector<int>{1}};
    powsOf2.reserve(nodesTot + 1);
    for([[maybe_unused]] auto const j: vs::iota(1, nodesTot + 1)) {
        powsOf2.emplace_back((powsOf2.back() * 2) % kMod);
    } 

    // 2. Track degrees and XOR neighbor-sums instead of building an Adjacency List
    auto degreePerNode{std::vector<int>(nodesTot)};
    auto xorSumPerNode{std::vector<int>(nodesTot)};
    for(auto const & edge: edges_) {
        auto const node1{edge[0] - 1};
        auto const node2{edge[1] - 1};
        degreePerNode[node1]++;
        degreePerNode[node2]++;
        xorSumPerNode[node1] ^= node2;
        xorSumPerNode[node2] ^= node1;
    }

    // Queue for leaf peeling, explicitly avoiding node 0 (the root)
    auto leavesQ{std::vector<int>{}};
    leavesQ.reserve(nodesTot);
    for(auto const node: vs::iota(1, nodesTot)) {
        if(degreePerNode[node] == 1) {
            leavesQ.emplace_back(node);
        }
    }

    auto parents{std::vector<int>(nodesTot, -1)};
    // Stores the bottom-up processing sequence (topological sorting order)
    auto processingOrder{std::vector<int>{}};
    processingOrder.reserve(nodesTot - 1);

    // 3. "Peel" the tree layer by layer
    // Queue reading pointer
    auto headQ{0};
    while(headQ < leavesQ.size()) {
        auto const currNode{leavesQ[headQ++]};
        // For a leaf, its XOR sum is exactly its parent's ID
        auto const parent{xorSumPerNode[currNode]};

        parents[currNode] = parent;
        processingOrder.emplace_back(currNode);
        // "Remove" the edge by XORing the leaf out of the parent
        xorSumPerNode[parent] ^= currNode;
        --degreePerNode[parent];

        if(degreePerNode[parent] == kLeave && parent != kRoot) {
            leavesQ.emplace_back(parent);
        }
    }

    // 4. Build Heavy-Light Decomposition structures natively without recursion
    auto subtreeSzPerNode{std::vector<int>(nodesTot, 1)};
    auto heavyChildPerNode{std::vector<int>(nodesTot, -1)};

    // Bottom-up pass for subtree sizes and identifying heavy children
    for(auto const currNode: processingOrder) {
        auto const parent{parents[currNode]};
        subtreeSzPerNode[parent] += subtreeSzPerNode[currNode];
        if( auto & heavyChild{heavyChildPerNode[parent]};
            heavyChild == kNotHeavy ||
            subtreeSzPerNode[currNode] > subtreeSzPerNode[heavyChild]
        ) {
            heavyChild = currNode;
        }
    }

    auto depthPerNode{std::vector<int>(nodesTot, 0)};
    // Heavy-Light Decomposition chains
    auto chainHeadPerNode{std::vector<int>(nodesTot, 0)};

    // Top-down pass for depth and HLD chain heads
    for(auto const currNode: vs::reverse(processingOrder)) {
        auto const parent{parents[currNode]};
        depthPerNode[currNode] = depthPerNode[parent] + 1;
        // If currNode is the heavy child, extend the chain; otherwise, start a new one
        chainHeadPerNode[currNode] = (currNode == heavyChildPerNode[parent]) ?
            chainHeadPerNode[parent] : currNode;
    }

    // 6. Calculate Lowest Common Ancestor and Edge Distances
    auto const CalcDist{[&] [[nodiscard]] (auto node1_, auto node2_) {
        auto origNode1_{node1_};
        auto origNode2_{node2_};
        while(chainHeadPerNode[node1_] != chainHeadPerNode[node2_]) {
            if( depthPerNode[chainHeadPerNode[node1_]] <
                depthPerNode[chainHeadPerNode[node2_]]
            ) {
                std::swap(node1_, node2_);
            }
            node1_ = parents[chainHeadPerNode[node1_]];
        }
        auto const lcaNode{depthPerNode[node1_] < depthPerNode[node2_] ? node1_ : node2_};
        // Distance formula between two nodes 'u' and 'v' using depths:
        // depth(u) + depth(v) - 2 * depth(lca)
        return depthPerNode[origNode1_] + depthPerNode[origNode2_] - 2 * depthPerNode[lcaNode];
    }};

    // 7. Resolve queries
    auto const ProcessQuery{[&] [[nodiscard]] (auto const & query_) {
        auto const dist{CalcDist(query_[0] - 1, query_[1] - 1)};
        // Closed-form combinatorics formula to calculate exact number of valid edge
        // weight assignments that result in an odd path sum : 2^(depth - 1).
        return dist == 0 ? 0 : powsOf2[dist - 1];
    }};

    return queries_ | vs::transform(ProcessQuery) | rs::to<std::vector<int>>();
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
