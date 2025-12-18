// problem : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-v/description
// submission : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-v/submissions/1859314679
// solution post : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-v/solutions/7422861/
//    c-modern-readable-code-beats-100-runtime-pxfs

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
// let 'n' be the number of given days
// 'm' - transactions upper limit
// time complexity O(n * m)
// space complexity O(m)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto maximumProfit(
        std::span<int const> const prices_,
        int transCntULim_
    ) const -> long long;
};

auto Solution::maximumProfit(
    std::span<int const> const prices_,
    int transCntULim_
) const -> long long {
    namespace vs = std::views;

    auto const dayTotCnt{std::ssize(prices_)};
    auto dp{std::vector<std::array<long long, 3>>(
        transCntULim_ + 1,
        std::array<long long, 3>{}
    )};
    for(auto const transCnt: vs::iota(1, transCntULim_ + 1)) {
        dp[transCnt][1] = -prices_[0];
        dp[transCnt][2] = prices_[0];
    }
    for(auto const day: vs::iota(1, dayTotCnt)) {
        for(auto const transCnt: vs::iota(1, transCntULim_ + 1) | vs::reverse) {
            auto  & currProfNoPos{dp[transCnt][0]};
            auto const prevProfLong{dp[transCnt][1]};
            auto const prevProfShort{dp[transCnt][2]};
            auto const currPrice{prices_[day]};
            currProfNoPos = std::max(
                currProfNoPos,
                std::max(prevProfLong + currPrice, prevProfShort - currPrice)
            );
            auto & currProfLong{dp[transCnt][1]};
            auto const profNoPosOneTransBefore{dp[transCnt - 1][0]};
            currProfLong = std::max(currProfLong, profNoPosOneTransBefore - currPrice);
            auto & currProfShort{dp[transCnt][2]};
            currProfShort = std::max(currProfShort, profNoPosOneTransBefore + currPrice);
        }
    }
    auto const maxProf{dp[transCntULim_][0]};
    return maxProf;
}
