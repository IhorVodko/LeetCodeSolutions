// problem : https://leetcode.com/problems/maximum-total-subarray-value-i/description
// submission : https://leetcode.com/problems/maximum-total-subarray-value-i/submissions/2027638506
// solution post : 

// Approach : Greedy Min-Max Optimization
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the number of elements in the array
// Time :  O(n)
// Space : O(1)

// import std;

class Solution final{
public:
    using ll = long long;

    [[nodiscard]]
    static auto maxTotalValue(
        std::vector<int> const & nums_,
        int const subArrTot_
    ) -> ll;
};

auto Solution::maxTotalValue(
    std::vector<int> const & nums_,
    int const subArrTot_
) -> ll {
    namespace rs = std::ranges;

    // Isolate global boundaries to ensure the largest possible difference
    auto const [minNum, maxNum]{rs::minmax(nums_)};
    auto const maxTotalVal{static_cast<ll>(subArrTot_) * (maxNum- minNum)};

    return maxTotalVal;
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
