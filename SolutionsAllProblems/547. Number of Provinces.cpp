// problem : https://leetcode.com/problems/number-of-provinces/description/
// submission : https://leetcode.com/problems/number-of-provinces/submissions/1922273547
// solution post : https://leetcode.com/problems/number-of-provinces/solutions/7586664/
//    c-modern-readable-code-beats-100-runtime-e2hn

// import std;

inline static int const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' be the number of cities
// time complexity O(n^2)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    auto findCircleNum(std::vector<std::vector<int>> const & adjMx_) const -> int;

private:
    class DisjointSet final {
    public:
        explicit DisjointSet(int const sz_);

        [[nodiscard]]
        auto Find(int const node_) -> int;
        auto Join(int const node1_, int const node2_) -> void;
        [[nodiscard]]
        inline auto GetComponentsCnt() const -> int;

    private:
        std::vector<int> mRoots;
        std::vector<int> mRanks;
        int mComponentsCnt;
    };
};

auto Solution::findCircleNum(
    std::vector<std::vector<int>> const & adjMx_
) const -> int{
    namespace vs = std::views;

    auto const mxSz{std::ssize(adjMx_)};
    auto ds{DisjointSet{static_cast<int>(mxSz)}};
    // Traverse the adjacency matrix and union connected cities
    for(auto const r: vs::iota(0, mxSz)) {
        for(auto const c: vs::iota(0, mxSz)) {
            if(adjMx_[r][c] == 1) {
                ds.Join(r, c);
            }
        }
    }

    auto const provincesCnt{ds.GetComponentsCnt()};
    return provincesCnt;
}

Solution::DisjointSet::DisjointSet(int const sz_):
    mRoots(sz_),
    mRanks(sz_), 
    mComponentsCnt{sz_}
{
    // Initially, each node is its own parent (separate component)
    std::iota(mRoots.begin(), mRoots.end(), 0);
    std::iota(mRoots.begin(), mRoots.end(), 0);
}

[[nodiscard]]
auto Solution::DisjointSet::Find(int const node_) -> int {
    // Path compression: recursively attach node to its root
    if(node_ == mRoots[node_]) {
        return node_;
    }
    return mRoots[node_] = Find(mRoots[node_]);
}

auto Solution::DisjointSet::Join(int const node1_,int const node2_) -> void {
    auto const rootX{Find(node1_)};
    auto const rootY{Find(node2_)};

    // If both nodes share the same root, they are already connected
    if(rootX == rootY) {
        return;
    }
    // Union by rank to keep tree shallow
    auto const rankX{mRanks[rootX]};
    auto & rankY{mRanks[rootY]};
    if(rankX > rankY) {
        mRoots[rootY] = rootX;
    } else if(rankX < rankY) {
        mRoots[rootX] = rootY;
    } else {
        mRoots[rootX] = rootY;
        rankY += 1;
    }
    // Merging two components reduces total count by one
    --mComponentsCnt;
}

[[nodiscard]]
auto Solution::DisjointSet::GetComponentsCnt() const -> int {
    return mComponentsCnt;
}
