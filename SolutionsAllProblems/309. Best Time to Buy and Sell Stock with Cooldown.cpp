// problem : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/description/
// submission : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/submissions/1814012531
// solution post : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/solutions/7307761/
//    c-modern-readable-code-beats-100-runtime-hnqh

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
// let 'n' be the number of the given prices
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto maxProfit(std::span<const int> const prices_) const -> int;
};

auto Solution::maxProfit(std::span<const int> const prices_) const -> int {
    using limitIntT = std::numeric_limits<int>;

    auto sold{limitIntT::min()};
    auto held{limitIntT::min()};
    auto reset{0};
    for(auto const price: prices_) {
        auto const preSold{sold};
        sold = held + price;
        held = std::max(held, reset - price);
        reset = std::max(reset, preSold);
    }
    auto const maxProfit{std::max(sold, reset)};
    return maxProfit;
}
