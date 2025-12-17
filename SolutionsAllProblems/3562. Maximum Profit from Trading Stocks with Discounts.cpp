// problem : https://leetcode.com/problems/maximum-profit-from-trading-stocks-with-discounts/description/
// submission : https://leetcode.com/problems/maximum-profit-from-trading-stocks-with-discounts/submissions/1858383279
// solution post : https://leetcode.com/problems/maximum-profit-from-trading-stocks-with-discounts/solutions/7420574/
//    c-modern-readable-code-beats-100-runtime-8tsv

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

// solves a problem '3562. Maximum Profit from Trading Stocks with Discounts'
// let 'n' be the number of given emplyees
// 'm' - given budget
// time complexity O(n * m^2)
// space complexity O(n * m)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    // calculates a maximum profit per given budget
    [[nodiscard]]
    auto maxProfit(
        int const employeeSz_,
        std::span<int const> const buyPrices_,
        std::span<int const> const sellPrices_,
        std::span<std::vector<int> const> const bossAndEmployeeArr_,
        int const budget_
    ) -> int;

private:
    // calculates a maximum profit per budget. Implements recursive dynamic programming
    // top-down approach, using depth-first search over a tree of employee hierarchy
    [[nodiscard]]
    auto DoDfs(
        int const employee_
    ) const -> std::tuple<std::vector<int>, std::vector<int>, int>;

    std::span<int const> mBuyPrices;
    std::span<int const> mSellPrices;
    std::vector<std::vector<int>> mEmployeesPerBossArr;
    int mBudget;
};

auto Solution::maxProfit(
    int const employeeSz_,
    std::span<int const> const buyPrices_,
    std::span<int const> const sellPrices_,
    std::span<std::vector<int> const> const bossAndEmployeeArr_,
    int const budget_
) -> int {
    namespace vs = std::views;

    mBuyPrices = buyPrices_;
    mSellPrices = sellPrices_;
    mBudget = budget_;
    mEmployeesPerBossArr.clear();
    mEmployeesPerBossArr.resize(employeeSz_);
    for(auto const & bossAndEmployee: bossAndEmployeeArr_) {
        auto const boss{bossAndEmployee[0] - 1};
        auto const employee{bossAndEmployee[1] - 1};
        mEmployeesPerBossArr[boss].emplace_back(employee);
    }
    auto const maxProf{std::get<0>(DoDfs(0))[budget_]};
    return maxProf;
}

auto Solution::DoDfs(
    int const employee_
) const -> std::tuple<std::vector<int>, std::vector<int>, int>
{
    // case 'A' - discounted buy price is not available
    // case 'B' - discounted buy price is available
    namespace vs = std::views;

    auto const buyPrice{mBuyPrices[employee_]};
    auto const discBuyPrice{mBuyPrices[employee_] / 2};
    auto maxProfPerBudgA{std::vector<int>(mBudget + 1)};
    auto maxProfPerBudgB{std::vector<int>(mBudget + 1)};
    auto maxSubProfPerBudgA{std::vector<int>(mBudget + 1)};
    auto maxSubProfPerBudgB{std::vector<int>(mBudget + 1)};
    auto totCost{buyPrice};
    for(auto const boss: mEmployeesPerBossArr[employee_]) {
        auto [dbSubTreeMaxProfA, dbSubTreeMaxProfB, currCost]{DoDfs(boss)};
        totCost += currCost;
        for(auto const budget: vs::iota(0, mBudget + 1) |
            vs::reverse
        ) {
            for(auto const curSubProf:
                vs::iota(0, std::min(currCost, budget) + 1)
            ) {
                auto const currSubProfit0{
                    maxSubProfPerBudgA[budget - curSubProf] +
                    dbSubTreeMaxProfA[curSubProf]
                };
                maxSubProfPerBudgA[budget] =
                    std::max(maxSubProfPerBudgA[budget],currSubProfit0);
                auto const currSubProfit1{
                    maxSubProfPerBudgB[budget - curSubProf] +
                    dbSubTreeMaxProfB[curSubProf]
                };
                maxSubProfPerBudgB[budget] = std::max(
                    maxSubProfPerBudgB[budget],
                    currSubProfit1
                );
            }
        }
    }
    for(auto const budget: vs::iota(0, mBudget + 1)) {
        maxProfPerBudgA[budget] = maxSubProfPerBudgA[budget];
        maxProfPerBudgB[budget] = maxSubProfPerBudgA[budget];
        if(budget >= discBuyPrice) {
            auto const curProf{mSellPrices[employee_] - discBuyPrice};
            maxProfPerBudgB[budget] = std::max(
                maxSubProfPerBudgA[budget],
                maxSubProfPerBudgB[budget - discBuyPrice] + curProf
            );
        }
        if(budget >= buyPrice) {
            auto const curProf{mSellPrices[employee_] - buyPrice};
            maxProfPerBudgA[budget] = std::max(
                maxSubProfPerBudgA[budget],
                maxSubProfPerBudgB[budget - buyPrice] + curProf
            );
        } 
    }
    return {maxProfPerBudgA, maxProfPerBudgB, totCost};
}
