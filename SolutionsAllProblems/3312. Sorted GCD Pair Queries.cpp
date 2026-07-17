// problem : https://leetcode.com/problems/sorted-gcd-pair-queries/description
// submission : https://leetcode.com/problems/sorted-gcd-pair-queries/submissions/2071469567
// solution post : https://leetcode.com/problems/sorted-gcd-pair-queries/solutions/8403747/modern-readable-code-optimal-time-comple-e2h8

// Approach : Frequency Array with Inclusion-Exclusion (Sieve Method)
// Runtime : 34 ms, beats 89.33 %

// Complexity analysis
// let 'n' be the count of numbers
// 'm' - maximum number
// 'q' - number of queries
// Time : O(n + m * log(m) + q * log(m))
// Space : O(m)

// import std;

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    }()
};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    static auto gcdValues(
        std::vector<int> const & nums_,
        std::vector<long long> const & queries_
    ) -> std::vector<int>;
};

auto Solution::gcdValues(
    std::vector<int> const & nums_,
    std::vector<long long> const & queries_
) -> std::vector<int> {
    auto const maxNum{rs::max(nums_)};
    auto const sz{static_cast<std::size_t>(maxNum + 1)};

    // Frequency of each number up to maxVal
    static thread_local auto freqPerNum{std::vector<long long>{}};
    // Array to store exact occurrence count of each GCD pair, and later prefix sums
    static thread_local auto cntPerExactPair{std::vector<long long>{}};

    freqPerNum.assign(sz, 0ll);
    cntPerExactPair.assign(sz, 0ll);

    for(auto const num: nums_) {
        ++freqPerNum[num];
    }    

     // Compute exact pairs for each GCD from maxVal down to 1
    for(auto const divisor: vs::iota(1, maxNum + 1) | vs::reverse) {
        auto multiplesCnt{0ll};

        // Count all numbers that are multiples of the current GCD candidate 'divisor'
        for(auto const multiplier: vs::iota(1, maxNum / divisor + 1)) {
            multiplesCnt += freqPerNum[multiplier * divisor];
        }

        // Total pairs where the GCD is a multiple of 'divisor'
        auto pairsCnt{multiplesCnt * (multiplesCnt - 1ll) / 2ll};

        // Subtract pairs that have a strictly larger multiple of 'divisor' as their GCD
        for(auto const multiplier: vs::iota(2, maxNum / divisor + 1)) {
            pairsCnt -= cntPerExactPair[multiplier * divisor];
        }

        cntPerExactPair[divisor] = pairsCnt;
    }

    // Convert exactPairs into prefix sums to facilitate binary search
    std::partial_sum(cntPerExactPair.begin(), cntPerExactPair.end(),
        cntPerExactPair.begin());

    // For each query, find the corresponding GCD
    return 
        queries_ |
        vs::transform([] (auto const query_) {
            return static_cast<int>(rs::distance(
                cntPerExactPair.begin(),
                rs::upper_bound(cntPerExactPair, query_)
            ));
        }) |
        rs::to<std::vector>()
    ;
}
