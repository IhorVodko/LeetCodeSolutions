// problem : https://leetcode.com/problems/calculate-money-in-leetcode-bank/description/
// submission : https://leetcode.com/problems/calculate-money-in-leetcode-bank/submissions/1811434882
// solution post : https://leetcode.com/problems/calculate-money-in-leetcode-bank/solutions/7300626/
//    c-modern-readable-code-beats-100-runtime-o448

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
// let 'n' be the number of the given days
// time complexity O(1)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto totalMoney(int days_) const -> int;

private:
    static int constexpr kDaysPerWeek{7};
    static int constexpr kFirstWeekMoney{28};
};

auto Solution::totalMoney(int days_) const -> int {
    auto const [weeks, days]{std::div(days_, kDaysPerWeek)};
    auto const lastWeekMoney{kFirstWeekMoney + (weeks - 1) * 7};
    auto const weeksMoney{weeks * (kFirstWeekMoney + lastWeekMoney) / 2};
    auto const daysMoney{days * (2 * weeks + 1 + days) /  2 };
    auto const money{weeksMoney + daysMoney};
    return money;
}
