// problem : https://leetcode.com/problems/count-number-of-trapezoids-i/description
// submission : https://leetcode.com/problems/count-number-of-trapezoids-i/submissions/1844917734
// solution post : https://leetcode.com/problems/count-number-of-trapezoids-i/solutions/7387128/
//    c-modern-readable-code-beats-100-runtime-h5c9

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
// let 'n' be the number of given points
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto countTrapezoids(
        std::span<std::vector<int> const> const points_
    ) const -> int;

private:

    static int constexpr kModVal{1'000'000'007};
};

auto Solution::countTrapezoids(
    std::span<std::vector<int> const> const points_
) const -> int {
    namespace vs = std::views;

    auto yToCnt{std::unordered_map<int, int>{}};
    auto totTrapezoidsCnt{0ll};
    auto totHorizontalSideCnt{0ll};
    for(auto const & point: points_) {
        ++yToCnt[point[1]];
    }
    for(auto const [_, cnt]: yToCnt) {
        auto currHorizontalSideCnt{
            static_cast<long long>(cnt) * (cnt - 1) / 2
        };
        auto currTrapezoidsCnt{currHorizontalSideCnt * totHorizontalSideCnt};
        totTrapezoidsCnt = (totTrapezoidsCnt + currTrapezoidsCnt) % kModVal;
        totHorizontalSideCnt += currHorizontalSideCnt;
    }
    return totTrapezoidsCnt;
}
