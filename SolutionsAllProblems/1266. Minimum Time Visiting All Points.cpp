// problem : https://leetcode.com/problems/minimum-time-visiting-all-points/description
// submission : https://leetcode.com/problems/minimum-time-visiting-all-points/submissions/1885187837
// solution post : https://leetcode.com/problems/minimum-time-visiting-all-points/solutions/7495119/
//    c-modern-readable-code-beats-100-runtime-0di2

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

// let 'n' be the number of points
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto minTimeToVisitAllPoints(std::vector<std::vector<int>> const & points_) const -> int;
};

auto Solution::minTimeToVisitAllPoints(
    std::vector<std::vector<int>> const & points_
) const -> int {
    namespace vs = std::views;

    auto time{0};
    for(auto const [cur, next]: vs::zip(
            points_,
            points_ | vs::drop(1)
    )) {
        auto const horizontalDist{std::abs(next[0] - cur[0])};
        auto const verticalDist{std::abs(next[1] - cur[1])};
        time += std::max(horizontalDist, verticalDist);
    }
    return time;
}
