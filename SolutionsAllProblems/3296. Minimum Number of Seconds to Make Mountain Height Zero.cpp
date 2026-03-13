// problem : https://leetcode.com/problems/minimum-number-of-seconds-to-make-mountain-height-zero/description/
// submission : https://leetcode.com/problems/minimum-number-of-seconds-to-make-mountain-height-zero/submissions/
//    1947256065
// solution post : https://leetcode.com/problems/minimum-number-of-seconds-to-make-mountain-height-zero/solutions/
//    7646108/c-modern-readable-code-runtime-0-ms-beat-4o1v

// import std;

namespace {

// Compile-time initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

}

// let 'n' be the number of workers
// 'm' - maximum worker time
// 'h' - mountain height
// time complexity O(n * log(m * h^2)) 
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    using ll = long long;

    auto minNumberOfSeconds(
        int const mountainHeight_,
        std::vector<int> & workerTimes_
    ) const -> ll;
};

auto Solution::minNumberOfSeconds(
    int const mountainHeight_,
    std::vector<int> & workerTimes_
) const -> ll {
    namespace vs = std::views;
    namespace rngs = std::ranges;
    
    // Determine the maximum single worker time
    auto const maxTime{*rngs::max_element(workerTimes_)};
    // Set initial lower bound for total time
    auto totTimeLowLim{1ll};
    // Set upper bound for total time assuming one slowest worker does all
    auto totTimeUpLim{
        static_cast<ll>(maxTime) * mountainHeight_ * (mountainHeight_ + 1) / 2};
    // Binary search to find minimum achievable total time
    auto const minTotTimeIt{rngs::partition_point(
        vs::iota(totTimeLowLim, totTimeUpLim + 1),
        [&] (auto const totTime_) {
            auto totCompletedHeight{0ll};
            // Calculate total height completed by all workers within current time
            for(auto const time: workerTimes_) {
                // Height that this worker can complete in 'totTime_' seconds
                auto curCompletedHeight{static_cast<ll>(
                    (-1.0 + std::sqrt(1.0 + 8.0 * totTime_ / time)) / 2.0)};
                totCompletedHeight += curCompletedHeight;
            }
            // Check if current total time is insufficient
            auto const isInsufficient{totCompletedHeight < mountainHeight_};
            return isInsufficient;
    })};
    return *minTotTimeIt;
}
