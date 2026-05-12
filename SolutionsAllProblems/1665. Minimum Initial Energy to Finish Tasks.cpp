// problem : https://leetcode.com/problems/minimum-initial-energy-to-finish-tasks/description
// submission : https://leetcode.com/problems/minimum-initial-energy-to-finish-tasks/submissions/2001463793
// solution post : https://leetcode.com/problems/minimum-initial-energy-to-finish-tasks/solutions/8204373/
//    c-modern-readable-code-beats-100-runtime-sb2j

// Approach : Greedy
// Runtime : 13 ms, beats 100.00 %

// Complexity
// let 'n' be the number of tasks
// complexity :  O(n * log(n))
// complexity : O(n)

// import std;

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

class Solution final {
public:
    using taskT = std::vector<int>;
    using tasksT = std::vector<taskT>;

    [[nodiscard]]
    auto minimumEffort(tasksT & tsks_) const -> int;
};

auto Solution::minimumEffort(tasksT & tsks_) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto const tsksSz{std::ssize(tsks_)};
    auto diffAndIdxArr{std::vector<std::pair<int, int>>{}};
    diffAndIdxArr.reserve(tsksSz);

    for(auto const j: vs::iota(0, tsksSz)) {
        auto const & tsk{tsks_[j]};
        diffAndIdxArr.emplace_back(tsk[1] - tsk[0], j);
    }

    // Sort ascending by the energy bottleneck-difference to process the most restrictive
    // first.
    rngs::sort(diffAndIdxArr, std::less{}, [] (auto const & diffAndIdx_) {
        return diffAndIdx_.first;
    });

    auto const minNrg{rngs::fold_left(diffAndIdxArr, 0,
        // Simulate backwards energy tracking.
        [&] (auto nrg_, auto const & diffAndIdx_) {
            auto const & tsk{tsks_[diffAndIdx_.second]};
            // Update energy to the maximum of: (previous energy + current task cost) or
            // current task minimum required energy 
            return nrg_ = std::max(nrg_ + tsk[0], tsk[1]);
    })}; 

    return minNrg;
}
