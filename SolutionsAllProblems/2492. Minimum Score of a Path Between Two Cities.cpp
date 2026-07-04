// problem : https://leetcode.com/problems/minimum-score-of-a-path-between-two-cities/description
// submission : https://leetcode.com/problems/minimum-score-of-a-path-between-two-cities/submissions/2055801204
// solution post : https://leetcode.com/problems/minimum-score-of-a-path-between-two-cities/solutions/8375865/
//    modern-readable-code-optimal-time-comple-dbpp

// Approach : Disjoint Set Union (DSU)
// Runtime : 8 ms, beats 98.01 %

// Complexity
// let 'V' be the number of cities
// 'E' - number of roads
// Time :  O(V + E)
// Space : O(V)

// import std;

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

template <typename T_>
using vec2T = std::vector<std::vector<T_>>;

auto constexpr kMaxScore{std::numeric_limits<int>::max()};
auto constexpr kStartCity{1};
auto constexpr kFrom{0};
auto constexpr kTo{1};
auto constexpr kDist{2};

// Tracks connected components and their absolute lowest edge weight
class Dsu final {
public:
    explicit Dsu(int const size_) :
        mParent{vs::iota(0, size_ + 1) | rs::to<std::vector>()},
        mMinScore(size_ + 1, kMaxScore)
    {}

    // Resolves the root of a set utilizing path compression
    auto Find(int const city_) -> int {
        if (mParent[city_] == city_) {
            return city_;
        }
        
        mParent[city_] = Find(mParent[city_]);
        return mParent[city_];
    }

    // Merges subsets and updates the root's minimum observed weight
    auto Unite(
        int const cityU_, 
        int const cityV_, 
        int const dist_
    ) -> void {
        auto const rootU{Find(cityU_)};
        auto const rootV{Find(cityV_)};

        auto const newMinScore{std::min({mMinScore[rootU], mMinScore[rootV], dist_})};

        if (rootU != rootV) {
            mParent[rootV] = rootU;
        }
        
        mMinScore[rootU] = newMinScore;
    }

    [[nodiscard]]
    auto GetMinScore(int const city_) -> int {
        return mMinScore[Find(city_)];
    }

private:
    std::vector<int> mParent;
    std::vector<int> mMinScore;
};

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace 

class Solution final {
public:
    [[nodiscard]]
    static auto minScore(
        int const cityTot_,
        vec2T<int> const & roads_
    ) -> int;
};

auto Solution::minScore(
    int const cityTot_,
    vec2T<int> const & roads_
) -> int {
    auto dsu{Dsu{cityTot_}};

    // Process all edges to construct components and evaluate local minimums
    rs::for_each(roads_, [&] (auto const & road_) {
        dsu.Unite(road_[kFrom], road_[kTo], road_[kDist]);
    });

    // The target answer belongs to the component housing the starting point
    return dsu.GetMinScore(kStartCity);
}
