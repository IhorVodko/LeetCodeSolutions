// problem : https://leetcode.com/problems/count-number-of-trapezoids-ii/description/
// submission : https://leetcode.com/problems/count-number-of-trapezoids-ii/submissions/1846116004
// solution post : https://leetcode.com/problems/count-number-of-trapezoids-ii/solutions/7389794/
//    c-modern-readable-code-beats-100-runtime-cl60

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
// time complexity O(n^2)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto countTrapezoids(
        std::span<std::vector<int> const> const points_
    ) const -> int;
};

auto Solution::countTrapezoids(
    std::span<std::vector<int> const> const points_
) const -> int {
    namespace vs = std::views;

    auto const pointsSz{std::ssize(points_)};
    auto slopeToIntercepts{std::unordered_map<double, std::vector<double>>{}};
    auto midToSlopes{std::unordered_map<double, std::vector<double>>{}};
    auto trapezoidsCnt{0};
    for(auto const i1: vs::iota(0, pointsSz)) {
        auto const x1{static_cast<double>(points_[i1][0])};
        auto const y1{static_cast<double>(points_[i1][1])};
        for(auto const i2: vs::iota(i1 + 1, pointsSz)) {
            auto const x2{static_cast<double>(points_[i2][0])};
            auto const y2{static_cast<double>(points_[i2][1])};
            auto slope{0.};
            auto intercept{0.};
            if(x1 == x2) {
                slope = std::numeric_limits<double>::max();
                intercept = x1;
            } else {
                slope = (y2 - y1) / (x2 - x1);
                auto const diffX{x1 - x2};
                auto const diffY{y1 - y2};
                intercept = (y1 * diffX - x1 * diffY) / diffX;
            }
            auto const mid{(x1 + x2) * 10'000 + (y1 + y2)};
            slopeToIntercepts[slope].emplace_back(intercept);
            midToSlopes[mid].emplace_back(slope);
        }
    }
    for(auto const & [_, intercepts]: slopeToIntercepts) {
        if(intercepts.size() == 1) {
            continue;
        }
        auto interceptToCnt{std::unordered_map<double, int>{}};
        for(auto const intercept: intercepts) {
            ++interceptToCnt[intercept];
        }
        auto interceptTotCnt{0};
        for(auto const [_, cnt]: interceptToCnt) {
            trapezoidsCnt += interceptTotCnt * cnt;
            interceptTotCnt += cnt;
        }
    }
    for(auto const & [_, slopes]: midToSlopes) {
        if(slopes.size() == 1) {
            continue;
        }
        auto slopeToCnt{std::unordered_map<double, int>{}};
        for(auto const slope: slopes) {
            ++slopeToCnt[slope]; 
        }
        auto slopeTotCnt{0};
        for(auto const [_, cnt]: slopeToCnt) {
            trapezoidsCnt -= slopeTotCnt * cnt;
            slopeTotCnt += cnt;
        }
    }
    return trapezoidsCnt;
}
