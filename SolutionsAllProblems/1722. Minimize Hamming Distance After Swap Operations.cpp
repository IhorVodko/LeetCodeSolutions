// problem : https://leetcode.com/problems/minimize-hamming-distance-after-swap-operations/description
// submission : https://leetcode.com/problems/minimize-hamming-distance-after-swap-operations/submissions/1984761550
// solution post : https://leetcode.com/problems/minimize-hamming-distance-after-swap-operations/solutions/8038924/
//    c-modern-readable-code-beats-100-runtime-hvrd

// Approach : Disjoint Set Union (DSU) with Component Frequency Counting
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the length of the arrays (source and target)
// 'm' - number of the allowed swaps
// 'K' - maximum value in the arrays (source and target)
// complexity :  O(n + m + K)
// complexity : O(n + K)

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

// DisjointSet class to manage connected components using union-find with path compression
// and union by rank optimizations.
class DisjointSet final {
public:
    // Initialize roots and ranks for the given size.
    explicit DisjointSet(int const sz_) :
        mRoots(sz_),
        mRanks(sz_)
    {
        // Set each element to be its own root initially.
        std::ranges::iota(mRoots, 0);
    }

    // Find the root of the given element with path compression.
    [[nodiscard]]
    auto Find(int const val_) -> int {

        auto & root{mRoots[val_]};

        // Recursively find the root and compress the path.
        return (val_ == root) ? val_ : root = Find(root);
    } 

    // Union two elements into the same set using union by rank.
    auto Union(
        int val1_,
        int val2_
    ) -> void {
        // Find the roots of both elements.
        val1_ = Find(val1_);
        val2_ = Find(val2_);

        // If they are already in the same set, do nothing.
        if(val1_ == val2_) {
            return;
        }

        // Get the ranks of the roots to determine which tree to merge into which.
        auto rank1{mRanks[val1_]};
        auto rank2{mRanks[val2_]};

        // Ensure rank1 is less than or equal to rank2 to keep the tree shallow.
        if(rank1 > rank2) {
            std::swap(val1_, val2_);
        }

        // Attach the shorter tree to the root of the taller tree.
        mRoots[val1_] = val2_;

        // If ranks are equal, increment the rank of the new root.
        if(rank1 == rank2) {
            ++rank2;
        }
    }

private:
    // Stores the root of each element.
    std::vector<int> mRoots{};
    // Stores the rank (approximate depth) of each tree.
    std::vector<int> mRanks{};
};

class Solution final {
public:
    [[nodiscard]]
    auto minimumHammingDistance(
        std::vector<int> const & sourceNums_,
        std::vector<int> const & targetNums_,
        std::vector<std::vector<int>> const & allowedSwaps_
    ) const -> int;
};

auto Solution::minimumHammingDistance(
    std::vector<int> const & sourceNums_,
    std::vector<int> const & targetNums_,
    std::vector<std::vector<int>> const & allowedSwaps_
) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto const numsSz{static_cast<int>(sourceNums_.size())};
    // Initialize the disjoint set to group allowed swaps.
    auto ds{DisjointSet{numsSz}};

    // Process each allowed swap and unite the corresponding indices.
    for(auto const & swap: allowedSwaps_) {
        ds.Union(swap[0], swap[1]);
    }

    // Create a 2D vector to group indices by their root component.
    auto setPerIdx{std::vector<std::vector<int>>(numsSz)};

    // Iterate through all indices and group them by their disjoint set root.
    for(auto const idx: vs::iota(0, numsSz)) {
        auto const root{ds.Find(idx)};

        setPerIdx[root].emplace_back(idx);    
    }

    // The count of matching elements.
    auto numMatchCnt{0};

    // Find the max number in both source and target arrays to size the frequency map.
    auto const maxNum{
        std::max(*rngs::max_element(sourceNums_), *rngs::max_element(targetNums_))};
    // A frequency array to count occurrences of numbers in a component.
    auto numCnts{std::vector<int>(maxNum + 1)};

    // Iterate through each component group.
    for(auto const j: vs::iota(0, numsSz)) {
        auto const & set{setPerIdx[j]};

        if(set.empty()) {
            continue;
        }

        // Count the occurrences of each source number in the current component.
        for(auto const idx: set) {
            ++numCnts[sourceNums_[idx]];
        }

        // Match target numbers against the available source numbers in the component.
        for(auto const idx: set) {
            auto const targetNum{targetNums_[idx]};

            // If a matching number is available, consume it and increment the count.
            if(numCnts[targetNum] > 0) {
                --numCnts[targetNum];
                ++numMatchCnt;
            }
        }

        // Reset the frequency counts for the next component to avoid reallocation.
        for(auto const idx: set) {
            numCnts[sourceNums_[idx]] = 0;
        }
    }

    // Calculate the Hamming distance by subtracting matches from the total size.
    auto const hummingDist{numsSz - numMatchCnt};

    return hummingDist;
}
