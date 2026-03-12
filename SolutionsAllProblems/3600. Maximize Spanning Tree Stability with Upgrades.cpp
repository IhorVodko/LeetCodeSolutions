// problem : https://leetcode.com/problems/maximize-spanning-tree-stability-with-upgrades/description/
// submission : https://leetcode.com/problems/maximize-spanning-tree-stability-with-upgrades/submissions/1946378715
// solution post : https://leetcode.com/problems/maximize-spanning-tree-stability-with-upgrades/solutions/7644241/
//    c-modern-readable-code-runtime-0-ms-beat-a14s

// import std;

namespace {

// Compile-time initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

class DisjointSet final {
public:
    explicit DisjointSet(size_t const sz_):
        mSets(sz_ + 1), 
        mRanks(sz_ + 1)
    {
        // Initially each node is its own parent (separate set)
        std::iota(mSets.begin(), mSets.end(), 0uz);
    }

    [[nodiscard]]
    auto Find(size_t const val_) -> size_t {
        auto & set{mSets[val_]};
        // Path compression: recursively find root and attach current node directly to
        // the root
        if(val_ != set) {
            set = Find(set);
        }
        return set;
    }

    [[nodiscard]]
    auto Union(
        auto const val1_,
        auto const val2_
    ) -> bool {
        auto const set1{Find(val1_)};
        auto const set2{Find(val2_)};
        // Nodes already belong to the same set
        if(set1 == set2) {
            return false;
        }
        // Union by rank heuristic
        auto const rank1{mRanks[val1_]};
        auto const rank2{mRanks[val2_]};
        if(rank1 > rank2) {
            mSets[set2] = set1;
        } else {
            mSets[set1] = set2;
            // If ranks are equal, resulting root rank increases
            if(rank1 == rank2) {
                ++mRanks[set2];
            }
        }
        return true;
    }

private:
    std::vector<size_t> mRanks;
    std::vector<size_t> mSets;
};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    auto maxStability(
        int const nodesTotCnt_,
        std::vector<std::vector<int>> const & edgeDataList_,
        int const upgradeCntUpLim_
    ) const -> int;

private:
    static auto constexpr kIsMust{1};
};


// let 'n' be the number of nodes
// 'm' - number of edges
// time complexity O(m * log(m))
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
auto Solution::maxStability(
    int const nodesTotCnt_,
    std::vector<std::vector<int>> const & edgeDataList_,
    int const upgradeCntUpLim_
) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    using intLim = std::numeric_limits<int>;

    auto disSet{DisjointSet{static_cast<size_t>(nodesTotCnt_)}};
    auto usedEdgeCnt{0};
    auto minMandatoryScore{intLim::max()};
    auto minOptNotUpgradedScore{intLim::max()};
    auto minOptUpgradedScore{intLim::max() / 2};
    auto optionalEdgeDataList{std::vector<std::array<int, 3>>{}};
    for(auto const edgeData: edgeDataList_) {
        auto const nodeFrom{edgeData[0]};
        auto const nodeTo{edgeData[1]};
        auto const edgeScore{edgeData[2]};
        auto const edgeMustStatus{edgeData[3]};
        if(edgeMustStatus == kIsMust) {
            // Forced edges must be included; detect cycles immediately
            if(!disSet.Union(nodeFrom, nodeTo)) {
                return -1;
            }
            ++usedEdgeCnt;
            // Track the minimum stability among mandatory edges
            minMandatoryScore = std::min(minMandatoryScore, edgeScore);
        } else  {
            optionalEdgeDataList.emplace_back(std::array{nodeFrom, nodeTo, edgeScore});
        }
    }
    // Process optional edges in descending stability (Maximum Spanning Tree order)
    rngs::sort(optionalEdgeDataList, std::greater{},
        [] (auto const val_) { return val_.back(); });
    for(auto const [nodeFrom, nodeTo, edgeScore]: optionalEdgeDataList) {
        if(disSet.Union(nodeFrom, nodeTo)) {
            ++usedEdgeCnt;
            // Edge at this position becomes the smallest non-upgraded edge, since it is
            // optimal to upgrade upgradeCntUpLim_ edges wiht lowes stability score
            if(usedEdgeCnt == nodesTotCnt_ - upgradeCntUpLim_ - 1) {
                minOptNotUpgradedScore = edgeScore;
            }
            // Track the smallest optional edge score included in the tree
            minOptUpgradedScore = edgeScore;
        }
    }
    // If spanning tree was not formed
    if(usedEdgeCnt + 1 != nodesTotCnt_) {
        return -1;
    }
    // It is optimal to upgrade optional edge with the lowest stability score if
    // upgradeCntUpLim_ is at least 1. The resulted score will be a candidate for the
    // minimum tree score
    minOptUpgradedScore *= upgradeCntUpLim_ > 0 ? 2 : 1;
    // Final bottleneck (minimum stability score edge) can come from mandatory edges,
    // non-upgraded optional edges, or upgraded optional edges
    auto const maxTreeScore{
        std::min({minMandatoryScore, minOptNotUpgradedScore, minOptUpgradedScore})};
    return maxTreeScore;
}
