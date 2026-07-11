// problem : https://leetcode.com/problems/count-the-number-of-complete-components/description/
// submission : https://leetcode.com/problems/count-the-number-of-complete-components/submissions/2064001465
// solution post : https://leetcode.com/problems/count-the-number-of-complete-components/solutions/8390456/
//        modern-readable-code-optimal-time-comple-oxze

// Approach : Disjoint Set Union (Union-Find) with Component Tracking
// Runtime : 0 ms, beats 100.00 %

// let 'n' be the number of nodes
// 'm' - number of edes
// a(n) - the Inverse Ackermann function
// Time :  O(n + m * a(n))
// Space : O(n)

// import std;

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

// Disjoint Set tracking component sizes and edge counts.
class DS final {
public:
    explicit DS(int const nodeTot_) :
        mParents(nodeTot_),
        mNodeTotals(nodeTot_, 1),
        mEdgeTotals(nodeTot_)
    {
        rs::iota(mParents, 0);
    }

    template<rs::input_range R_>
    explicit DS(
        std::from_range_t,
        R_ && edges_,
        int const nodeTot_
    ) :
        DS{nodeTot_}
    {
        for(auto const & edge: edges_) {
            AddEdge(edge[0], edge[1]);
        }
    }

    [[nodiscard]]
    auto IsComplete(auto const root_) const -> bool {
        // Complete graph property is verified only at the component's root.
        if(mParents[root_] != root_) {
            return false;
        }
        auto const nodeTot{mNodeTotals[root_]};
        auto const edgeTot{mEdgeTotals[root_]};

        // Check if the component has the maximum possible number of edges.
        return edgeTot == nodeTot * (nodeTot - 1) / 2;
    }

private:
    [[nodiscard]]
    auto Find(int const node_) -> int {
        if(mParents[node_] == node_) {
            return node_;
        }
        // Path compression.
        return mParents[node_] = Find(mParents[node_]);
    }

    auto AddEdge(
        int const node1_,
        int const node2_
    ) -> void {
        auto const root1{Find(node1_)};
        auto const root2{Find(node2_)};

        // Track an internal edge within an existing component.
        if(root1 == root2) {
            mEdgeTotals[root2] += 1;
        } else {
            // Merge components and aggregate their node and edge totals.
            mParents[root1] = root2;
            mNodeTotals[root2] += mNodeTotals[root1];
            mEdgeTotals[root2] += mEdgeTotals[root1] + 1;
        }
    }

    std::vector<int> mParents;
    std::vector<int> mNodeTotals;
    std::vector<int> mEdgeTotals;
};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    static auto countCompleteComponents(
        int const nodeTot_, 
        std::vector<std::vector<int>> const & edges_
    ) -> int;
};

auto Solution::countCompleteComponents(
    int const nodeTot_, 
    std::vector<std::vector<int>> const & edges_
) -> int {
    // Count all valid roots representing complete components.
    return static_cast<int>(rs::count_if(
        vs::iota(0, nodeTot_),
        [ds{edges_ | rs::to<DS>(nodeTot_)}] (auto const node_) {
            return ds.IsComplete(node_);
        }     
    ));
}
