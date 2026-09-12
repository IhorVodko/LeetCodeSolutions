// problem : https://leetcode.com/problems/maximum-score-of-non-overlapping-intervals/description
// submission : https://leetcode.com/problems/maximum-score-of-non-overlapping-intervals/submissions/2139520918
// solution post : https://leetcode.com/problems/maximum-score-of-non-overlapping-intervals/solutions/8517485/
//    simplanation-simple-explanation-by-cyber-44xc

// Approach : https://leetcode.com/problems/maximum-score-of-non-overlapping-intervals/submissions/2139520918
// Runtime : 258 ms, beats 100.00 %

// Complexity analysis
// let 'N' be the number of intervals
// Time :  O(N * log(N))
// Space : O(N)

// import std;

// #include <algorithm>
// #include <array>
// #include <functional>
// #include <ios>
// #include <iostream>
// #include <ranges>
// #include <span>
// #include <vector>

// #include <cstddef>
// #include <cstdint>

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

using std::size_t;

constexpr auto kMaxSelectedIntervalsCnt{4uz};
constexpr auto kIntervalStartIdx{0uz};
constexpr auto kIntervalEndIdx{1uz};
constexpr auto kIntervalWeightIdx{2uz};

// Optimize standard I/O operations for performance before main() execution
[[maybe_unused]]
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

struct IntervalData final{
    int start{};
    int end{};
    size_t weight{};
    int idx{}; 
};

struct SelectedIntervalIdxs final{
    // Maintain a bounded list of selected interval indices
    auto AddIdx(int const idx_) -> void  {
        idxs[cnt_++] = idx_;
    }

    // Sort indices internally for stable lexicographical comparisons
    auto SortIdxs() -> void {
        rs::sort(std::span{idxs.data(), static_cast<size_t>(cnt_)});
    }

    [[nodiscard]]
    auto GetSelectedIntervalIdxs() const -> std::span<int const> {
        return std::span<int const>{idxs.data(), static_cast<size_t>(cnt_)};
    }

    [[nodiscard]]
    auto operator<(SelectedIntervalIdxs const & rhs_) const -> bool {
        return rs::lexicographical_compare(
            GetSelectedIntervalIdxs(), rhs_.GetSelectedIntervalIdxs()
        );
    }

    std::array<int, kMaxSelectedIntervalsCnt> idxs;
    int cnt_{};
};

struct DpState final{
    // Favor higher weight, breaking ties with lexicographically smaller indices
    [[nodiscard]]
    auto operator<(DpState const & rhs_) const -> bool {
        if(totWeight != rhs_.totWeight) {
            return totWeight < rhs_.totWeight;
        }
        return rhs_.selectedIdxs < selectedIdxs;
    }

    size_t totWeight{};
    SelectedIntervalIdxs selectedIdxs;
};

using state = std::array<DpState, kMaxSelectedIntervalsCnt + 1>;

} // namespace

class Solution final {
public:
    [[nodiscard]]
    static auto maximumWeight(
        std::vector<std::vector<int>> & intervals_
    ) -> std::vector<int>;
};

auto Solution::maximumWeight(
    std::vector<std::vector<int>> & intervals_
) -> std::vector<int> {
    auto const totIntervals{intervals_.size()};

    // 1. Augment intervals with their original indices to track them after sorting
    auto intervals{
        intervals_ |
        vs::enumerate |
        vs::transform([] (auto const & idxAndInterval_) {
            auto const & [idx, interval]{idxAndInterval_};
            return IntervalData{
                interval[kIntervalStartIdx],
                interval[kIntervalEndIdx],
                static_cast<size_t>(interval[kIntervalWeightIdx]),
                static_cast<int>(idx)
            };
        }) |
        rs::to<std::vector>()
    };

    // 2. Sort intervals ascending by end time to support sequential non-overlapping DP
    rs::sort(intervals, [] (auto const & lhs_, auto const & rhs_) {
        if(lhs_.end != rhs_.end) {
            return lhs_.end < rhs_.end; 
        }
        return lhs_.start < rhs_.start;
    });

    // 3. Init DP table where dp[i][k] tracks optimal state up to interval i for k choices
    auto dpStateTable{std::vector<state>(totIntervals, state{})};

    // 4. Traverse all sorted intervals to compute overlapping boundaries and DP transitions
    for(auto const intervalsBeg{intervals.cbegin()};
        auto const & [currIntervalIdx, currInterval]: intervals | vs::enumerate
    ) {
        auto const searchEnd{intervalsBeg + currIntervalIdx};
        // Locate the latest preceding interval that completes before current starts
        auto const lastValidIntervalIt{rs::lower_bound(
            intervalsBeg,
            searchEnd,
            currInterval.start,
            std::less{},
            &IntervalData::end
        )};

        auto const hasPrevInterval{lastValidIntervalIt != intervalsBeg};
        auto const pevIntervalIdx{hasPrevInterval ?
            lastValidIntervalIt - intervalsBeg - 1 : 0uz
        };

        // 5. Compute DP transitions for choices from 1 up to the required interval count
        for(auto const selectedIntervalsCnt:
            vs::iota(1uz, kMaxSelectedIntervalsCnt + 1)
        ) {
            auto const skipState{currIntervalIdx > 0 ?
                dpStateTable[currIntervalIdx - 1][selectedIntervalsCnt] : DpState{}
            };
            auto takeState{hasPrevInterval ?
                dpStateTable[pevIntervalIdx][selectedIntervalsCnt - 1] : DpState{}
            };
            auto & [totWeight, selectedIdxs]{takeState};

            // Form new state by incorporating the current interval's weight and index
            totWeight += currInterval.weight;
            selectedIdxs.AddIdx(currInterval.idx);
            selectedIdxs.SortIdxs();

            // Select the maximum state between skipping or taking the current interval
            dpStateTable[currIntervalIdx][selectedIntervalsCnt] =
                std::max(skipState, takeState)
            ;
        }
    }

    auto const & bestState{dpStateTable.back()[kMaxSelectedIntervalsCnt]};
    // 6. Extract globally optimal indices sequence for exact interval target count
    auto const bestSelectedIntervalIdxs{
        bestState.selectedIdxs.GetSelectedIntervalIdxs()
    };

    return std::vector<int>{
        bestSelectedIntervalIdxs.begin(), bestSelectedIntervalIdxs.end()
    };
}
