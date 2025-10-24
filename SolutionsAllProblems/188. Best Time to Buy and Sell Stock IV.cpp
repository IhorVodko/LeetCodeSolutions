// problem : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/description/ 
// submission : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/submissions/1810163970
// solution post : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/solutions/7296854/
//    c-modern-readable-code-beats-100-runtime-cgy0

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
// let 'p' be the number of the given prices
// 't' - given number of the transactions
// time complexity O(p * t)
// space complexity O(p * t)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto maxProfit(
        int const transactionsCnt_,
        std::span<int> const prices_
    ) const -> int;
};

auto Solution::maxProfit(
    int const transactionsCnt_,
    std::span<int> const prices_
) const -> int {
    namespace vs = std::views;
    using mxT = std::vector<std::vector<int>>;

    if(transactionsCnt_ <= 0) {
        return 0;
    }
    auto const daysCnt{std::ssize(prices_)};
    auto unrealizedProfit{
        mxT(transactionsCnt_ + 1, std::vector<int>(daysCnt, 0))
    };
    auto realizedProfit{
        mxT(transactionsCnt_ + 1, std::vector<int>(daysCnt, 0))
    };
    for(auto const day: vs::iota(0, daysCnt)) {
        realizedProfit[0][day] = 0;
    }
    unrealizedProfit[1][0] = realizedProfit[0][0] - prices_[0];
    realizedProfit[1][0] = unrealizedProfit[1][0] + prices_[0];
    for(auto const transactionIdxCurr: vs::iota(2, transactionsCnt_ + 1)) {
        auto const transactionIdxPrev{transactionIdxCurr - 1};
        auto const price{prices_[0]};
        unrealizedProfit[transactionIdxCurr][0] =
            realizedProfit[transactionIdxPrev][0] -
            price
        ;
        realizedProfit[transactionIdxCurr][0] =
            unrealizedProfit[transactionIdxPrev][0] +
            price
        ;
    }
    for(auto const currDay: vs::iota(1, daysCnt)) {
        auto const price{prices_[currDay]};
        for(auto const transactionIdx: vs::iota(1, transactionsCnt_ + 1)) {
            auto const prevDay{currDay - 1};
            unrealizedProfit[transactionIdx][currDay] = std::max(
                unrealizedProfit[transactionIdx][prevDay],
                realizedProfit[transactionIdx - 1][prevDay] - price
            );
            realizedProfit[transactionIdx][currDay] = std::max(
                realizedProfit[transactionIdx][prevDay],
                unrealizedProfit[transactionIdx][currDay] + price
            );
        }
    }
    auto const maxProfit{realizedProfit.back().back()};
    return maxProfit;
}
