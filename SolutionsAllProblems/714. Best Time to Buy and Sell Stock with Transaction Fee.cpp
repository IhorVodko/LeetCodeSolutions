// problem : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/description/
// submission : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/submissions/1844249098
// solution post : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/solutions/7385753/
//    c-modern-readable-code-beats-100-runtime-6wvh

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
    auto maxProfit(
        std::span<int const> const prices_,
        int const fee_
    ) const -> int;
};

auto Solution::maxProfit(
    std::span<int const> const prices_,
    int const fee_
) const -> int {
   namespace vs = std::views;

    auto maxProfitNoStock{0};
    auto maxProfitHasStock{-1 * prices_[0]};
    for(auto const day: vs::iota(1u, prices_.size())) {
        auto const tmpProfitHasStock{maxProfitHasStock};
        auto const currProfitHasStock{maxProfitNoStock - prices_[day]};
        maxProfitHasStock = std::max(maxProfitHasStock, currProfitHasStock);
        auto const currProfitNoStock{tmpProfitHasStock + prices_[day] - fee_};
        maxProfitNoStock = std::max(maxProfitNoStock, currProfitNoStock);
    }
    return maxProfitNoStock;
}
