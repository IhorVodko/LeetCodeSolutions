// problem : https://leetcode.com/problems/block-placement-queries/description
// submission : https://leetcode.com/problems/block-placement-queries/submissions/2017217768
// solution post : https://leetcode.com/problems/block-placement-queries/solutions/8302600/c-modern-readable-code-beats-99-runtime-qfn5u

// Approach : Offline Query Processing with Time Reversal and Fenwick Tree
// Runtime : 250 ms, beats 99.00 %

// Complexity
// let 'n' be the number of queries
// 'M' - maximum 'x' coordinate among queries
// complexity :  O(n * log(n) + M * log(n))
// complexity : O(n + M)

// import std;

class FenwickTree final {
public:
    explicit FenwickTree(int const sz_) :
        mSz(sz_),
        mTree(sz_ + 1)
    {}
    
    // Point update to maximum value
    auto Update(
        int j_,
        int val_
    ) -> void {
        for (; j_ <= mSz; j_ += j_ & -j_) {
            mTree[j_] = std::max(mTree[j_], val_);
        }
    }
    
    // Range query for maximum value up to index j
    [[nodiscard]]
    auto Query(int j_) const -> int {
        int mx = 0;
        for (; j_ > 0; j_ -= j_ & -j_) {
            mx = std::max(mx, mTree[j_]);
        }
        return mx;
    }

private:
    int mSz;
    std::vector<int> mTree;
};

class Solution final {
public:
    using queryT = std::vector<int>;
    using queriesT = std::vector<queryT>;

    [[nodiscard]]
    static auto getResults(queriesT & queries_) -> std::vector<bool>;
};

auto Solution::getResults(queriesT & queries_) -> std::vector<bool> {
    namespace vs = std::views;
    namespace rs = std::ranges;

    // Accumulate the final state of all obstacles
    auto obstacles{
        queries_ |
        vs::filter([](auto const & q_) { return q_[0] == 1; }) |
        vs::transform([](auto const & q_) { return q_[1]; }) |
        rs::to<std::set<int>>()
    };
    // Origin is our left-most guaranteed boundary
    obstacles.emplace(0);

    // Find the maximum coordinate bound to dimension the Fenwick Tree efficiently
    auto const maxX{
        rs::max(queries_ | vs::transform([](auto const & q_) { return q_[1]; }))
    };

    auto tree{FenwickTree{maxX + 1}};
    // Initialize the tree based on the completely fragmented state
    for(auto const [x1, x2]: vs::zip(obstacles, obstacles | vs::drop(1))) {
        tree.Update(x2, x2 - x1);
    }
        
    auto ans{std::vector<bool>{}};
    // Pre-allocate to prevent reallocation overhead
    ans.reserve(rs::count_if(queries_, [](auto const & q_) { return q_[0] == 2; }));
    
    // Process queries backwards
    for (const auto & q : queries_ | vs::reverse) {
        auto const type{q[0]};
        auto const x{q[1]};
        
        if (type == 1) {
            // Time-reversed query 1 implies 'removing' an obstacle and merging intervals
            auto const currObstacle{obstacles.find(x)};
            auto prevObstacle{std::prev(currObstacle)};
            auto nextObstacle{std::next(currObstacle)};
            
            // If there's an interval boundary to the right, extend its span backwards
            if (nextObstacle != obstacles.cend()) {
                tree.Update(*nextObstacle, *nextObstacle - *prevObstacle);
            }
            obstacles.erase(currObstacle);
        } else {
            auto const sz{q[2]};
            // Find the closest obstacle strictly <= x
            auto const currObstacle{obstacles.upper_bound(x)};
            auto const prevObstacle{*std::prev(currObstacle)};
            
            // Maximum of existing intervals up to 'prevObstacle' OR the open space from
            // 'prevObstacle' to 'x'
            ans.emplace_back(
                (tree.Query(prevObstacle) >= sz) || (x - prevObstacle >= sz));
        }
    }
    
    // Because we appended results during a reverse traversal, reverse it back.
    rs::reverse(ans);

    return ans;
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
