// problem : https://leetcode.com/problems/number-of-sets-of-k-non-overlapping-line-segments/description
// submission : https://leetcode.com/problems/number-of-sets-of-k-non-overlapping-line-segments/submissions/2143710870
// solution post : https://leetcode.com/problems/number-of-sets-of-k-non-overlapping-line-segments/solutions/8524610/
//  simplanation-simple-explanation-by-cyber-gn2u

// Approach : Combinatorial Bijection via Expanded Space
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the required number of line segments
// Time :  O(n)
// Space : O(1)

// import std;

// #include <algorithm>
// #include <cstdint>
// #include <ios>
// #include <iostream>
// #include <ranges>

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

// Modulo applied to prevent integer overflow on large combinations
constexpr auto kModVal{1'000'000'007ll};
// Endpoints required to define a single valid line segment
constexpr auto kPointCntPerSegment{2ll};
// Offset applied to convert point counts into segment gaps
constexpr auto kPointOffset{1ll};
// Exponent shift for modular multiplicative inverse via Fermat
constexpr auto kFermatLittleTheoremOffset{2ll};

// Calculate the product of a sequence of numbers modulo
constexpr auto calcProdMod{[] [[nodiscard]] (
    auto const startVal_,
    auto const multCnt_
) {
    auto const offsetRng{vs::iota(0ll, multCnt_)};

    return rs::fold_left(
        offsetRng,
        1ll,
        [=] (const auto accumProd_, const auto offset_) {
            const auto factor{startVal_ - offset_};
            return (accumProd_ * factor) % kModVal;
        }
    );
}};

constexpr auto isOdd{[] [[nodiscard]] (auto const num_) { return num_ % 2 == 1; }};

// Calculate the modular inverse using exponentiation by squaring
constexpr auto calcModInv{[] [[nodiscard]] (
    auto base_,
    auto exp_
) {
    auto res{1ll};

    while(exp_ > 0ll) {
        if(isOdd(exp_)) {
            res = (res * base_) % kModVal;
        }

        base_ = (base_ * base_) % kModVal;
        exp_ /= 2ll;
    }

    return res;
}};

// Optimize standard I/O stream operations performance.
[[maybe_unused]]
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

}

class Solution final {
public:
    /**
     * Calculates the number of ways to draw non-overlapping line segments.
     * Utilizes a combinatorics approach: it maps the problem to choosing 
     * 2 * numberOfSegments endpoints from (numberOfPoints + numberOfSegments - 1) 
     * possible positions, turning it into a stars-and-bars combinations problem.
     */
    [[nodiscard]]
    static auto numberOfSets(
        int const pointTot_,
        int const segmentTot_
    ) -> int;
};

auto Solution::numberOfSets(
    int const pointTot_,
    int const segmentTot_
) -> int {
    auto const pointTot{static_cast<long long>(pointTot_)};
    auto const segmentTot{static_cast<long long>(segmentTot_)};
    
    // Calculate N and K for the combinations formula C(N, K)
    // 1. Map problem to choosing points from an expanded space to handle sharing
    auto const itemTot{pointTot + segmentTot - kPointOffset};
    // 2. Determine total unique endpoints needed for the target segments
    auto const itemToSelect{segmentTot * kPointCntPerSegment};

    // 3. Verify the expanded space can accommodate the required endpoints
    if(itemTot < itemToSelect) {
        return 0;
    }

    // 4. Compute partial factorials required for the combination formula
    auto const numerator{calcProdMod(itemTot, itemToSelect)};
    auto const denominator{calcProdMod(itemToSelect, itemToSelect)};

    // 5. Calculate denominator's modular inverse using Fermat's Little Theorem
    const auto targetExp{kModVal - kFermatLittleTheoremOffset};
    const auto invDenominator{calcModInv(denominator, targetExp)};

    // 6. Combine terms to find total valid configurations
    const auto combTot{(numerator * invDenominator) % kModVal};

    return static_cast<int>(combTot);
}
