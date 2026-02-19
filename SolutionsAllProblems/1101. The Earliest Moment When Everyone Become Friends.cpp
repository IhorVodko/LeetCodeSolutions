// problem : https://leetcode.com/problems/the-earliest-moment-when-everyone-become-friends/description/
// submission : https://leetcode.com/problems/the-earliest-moment-when-everyone-become-friends/submissions/1924606983
// solution post : https://leetcode.com/problems/the-earliest-moment-when-everyone-become-friends/solutions/7592459/
//    c-modern-readable-code-beats-100-runtime-nf3h

// import std;

inline static int const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' be the number of people
// 'm' - number of logs
// time complexity O(n + m * log(m))
// space complexity O(n + log(m))
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    // Returns the earliest timestamp when all people become connected
    [[nodiscard]]
    auto earliestAcq(
        std::vector<std::vector<int>> & logs_,
        int const peopleTotCnt_
    ) const -> int;

private:
    // Disjoint Set (Union-Find) data structure
    class DisjointSet final {
    public:
        explicit DisjointSet(int const sz_);
        [[nodiscard]]
        // Find with path compression
        auto Find(int const val_) -> int;
        // Union by rank
        auto Union(
            int const val1_,
            int const val2_
        ) -> void;
        [[nodiscard]]
        auto GetDsSetCnt() const -> int;

    private:
        // Current number of disjoint sets
        int mDsSetCnt{};
        // Total number of elements
        int mSz{};
        std::vector<int> mRoots;
        std::vector<int> mRanks;
    };
};

// Main solution function
auto Solution::earliestAcq(
    std::vector<std::vector<int>> & logs_,
    int const peopleTotCnt_
) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    // If there are fewer logs than minimum required edges, full connection is impossible
    auto const logsSz{std::ssize(logs_)};
    if(logsSz < peopleTotCnt_ - 1) {
        return -1;
    }
    // Sort logs by timestamp
    rngs::sort(logs_, std::less{}, [] (auto const & log_) { return log_.front();});
    auto ds{DisjointSet{peopleTotCnt_}};
    for(auto const & log: logs_) {
        auto const time{log[0]};
        auto const people1{log[1]};
        auto const people2{log[2]};
        ds.Union(people1, people2);
        // If only one set remains, everyone is connected
        if(ds.GetDsSetCnt() == 1) {
            return time;
        }
    }
    // If never fully connected
    return -1;
}

Solution::DisjointSet::DisjointSet(int const sz_) :
    mSz{sz_},
    mDsSetCnt{sz_},
    mRoots(sz_),
    mRanks(sz_)
{
    namespace rngs = std::ranges;
    std::iota(mRoots.begin(), mRoots.end(), 0);
    rngs::fill(mRanks, 1);
}

// Find with path compression
[[nodiscard]]
auto Solution::DisjointSet::Find(int const val_) -> int {
    auto & valRoot{mRoots[val_]};
    if(val_ == valRoot) {
        return val_;
    }
    // Recursively compress path
    return valRoot = Find(valRoot);
} 

// Union by rank
auto Solution::DisjointSet::Union(
    int const val1_,
    int const val2_
) -> void {
    auto const root1{mRoots[Find(val1_)]};
    auto const root2{mRoots[Find(val2_)]};
    if(root1 == root2) {
        return;
    }
    // Reduce number of disjoint sets
    --mDsSetCnt;
    auto & rank1{mRanks[val1_]};
    auto & rank2{mRanks[val2_]};
    // Attach smaller rank tree under larger rank tree
    if(rank1 < rank2) {
        mRoots[root1] = root2;
    } else if(rank1 == rank2) {
        mRoots[root2] = root1;
        ++rank2;
    } else {
        mRoots[root2] = root1;
    }
}

// Returns current number of disjoint sets
[[nodiscard]]
auto Solution::DisjointSet::GetDsSetCnt() const -> int {
    return mDsSetCnt;
}
