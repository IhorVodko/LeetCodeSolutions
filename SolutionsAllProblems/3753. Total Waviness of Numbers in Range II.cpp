// problem : https://leetcode.com/problems/total-waviness-of-numbers-in-range-ii/description/?envType=daily-question&envId=2026-06-05
// submission : https://leetcode.com/problems/total-waviness-of-numbers-in-range-ii/submissions/2023448686
// solution post : https://leetcode.com/problems/total-waviness-of-numbers-in-range-ii/solutions/8315750/
//    c-modern-readable-code-beats-100-runtime-2ol9

// Approach : Combinatorial Digit Analysis via Prefix-Suffix Permutations
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the given range upper limit
// 'M' - maximum possible range upper limit
// complexity :  O(log(n))
// complexity : O(log(M))

// import std;

namespace {

namespace vs = std::views;
namespace rs = std::ranges;

using ll = long long;

auto constexpr kBase{10}; 
auto constexpr kMaxDigits64Bit{19}; 

// Precomputes powers of 10 to eliminate repetitive scaling overhead
constexpr auto kPow10Arr{[] {
    auto arr{std::array<ll, kMaxDigits64Bit>{}};
    rs::generate(arr, [val = 1ull] () mutable {
        auto const curr{static_cast<ll>(val)};
        val *= kBase;

        return curr;
    });

    return arr;
}()};

// Arithmetic progression sum for bounding logic
constexpr auto SumFirstN{[] (ll const n_) -> ll {
    return n_ > 0 ? n_ * (n_ + 1) / 2 : 0;
}};

// Combinations of picking 3 items for triplet logic bounds
constexpr auto Choose3OfN{[] (ll const n_) -> ll {
    return n_ >= 3 ? n_ * (n_ - 1) * (n_ - 2) / 6 : 0; 
}};

} // namespace 

class Solution final {
public:
    using ll = long long;

    [[nodiscard]]
    static auto totalWaviness(
        ll const numLoLim_,
        ll const numUpLim_
    ) -> ll;

private:
    [[nodiscard]]
    static auto Compute(ll const num_) -> ll;

    [[nodiscard]]
    static auto EvaluatePosition(
        ll const num_,
        int const pos_
    ) -> ll;

    static constexpr auto kMaxDigit{9}; 
    static constexpr auto kLeadingZeroFalsePeaks{45}; 
    static constexpr auto kValidTripletsPer1000{570};
    static constexpr auto kFirstValidNum{100};
    static constexpr auto kUnequalDigitPairsCnt{90};

};

auto Solution::totalWaviness(
    ll const numLoLim_,
    ll const numUpLim_
) -> ll {
    // Evaluates range bounds mathematically using prefix sums subtraction
    return Compute(numUpLim_ + 1) - Compute(numLoLim_);
}

auto Solution::Compute(ll const num_) -> ll {
    namespace vs = std::views;
    namespace rs = std::ranges;

    // Triplet sequences intrinsically require at least 3 digits
    if(num_ < kFirstValidNum) {
        return 0;
    }

    // Determine exact digit count to establish valid central positions
    auto const digitCnt{rs::distance(
        kPow10Arr.cbegin(),
        rs::upper_bound(kPow10Arr, num_)
    )};

    auto positions{vs::iota(1, digitCnt - 1)};
    // Aggregate valid combinations sequentially across all potential sequence centers
    auto const totalValidWays{rs::fold_left(
        positions | vs::transform([num_] (int const pos_) {
            return EvaluatePosition(num_, pos_); }),
        0ll,
        std::plus{}
    )};

    return totalValidWays;
}

auto Solution::EvaluatePosition(
    ll const num_,
    int const pos_
) -> ll {
    // Extract sequence components relative to the central pivot position
    auto const suffix{num_ % kPow10Arr[pos_]};
    auto const suffixMult{kPow10Arr[pos_ - 1]};
    auto const prefix{num_ / kPow10Arr[pos_ + 1]}; 
    auto const lDigit{(num_ / kPow10Arr[pos_ + 1]) % 10};
    auto const midDigit{(num_ / kPow10Arr[pos_]) % 10};
    auto const rDigit{num_ / kPow10Arr[pos_ - 1] % 10};
    auto wayCnt{0ll};

    // Evaluate structural locks dictated by exact digit inequalities
    auto const isValley{lDigit > midDigit && midDigit < rDigit};
    auto const isPeak{lDigit < midDigit && midDigit > rDigit};
    auto const isPotentialPeak{lDigit < midDigit && midDigit <= rDigit};

    if(isValley) {
        wayCnt += suffix - suffixMult * (midDigit + 1);
    }
    if(isPeak) {
        wayCnt += suffix;
    }
    // Scale combinations relying on right-side suffix manipulation
    if(isPotentialPeak) {
        wayCnt += suffixMult * midDigit;
    }

    // Adjust for variable peak centers bounded against fixed left digits
    auto const maxDiffMid{kMaxDigit - std::min(lDigit, midDigit)};
    wayCnt += (kLeadingZeroFalsePeaks - SumFirstN(maxDiffMid)) * suffixMult;
    if(lDigit < midDigit) {
        wayCnt += (SumFirstN(midDigit - 1) - SumFirstN(lDigit)) * suffixMult;
    }

    // Compute permutations with smaller left digits ensuring structural compliance
    auto const maxDiffLeft{kMaxDigit - lDigit};
    auto const wayCntWithSmallerLDigit{
        (lDigit * kUnequalDigitPairsCnt) - Choose3OfN(lDigit + 1) - Choose3OfN(11) +
            Choose3OfN(maxDiffLeft + 2)
    };
    wayCnt += wayCntWithSmallerLDigit * suffixMult;

    // Filter out false peaks caused by leading zeros when prefix is out of bounds
    if(prefix < kBase) {
        wayCnt -= kLeadingZeroFalsePeaks * suffixMult;
    }

    // Append baseline unrestricted combinations using a constant distribution factor
    wayCnt += kValidTripletsPer1000 * (prefix / kBase) * suffixMult;
    if(prefix >= kBase) {
        wayCnt -= kLeadingZeroFalsePeaks * suffixMult;
    }

    return wayCnt;
}
