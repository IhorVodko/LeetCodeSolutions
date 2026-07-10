// problem : https://leetcode.com/problems/path-existence-queries-in-a-graph-ii/description
// submission : https://leetcode.com/problems/path-existence-queries-in-a-graph-ii/submissions/2063186760
// solution post : https://leetcode.com/problems/path-existence-queries-in-a-graph-ii/solutions/8388820/
//    modern-readable-code-optimal-time-comple-9ytg

// Approach : Sorting & Binary Lifting (Sparse Table)
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the number of nodes
// 'm' - number of queries
// Time :  O((n + m) * log(n))
// Space : O(n * log(n))

// import std;

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

// 2^18 > 10^5, sufficient for max node count
auto constexpr kMax2Exp{18};
// Problem constraint for maximum node count
auto constexpr KMaxNodeTot_{100'005};
// Sparse table for binary lifting
auto gJumps{std::array<std::array<int, kMax2Exp>, KMaxNodeTot_>{}};

struct Node final {
    int id{};
    int val{};
};

} // namespace 

class Solution final {
public:
    [[nodiscard]]
    static auto pathExistenceQueries(
        int const nodeTot_, 
        std::vector<int> & nums_,
        int const maxDiff_,
        std::vector<std::vector<int>> const & queries_
    ) -> std::vector<int>;
};

auto Solution::pathExistenceQueries(
    int const nodeTot_, 
    std::vector<int> & nums_,
    int const maxDiff_,
    std::vector<std::vector<int>> const & queries_
) -> std::vector<int> {
    // Associate values with original indices to track them after sorting
    auto nodes{
        nums_ |
        vs::enumerate |
        vs::transform([] (auto const & idxAndVal_) { 
            auto const [idx, val_] = idxAndVal_;
            return Node{static_cast<int>(idx), val_}; 
        }) |
        rs::to<std::vector>() 
    };

    rs::sort(nodes, {}, &Node::val);

    // Map original index to its new position in the sorted array
    auto posSorted{std::vector<int>(nodeTot_)};
    for(auto const j: vs::iota(0, nodeTot_)) {
        posSorted[nodes[j].id] = j;
    }

    // Determine the farthest reachable node moving right via valid steps
    auto reach{std::vector<int>(nodeTot_, -1)};
    reach[nodeTot_ - 1] = nodeTot_ - 1;
    for(auto const j: vs::iota(0, nodeTot_ - 1) | vs::reverse) {
        if(nodes[j + 1].val - nodes[j].val <= maxDiff_) {
            reach[j] = reach[j + 1];
        } else {
            reach[j] = j;
        } 
    }

    // Precompute the maximum 1-step jump for each node
    auto left{0};
    for(auto const right: vs::iota(0, nodeTot_)) {
        while(nodes[right].val - nodes[left].val > maxDiff_) {
            gJumps[left][0] = right - 1;
            ++left;
        }
    }
    while(left < nodeTot_) {
        gJumps[left][0] = nodeTot_ - 1;
        ++left;
    }

    // Build the sparse table for jump distances of powers of 2
    for(auto const k: vs::iota(1, kMax2Exp)) {
        for(auto const j: vs::iota(0, nodeTot_) | vs::reverse) {
            gJumps[j][k] = gJumps[gJumps[j][k - 1]][k - 1];
        }
    }

    auto const solve{[&] (auto const & query_) {
        // Translate original query indices into the sorted domain
        auto leftIdx{posSorted[query_[0]]};
        auto rightIdx{posSorted[query_[1]]};

        // Always traverse left to right in the sorted array
        if(leftIdx > rightIdx) std::swap(leftIdx, rightIdx);
        if(leftIdx == rightIdx) return 0;

        // Target is unreachable from the starting node
        if(reach[leftIdx] < rightIdx) return -1;

        // Find minimum jumps to reach or exceed target using binary lifting
        auto jmp{0};
        for(auto const k: vs::iota(0, kMax2Exp) | vs::reverse) {
             // If taking 2^k jumps keeps us strictly before the target, take it
            if(gJumps[leftIdx][k] < rightIdx) {
                leftIdx = gJumps[leftIdx][k];
                jmp |= (1 << k);
            }
        }

        // Because we already confirmed reachability using the `reach` array, we know
        // exactly 1 more jump will securely land on or past 'rightIdx'.
        return jmp + 1;
    }};

    return 
        queries_ |
        vs::transform(solve) |
        rs::to<std::vector>()
    ;
}
