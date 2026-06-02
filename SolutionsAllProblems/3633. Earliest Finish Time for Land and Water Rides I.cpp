// problem : https://leetcode.com/problems/earliest-finish-time-for-land-and-water-rides-i/description
// submission : https://leetcode.com/problems/earliest-finish-time-for-land-and-water-rides-i/submissions/2020169345
// solution post : https://leetcode.com/problems/earliest-finish-time-for-land-and-water-rides-i/solutions/8308809/
//    c-modern-readable-code-beats-100-runtime-oza6

// Approach : Greedy Independent Optimization
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the number of land rides
// 'm' - nubmer of water rides
// complexity :  O(n + m)
// complexity : O(1)

class Solution final {
public:
    [[nodiscard]]
    static auto earliestFinishTime(
        std::vector<int> const & landStarts_,
        std::vector<int> const & landDurations_,
        std::vector<int> const & waterStarts_,
        std::vector<int> const & waterDurations_
    ) -> int;

private:
    [[nodiscard]]
    static auto Solve(
        std::vector<int> const & starts1_,
        std::vector<int> const & durations1_,
        std::vector<int> const & starts2_,
        std::vector<int> const & durations2_
    ) -> int;
};

auto Solution::earliestFinishTime(
    std::vector<int> const & landStarts_,
    std::vector<int> const & landDurations_,
    std::vector<int> const & waterStarts_,
    std::vector<int> const & waterDurations_
) -> int {
    // Determine the earliest completion for the Land-then-Water sequence.
    auto const minLandThenWaterEnd{
        Solve(landStarts_, landDurations_, waterStarts_, waterDurations_)
    };
    // Determine the earliest completion for the Water-then-Land sequence.
    auto const minWaterThenLandEnd{
        Solve(waterStarts_, waterDurations_, landStarts_, landDurations_)
    };
    
    return std::min(minLandThenWaterEnd, minWaterThenLandEnd);
}

auto Solution::Solve(
    std::vector<int> const & starts1_,
    std::vector<int> const & durations1_,
    std::vector<int> const & starts2_,
    std::vector<int> const & durations2_
) -> int {
    namespace vs = std::views;
    namespace rs = std::ranges;
    using intLimT = std::numeric_limits<int>;

    // Find the absolute earliest exit time from any ride in the first category.
    auto const minEnd1{rs::min(vs::zip_transform(std::plus{}, starts1_, durations1_))};

    // Evaluate the second category assuming arrival at the optimal first exit time.
    auto minEnd2{rs::min(vs::zip_transform(
        [&] (int const start_, int const dur_) -> int {
            // Factor in potential waiting time if arriving before the ride opens.
            return std::max(start_, minEnd1) + dur_;
        },
        starts2_, durations2_
    ))};

    return minEnd2;
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
