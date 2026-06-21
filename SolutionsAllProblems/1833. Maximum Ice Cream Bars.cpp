// problem : https://leetcode.com/problems/maximum-ice-cream-bars/description
// submission : https://leetcode.com/problems/maximum-ice-cream-bars/submissions/2041286361
// solution post : https://leetcode.com/problems/maximum-ice-cream-bars/solutions/8349911/c-modern-readable-code-beats-100-runtime-bgml

// Approach : Greedy Optimization via Counting Sort
// Runtime : 0 ms, beats 100.00 %


// Complexity
// let 'n' be the number of costs
// 'm' - maximum cost
// Time :  O(n + m)
// Space : O(m)

// import std;

class Solution final {
public:
    [[nodiscard]]
    static auto maxIceCream(
        std::vector<int> const & costs_,
        int const budget_
    ) -> int;
};

auto Solution::maxIceCream(
    std::vector<int> const & costs_,
    int const budget_
) -> int {
    namespace rs = std::ranges;
    namespace vs = std::views;

    // Use frequency array (counting sort) to bypass general O(N log N) sorting
    auto cntPerCostArr{std::vector<int>(rs::max(costs_) + 1)};
    for(auto const cost: costs_) {
        ++cntPerCostArr[cost];
    }

    auto boughtTot{0};
    for(auto spent{0};
        auto const cost: vs::iota(0, std::ssize(cntPerCostArr))
    ) {
        auto const costCnt{cntPerCostArr[cost]};
        if(costCnt == 0) {
            continue;
        }

        // Greedily acquire maximum units at the current price point
        auto const boughtCnt{std::min((budget_ - spent) / cost, costCnt)};
        boughtTot += boughtCnt;
        spent += boughtCnt * cost;
        
        // Halt processing once budget restricts buying the full stock
        if(boughtCnt == 0 || boughtCnt < costCnt) {
            return boughtTot;
        }
    }

    return boughtTot;
}

namespace {

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace
