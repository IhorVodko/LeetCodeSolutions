// problem : https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/
// submission : https://leetcode.com/problems/best-time-to-buy-and-sell-stock/submissions/1826926345
// solution post : https://leetcode.com/problems/best-time-to-buy-and-sell-stock/solutions/7341700/
//    c-modern-readable-code-beats-100-runtime-pdm2

// import std;

class Solution {
public:
// let 'n' be the number of the given prices
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto maxProfit(
        std::span<int const> const prices_
    ) const -> int;
};

auto Solution::maxProfit(
    std::span<int const> const prices_
) const -> int {
    namespace vs = std::views;

    if(prices_.empty()) {
        return 0;
    }
    auto minBuyPrice{prices_[0]};
    auto maxProfit{0};
    for(auto const price: prices_ | vs::drop(1)) {
        auto const currProfit{price - minBuyPrice};
        maxProfit = std::max(maxProfit, currProfit);
        minBuyPrice = std::min(minBuyPrice, price);
    } 
    return maxProfit;
}
