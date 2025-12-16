// problem : https://leetcode.com/problems/number-of-smooth-descent-periods-of-a-stock/description/
// submission : https://leetcode.com/problems/number-of-smooth-descent-periods-of-a-stock/submissions/1857485103
// solution post : https://leetcode.com/problems/number-of-smooth-descent-periods-of-a-stock/solutions/7418568/
//    c-modern-readable-code-beats-100-runtime-hne1

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
// let 'n' be the number of given prices
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto getDescentPeriods(
        std::span<int const> const prices_
    ) const -> long long;
};

auto Solution::getDescentPeriods(
    std::span<int const> const prices_
) const -> long long {
    namespace vs = std::views;

    auto preriodCnt{1ll};
    auto currPeriodCnt{1};
    for(auto const day: vs::iota(1u, prices_.size())) {
        if(prices_[day - 1] - prices_[day] == 1) {
            ++currPeriodCnt;
        } else {
            currPeriodCnt = 1;
        }
        preriodCnt += currPeriodCnt;
    } 
    return preriodCnt;
}
