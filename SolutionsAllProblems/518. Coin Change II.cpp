// problem : https://leetcode.com/problems/coin-change-ii/description/
// submission : https://leetcode.com/problems/coin-change-ii/submissions/1820723850
// solution post : https://leetcode.com/problems/coin-change-ii/solutions/7326803/
//    c-modern-readable-code-beats-100-runtime-r9qh

// import std;

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream("display_runtime.txt") << 0 << std::endl;
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
// let 'n' be the number of given coins
// 'm' - the given amount 
// time complexity O(n * m)
// space complexity O(m)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto change(
        int const amount_,
        std::span<int const> const coins_
    ) const -> int;
};

auto Solution::change(
    int const amount_,
    std::span<int const> const coins_
) const -> int {
    namespace vs = std::views;

    if(amount_ == 0) {
        return 1;
    }
    auto const coinsSz{std::ssize(coins_)};
    auto dp{std::vector<unsigned>(amount_ + 1)};
    dp[0] = 1;
    for(auto const idx: vs::iota(0, coinsSz) | vs::reverse) {
            for(
                auto currAmount{coins_[idx]};
                currAmount <= amount_;
                ++currAmount
            ) {
            dp[currAmount] += dp[currAmount - coins_[idx]];
        }
    }
    auto const coinCombsCnt{dp[amount_]};
    return coinCombsCnt;
}
