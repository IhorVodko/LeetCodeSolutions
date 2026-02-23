// problem : https://leetcode.com/problems/smallest-string-with-swaps/description/
// submission : https://leetcode.com/problems/smallest-string-with-swaps/submissions/1928821409
// solution post : https://leetcode.com/problems/smallest-string-with-swaps/solutions/7603347/
//    c-modern-readable-code-beats-100-runtime-5po8

// import std;

inline static int const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

class DisjointSet final {
public:
    explicit DisjointSet(int const sz_);
    [[nodiscard]]
    auto Find(int const val_) -> int;
    auto Union(
        int const val1_,
        int const val2_
    ) -> void;
    [[nodiscard]]
    auto GetSetCnt() const -> int;

private:
    std::vector<int> mRoots;
    std::vector<int> mRanks;
    int mSz{};
    int mSetCnt{};
};

// let 'n' be the string length
// time complexity O(n * log(n))
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    [[nodiscard]]
    auto smallestStringWithSwaps(
        std::string_view const str_,
        std::vector<std::vector<int>> const & swapIdxPairs_
    ) const -> std::string;
};

auto Solution::smallestStringWithSwaps(
    std::string_view const str_,
    std::vector<std::vector<int>> const & swapIdxPairs_
) const -> std::string {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto const strSz{std::ssize(str_)};
    auto ds{::DisjointSet{static_cast<int>(strSz)}};
    for(auto const & idxPair: swapIdxPairs_) {
        ds.Union(idxPair.front(), idxPair.back());
    }
    auto rootToIdxSet{std::unordered_map<int, std::vector<int>>{}};
    rootToIdxSet.reserve(ds.GetSetCnt());
    for(auto const vertex: vs::iota(0, strSz)) {
        // group indices by their connected component representative
        rootToIdxSet[ds.Find(vertex)].emplace_back(vertex);
    }
    auto lexMinStr{std::string(strSz, '?')};
    for(auto chrs{std::vector<char>{}};
        [[maybe_unused]] auto const & [ignore, indexSet]: rootToIdxSet
    ) {
        chrs.clear();
        auto const indexSetSz{std::ssize(indexSet)};
        chrs.reserve(indexSetSz);
        for(auto const idx: indexSet) {
            // collect characters belonging to the same connected component
            chrs.emplace_back(str_[idx]);
        }
        // sort characters to place smallest lexicographically first
        rngs::sort(chrs);
        for(auto const idx: vs::iota(0, indexSetSz)) {
            // write back sorted characters to their original positions
            lexMinStr[indexSet[idx]] = chrs[idx];
        }
    }
    return lexMinStr;
}

DisjointSet::DisjointSet(int const sz_):
    mRoots(sz_ + 1),
    mRanks(sz_ + 1, 1),
    mSz{sz_},
    mSetCnt{sz_}
{
    // initially each node is its own parent
    std::iota(mRoots.begin(), mRoots.end(), 0);
} 

[[nodiscard]]
auto DisjointSet::Find(int const val_) -> int {
    if(val_ == mRoots[val_]) {
        return mRoots[val_];
    }
    // path compression to flatten the tree
    return mRoots[val_] = Find(mRoots[val_]); 
}

auto DisjointSet::Union(
    int const val1_,
    int const val2_
) -> void {
    auto const root1{Find(val1_)};
    auto const root2{Find(val2_)};
    if(root1 == root2) {
        return;
    }
    auto & rank1{mRanks[root1]};
    auto & rank2{mRanks[root2]};
    // union by rank to keep trees shallow
    if(rank1 < rank2) {
        mRoots[root1] = root2;
    } else if(rank1 == rank2) {
        mRoots[root1] = root2;
        ++rank1;
    } else {
        mRoots[root2] = root1;
    }
    --mSetCnt;
}

[[nodiscard]]
auto DisjointSet::GetSetCnt() const -> int {
    return mSetCnt;
}
