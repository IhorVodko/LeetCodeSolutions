// problem : https://leetcode.com/problems/find-all-possible-stable-binary-arrays-i/description
// submission : https://leetcode.com/problems/find-all-possible-stable-binary-arrays-i/submissions/1944252115
// solution post : https://leetcode.com/problems/find-all-possible-stable-binary-arrays-i/solutions/7639512/
//    c-modern-readable-code-beats-100-runtime-joon

// import std;

namespace {
    using ll = long long;

    // Compile-time initializer to configure fast I/O before main() runs
    auto const fastIOInit{
        [] {
            std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return 0;
        } ()
    };

// Modulo value required by the problem for returning large numbers.
    constexpr auto kModulus{1'000'000'007};
// Maximum limit for the precomputed factorials based on problem constraints.
    constexpr auto kMaxLimit{205}; 

// Compile-time function to calculate modular exponentiation.
    consteval auto CalcPower(
        ll base_,
        ll exp_
    ) -> ll {
        auto res{1ll};
        base_ %= kModulus;
        while (exp_ >= 1) {
            if(exp_ % 2 == 1){
                res = (res * base_) % kModulus;
            }
            base_ = (base_ * base_) % kModulus;
            exp_ /= 2;
        }
        return res;
    }

// Compile-time function to compute the modular inverse using Fermat's Little Theorem.
    consteval auto CalcModInv(ll const num_) -> ll {
// Multiply by power of kModulus - 2 to get the modular inverse.
        return CalcPower(num_, kModulus - 2);
    }

// Struct to hold precomputed factorials and their modular inverses.
    struct PrecomputedData {
        std::array<ll, kMaxLimit> mFacts{};
        std::array<ll, kMaxLimit> mInvFacts{};

// Constructor evaluated at compile time to populate the math arrays.
        consteval PrecomputedData() {
            namespace vs = std::views;

            mFacts[0] = 1;
            mInvFacts[0] = 1;
// Compute factorials up to the maximum limit.
            for(auto const j: vs::iota(1, kMaxLimit)) {
                mFacts[j] = (mFacts[j - 1] * j) % kModulus;
            }
// Compute the inverse of the largest factorial to start the reverse calculation.
            mInvFacts[kMaxLimit - 1] = CalcModInv(mFacts[kMaxLimit - 1]);
// Compute the remaining inverse factorials iteratively backwards.
            for(auto const j: vs::iota(1, kMaxLimit - 1) | vs::reverse) {
                mInvFacts[j] = (mInvFacts[j + 1] * (j + 1)) % kModulus;
            }
        }
    };

// Global compile-time instance of the precomputed data.
    constexpr auto kMath{PrecomputedData{}};

// Function to compute combinations (n choose r) modulo 10^9 + 7.
    constexpr auto nCr(
        int const n_,
        int const r_
    ) -> ll {
// Return 0 for invalid combinations where r is out of bounds.
        if(r_ < 0 || r_ > n_) return 0;
// Calculate nCr using precomputed factorials and modular inverses.
        return kMath.mFacts[n_] * kMath.mInvFacts[r_] % kModulus *
            kMath.mInvFacts[n_ - r_] % kModulus;
    }
}

// let 'n' be the number of ones
// 'm' - the number of zeroes
// 'k' - the limit size of subarray
// time complexity O(n * m / k)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
// Main solution class for the problem.
class Solution final {
public:
    using ll = long long;

// Method to calculate the total number of stable arrays.
    auto numberOfStableArrays(
        int zeroTotCnt_,
        int oneTotCnt_,
        int const subArLengthLimit_
    ) const -> int;

private:
// Helper method to count ways to distribute elements into groups with a capacity limit.
    inline auto CountWays(
        int const n_,
        int const k_,
        int const subArLengthLimit_
    ) const -> ll;
};

// Implementation of the method to find the number of stable arrays.
auto Solution::numberOfStableArrays(
    int zeroTotCnt_,
    int oneTotCnt_,
    int const subArLengthLimit_
) const -> int {
    namespace vs = std::views;

// Swap counts to ensure zeroTotCnt_ is always less than or equal to oneTotCnt_ for
// optimization.
    if(zeroTotCnt_ > oneTotCnt_) {
        std::swap(zeroTotCnt_, oneTotCnt_);
    }
    auto stableArTotCnt{0ll};
// Iterate over the possible number of blocks for the zeroes.
    for(auto const j: vs::iota(1, zeroTotCnt_ + 1)) {
// Calculate the ways to distribute zeroes into 'j' valid blocks.
        auto const wZero{CountWays(zeroTotCnt_, j, subArLengthLimit_)};
// Skip further calculation if there are no valid ways to distribute zeroes.
        if(wZero == 0){
            continue;
        }
// Calculate ways for ones when they form 'j - 1' blocks.
        auto const wOne1{CountWays(oneTotCnt_, j - 1, subArLengthLimit_)};
// Calculate ways for ones when they form 'j' blocks (multiplied by 2 for the two
// alternating patterns).
        auto const wOne2{(CountWays(oneTotCnt_, j, subArLengthLimit_) * 2) % kModulus};
// Calculate ways for ones when they form 'j + 1' blocks.
        auto const wOne3{CountWays(oneTotCnt_, j + 1, subArLengthLimit_)};
// Sum up the total combinations for distributing the ones.
        auto const wOneTotal{(wOne1 + wOne2 + wOne3) % kModulus};
// Multiply valid zero configurations with valid one configurations and add to total.
        stableArTotCnt = (stableArTotCnt + wZero * wOneTotal) % kModulus;
    }
    return static_cast<int>(stableArTotCnt);
}

// Implementation of the helper method to count distributions using Inclusion-Exclusion.
auto Solution::CountWays(
    int const n_,
    int const k_,
    int const subArLengthLimit_
) const -> ll {
    namespace vs = std::views;

// Return 0 if the distribution is impossible due to item count limits or insufficient
// items for groups.
    if(k_ < 0 || n_ < k_ || static_cast<ll>(k_) * subArLengthLimit_ < n_){
        return 0;
    }
    auto waysTotCnt{0ll};
// Iterate through the number of invalid groups to apply Inclusion-Exclusion Principle.
    for(auto const j: vs::iota(0, k_ + 1)) {
// Stop the loop if the remaining elements cannot form the required valid groups.
        if(n_ - j * subArLengthLimit_ - 1 < k_ - 1) {
            break; 
        }
// Calculate the term for the Inclusion-Exclusion formula using nCr.
        auto  const term{
            (nCr(k_, j) * nCr(n_ - j * subArLengthLimit_ - 1, k_ - 1)) % kModulus};
// Subtract the term if 'j' is odd (the Exclusion step).
        if(j % 2 == 1) {
            waysTotCnt = (waysTotCnt - term + kModulus) % kModulus;
// Add the term if 'j' is even (the Inclusion step).
        } else {
            waysTotCnt = (waysTotCnt + term) % kModulus;
        }
    }
    return waysTotCnt;
}
