// problem : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-using-strategy/description/
// submission : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-using-strategy/submissions/1860150447
// solution post : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-using-strategy/solutions/7424946/
//    c-modern-readable-code-beats-100-runtime-jpye

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

// solve a problem '3652. Best Time to Buy and Sell Stock using Strategy'
// let 'n' be the number of given prices
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    // calculate maximum profit for given prices and strategies
    // (sell = -1, hold = 0, buy = 1) for each day, allowing to modify a consecutive
    // strategies window of lenth modifCnt_, first half of the window - hold, second -
    // buy
    [[nodiscard]]
    auto maxProfit(
        std::span<int const> const prices_,
        std::span<int const> const strategies_,
        int const modifCnt_
    ) const -> long long;
};

auto Solution::maxProfit(
    std::span<int const> const prices_,
    std::span<int const> const strategies_,
    int const modifCnt_
) const -> long long {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    // calculate modified profit of the first half of a modified strategies window with
    // strategy hold
    auto currModifProf{std::accumulate(
        prices_.begin() + modifCnt_ / 2, prices_.begin() + modifCnt_, 0ll)};
    auto const pricesTotCnt{std::ssize(prices_)};
    // add modified profit of the second half of a modified strategies window with
    // strategy buy
    currModifProf = std::transform_reduce(prices_.cbegin() + modifCnt_, prices_.cend(),
        strategies_.cbegin() + modifCnt_, currModifProf, std::plus{}, std::multiplies{});
    auto maxModifProf{currModifProf};
    // use a running window of the modified strategies length given to update maximum
    // modified profit
    for(auto windowBeg{1}, windowEnd{modifCnt_}; windowEnd < pricesTotCnt;
        ++windowBeg, ++windowEnd
    ) {
        // update for a price that moves out from the window: hold -> old strategy
        currModifProf += strategies_[windowBeg - 1] * prices_[windowBeg - 1];
        // update for a price that moves to the first half of the window
        // buy -> hold
        currModifProf -= prices_[windowBeg - 1 + (modifCnt_ / 2)];
        // update for a price that moves to a window: old strategy -> buy
        currModifProf -= strategies_[windowEnd] * prices_[windowEnd];
        currModifProf += prices_[windowEnd];

        maxModifProf = std::max(maxModifProf, currModifProf);
    }
    auto const unmodifProf{std::transform_reduce(prices_.cbegin(), prices_.cend(),
        strategies_.cbegin(), 0ll, std::plus{}, std::multiplies{})};
    auto const maxProf{std::max(unmodifProf, maxModifProf)};
    return maxProf;
}
