// problem : https://leetcode.com/problems/detect-cycles-in-2d-grid/description
// submission : https://leetcode.com/problems/detect-cycles-in-2d-grid/submissions/1989564129
// solution post : https://leetcode.com/problems/detect-cycles-in-2d-grid/solutions/8104899/c-modern-readable-code-beats-100-runtime-ohuo

// Approach : Disjoint Set Union (DSU) / Union-Find with Path Compression and Union by Rank
// Runtime : 3 ms, beats 100.00 %

// Complexity
// let 'n' by 'm' be the matrix size
// complexity :  O(n * m)
// complexity : O(n * m)

// import std;

namespace {

// Compile-time initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace

class DisjointSet final {
public:
    explicit DisjointSet(int const sz_) :
        mParents(sz_),
        mRanks(sz_, 1),
        mSz{sz_},
        mSetCnt{sz_}
    {
        std::ranges::iota(mParents, 0);
    }

    [[nodiscard]]
    auto Find(int const val_) -> int {
        // Apply path compression to flatten the tree for O(1) amortized lookup
        return mParents[val_] == val_ ? val_ : mParents[val_] = Find(mParents[val_]);
    }

    [[nodiscard]]
    auto Unite(
        int const val1_,
        int const val2_
    ) -> bool {
        auto parent1{Find(val1_)};
        auto parent2{Find(val2_)};
        // Both elements already share the same root, no need to unite
        if(parent1 == parent2) {
            return false;
        }
        auto & rank1{mRanks[parent1]};
        auto const rank2{mRanks[parent2]};
        // Apply union by rank to maintain a balanced tree
        if(rank1 < rank2) {
            std::swap(parent1, parent2);
        }
        mParents[parent2] = parent1;
        rank1 += rank2;
        --mSetCnt;
        return true;
    }

private:
    std::vector<int> mParents;
    std::vector<int> mRanks;
    int mSz{};
    int mSetCnt{};
};

class Solution final {
public:
    using mxT = std::vector<std::vector<char>>;

    [[nodiscard]]
    auto containsCycle(mxT const & grid_) const -> bool;
};

auto Solution::containsCycle(mxT const & grid_) const -> bool {
    namespace vs = std::views;

    auto const rSz{static_cast<int>(grid_.size())};
    auto const cSz{static_cast<int>(grid_.front().size())};
    auto ds{::DisjointSet{rSz * cSz}};
    for(auto const r: vs::iota(0, rSz)) {
        for(auto const c: vs::iota(0, cSz)) {
            // Convert 2D grid coordinates into a flattened 1D index
            auto const currCell{r * cSz + c};
            // Process only top and left neighbors to prevent redundant edges
            if(r > 0 && grid_[r][c] == grid_[r - 1][c]) {
                auto const aboveCell{(r - 1) * cSz + c};
                // Check if cycle present
                if(!ds.Unite(currCell, aboveCell)) {
                    return true;
                }
            }
            if(c > 0 && grid_[r][c] == grid_[r][c - 1]) {
                auto const leftCell{currCell - 1};
                // Check if cycle present
                if(!ds.Unite(currCell, leftCell)) {
                    return true;
                }
            }
        }
    }
    // Cycle not present
    return false;
}
