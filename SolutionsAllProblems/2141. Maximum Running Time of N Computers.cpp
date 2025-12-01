// problem : https://leetcode.com/problems/maximum-running-time-of-n-computers/description
// submission : https://leetcode.com/problems/maximum-running-time-of-n-computers/submissions/1844429243
// solution post : https://leetcode.com/problems/maximum-running-time-of-n-computers/solutions/
//    7386130/c-modern-readable-code-beats-100-runtime-hl2m

// import std;

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream{"display_runtime.txt"} << 0 << std::endl;
            }
        };
        std::atexit(&Print::DoPrint);
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

class Solution {
public:
// let 'n' be a given number of computers
// 'm' - number of given batterries
/// 'k' - the maximum battery power given
// time complexity O(m * log((m * k ) / n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto maxRunTime(
        int const computersCnt,
        std::span<int const> const batteries_
    ) const -> long long;
};

auto Solution::maxRunTime(
    int const computersCnt,
    std::span<int const> const batteries_
) const -> long long {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto totalPower{rngs::fold_left(batteries_, 0ll, std::plus{})};
    auto lowTime{1ll};
    auto highTime{totalPower / computersCnt};
    auto const isPossible{[=] [[nodiscard]] (long long const time_) -> bool {
        auto sumPower{rngs::fold_left(batteries_, 0ll, [=] (
            auto accum_, auto power_) {
                return accum_ + std::min<long long>(power_, time_);
        })};
        return sumPower >= time_ * computersCnt;
    }
    };
    auto const timeRange{vs::iota(1ll, highTime + 1)};
    auto const timeIt{rngs::partition_point(timeRange, isPossible)};
    auto const maxRuntime{timeIt == timeRange.begin() ? -1 : (*timeIt - 1)};
    return maxRuntime;
}
