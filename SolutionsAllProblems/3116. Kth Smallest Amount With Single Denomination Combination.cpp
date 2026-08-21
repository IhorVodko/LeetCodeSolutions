// problem : https://leetcode.com/problems/kth-smallest-amount-with-single-denomination-combination/description/
// submission : https://leetcode.com/problems/kth-smallest-amount-with-single-denomination-combination/submissions/2115460105
// solution post : https://leetcode.com/problems/kth-smallest-amount-with-single-denomination-combination/solutions/8474881/
//    simplanation-simple-explanation-by-cyber-999n

// Approach : Binary Search over Answer Space with Principle of Inclusion-Exclusion (PIE)
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis

// N: The total number of elements in the initially provided coins array.
// C: The count of independent primitive coins surviving the filtering process (C≤N≤15).
// K: The required rank index as stated in the problem.
// M​: The ultimate upper limit of the binary search interval space (≈min(coins)×K).

// Time :  O(N * log(N) + N * C + 2^C + 2^C * log(M))
// Space : O(2^C)

// import std;

// #include <vector>
// #include <numeric>
// #include <ranges>
// #include <algorithm>
// #include <bit>

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);

        return 0;
    } ()
};

// Cache to hold precomputed subset LCM and its corresponding PIE
//  (Principle of Inclusion-Exclusion) coefficient sign
struct CoinSubsetLcm {
    long long lcm{};
    long long sign{};
};

} // namespace
    
class Solution final {
public:
    [[nodiscard]]
    static auto findKthSmallest(
        std::vector<int> & coins_,
        int const kthSmallestRank_
    ) -> long long;
};

auto Solution::findKthSmallest(
    std::vector<int> & coins_,
         int const kthSmallestRank_
) -> long long {
    // 1. Sort coins to process smaller denominations first for optimal reduction
    rs::sort(coins_);

    auto usedCoins{std::vector<int>{}};
    for(auto const coin: coins_) {
        // 2. Extract primitive denominations by filtering out redundant multiples
        if(rs::none_of(usedCoins, [&] (auto const usedCoin_) {
            return coin % usedCoin_ == 0;
        })) {
            usedCoins.emplace_back(coin);
        }
    }

    auto const totCoins{usedCoins.size()};
    auto const totSubsets{std::size_t{1} << totCoins};
    // 3. Define the maximum possible amount boundary for the binary search space
    auto const maxAmount{static_cast<long long>(usedCoins.front()) * kthSmallestRank_};

    auto dpLcm{std::vector<long long>(totSubsets, 1)};
    auto CoinSubsetLcms{std::vector<CoinSubsetLcm>{}};
    CoinSubsetLcms.reserve(totSubsets);

    // 4. Compute subset LCMs dynamically using properties of sub-masks
    for(auto mask{1u}; mask < totSubsets; ++mask) {
        auto const parentLcm{dpLcm[mask & (mask - 1)]};
        auto const currCoin{usedCoins[std::countr_zero(mask)]};
        auto const currLcmMult{currCoin / std::gcd(parentLcm, currCoin)};

        // Discard LCMs exceeding the search space to prevent integer overflows
        if(parentLcm > maxAmount / currLcmMult) {
            dpLcm[mask] = maxAmount + 1;
        } else {
            dpLcm[mask] = parentLcm * currLcmMult;

            auto sign{(std::popcount(mask) % 2 == 1) ? 1ll : -1ll};

            CoinSubsetLcms.emplace_back(dpLcm[mask], sign);
        }
    }

    // 5. Apply the Principle of Inclusion-Exclusion to count valid formed amounts
    auto calcAmountRank{[&] (auto const amount_) {
        auto amountContribution{CoinSubsetLcms | vs::transform([=] (auto const subset_) {
            return amount_ / subset_.lcm * subset_.sign;
        })};

        return rs::fold_left(amountContribution, 0ll, std::plus{});
    }};

    // 6. Binary search the minimal amount yielding exactly the required rank target
    auto kthSmallestAmountIt{rs::partition_point(
        vs::iota(1ll, maxAmount + 1),
        [&] (auto const amount_) {
            return calcAmountRank(amount_) < kthSmallestRank_;
        }
    )};

    return *kthSmallestAmountIt;
}
