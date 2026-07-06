// problem : https://leetcode.com/problems/remove-covered-intervals/description
// submission : https://leetcode.com/problems/remove-covered-intervals/submissions/2058412524
// solution post : https://leetcode.com/problems/remove-covered-intervals/solutions/8380470/modern-readable-code-optimal-time-comple-wliu

// Approach : Sorting and Greedy Line Sweep
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the number of intervals
// Time :  O(n * log(n))
// Space : O(sort(n)), auxiliary space

// import std;

namespace {

namespace rs = std::ranges;

// Semantic indices for interval start and end
auto constexpr kL{0};
auto constexpr kR{1};

// Accumulator for folding over the intervals
struct State {
    int cnt{};
    int maxR{};
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
    static auto removeCoveredIntervals(std::vector<std::vector<int>> & intervals_) -> int;
};

auto Solution::removeCoveredIntervals(std::vector<std::vector<int>> & intervals_) -> int {
    if(intervals_.size() == 1) {
        return 1;
    }

    // Sort by start ascending, then by end descending to handle overlapping intervals
    rs::sort(intervals_, {}, [] (auto const & interval_) {
        return std::tuple{interval_[kL], -1 * interval_[kR]};
    });

    // Count non-covered intervals by tracking the furthest right boundary seen
    return rs::fold_left(
        intervals_,
        State{0, 0},
        [] (auto state_, auto const & interval_) {
            auto [cnt, maxR]{state_};
            auto const currR{interval_[kR]};

            return currR <= maxR ? state_ : State{cnt + 1, currR};
        }
    ).cnt;
}
