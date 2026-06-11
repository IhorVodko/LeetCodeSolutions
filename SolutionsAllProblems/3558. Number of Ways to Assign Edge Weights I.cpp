// problem : https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-i/description
// submission : https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-i/submissions/2030015225
// solution post : https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-i/solutions/8328401/
//    c-modern-readable-code-optimal-time-comp-0e6n

// Approach : Bottom-Up Tree Peeling (BFS) with XOR Parent Tracking
// Runtime : 19 ms, beats 99.33 %

// Complexity
// let 'n' be the number of edges
// Time :  O(n)
// Space : O(n)

// import std;

class Solution final {
public:
    [[nodiscard]]
    static auto assignEdgeWeights(std::vector<std::vector<int>> const & edges_) -> int;

private:
    static auto constexpr kMod{1'000'000'007uz};
};

auto Solution::assignEdgeWeights(std::vector<std::vector<int>> const & edges_) -> int {
    namespace rs = std::ranges;
    namespace vs = std::views;

    auto const nodesTot{edges_.size() + 1uz};
    // Track the number of connections (degree) for each node.
    auto degreePerNode{std::vector<size_t>(nodesTot)};
    // Track the XOR sum of all connected neighbors for each node.
    auto neighborsPerNode{std::vector<size_t>(nodesTot)};

    // Populate degrees and XOR sums. Shift 1-based indexing to 0-based.
    for(auto const & edge: edges_) {
        auto const from{edge[0uz] - 1uz};
        auto const to{edge[1uz] - 1uz};

        ++degreePerNode[from];
        ++degreePerNode[to];
        neighborsPerNode[from] ^= to;
        neighborsPerNode[to] ^= from;
    }

    auto const IsLeaf{[&] (size_t const node_) {
        return degreePerNode[node_] == 1uz;
    }};

    // Queue for BFS, pre-allocated to prevent heap reallocations.
    auto leavesQ{std::vector<size_t>{}};
    leavesQ.reserve(nodesTot);

    // Find initial leaves (skip node 0, the root, to peel bottom-up).
    rs::copy(vs::iota(1uz, nodesTot) | vs::filter(IsLeaf), std::back_inserter(leavesQ));

    auto combCnt{1uz};
    auto lvlBegin{0uz};

    // Peel the tree level by level, moving up towards the root.
    while(lvlBegin< leavesQ.size()) {
        auto const lvlEnd{leavesQ.size()};
        auto const currLvl{std::span{
            leavesQ.cbegin() + lvlBegin, leavesQ.cbegin() + lvlEnd
        }};

        lvlBegin = lvlEnd;

        for(auto const leaf: currLvl) {
            // For a leaf, its XOR sum is exactly its parent's ID.
            auto const parent{neighborsPerNode[leaf]};

            // Node 0 is the root. If parent is 0, we stop peeling.
            if(parent == 0uz) {
                continue;
            }

            // "Remove" the edge by XORing the leaf out.
            neighborsPerNode[parent] ^= leaf;

            --degreePerNode[parent];
            if(IsLeaf(parent)) {
                leavesQ.emplace_back(parent);
            }
        }

        // Multiply by 2 for each level peeled.
        combCnt %= kMod;
        combCnt *= 2uz;
    }

    // The final result represents 2^(depth - 1).
    return static_cast<int>(combCnt / 2uz);
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
