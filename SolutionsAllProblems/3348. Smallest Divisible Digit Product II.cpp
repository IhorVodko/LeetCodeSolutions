// problem : https://leetcode.com/problems/smallest-divisible-digit-product-ii/description
// submission : https://leetcode.com/problems/smallest-divisible-digit-product-ii/submissions/2098332245
// solution post : https://leetcode.com/problems/smallest-divisible-digit-product-ii/solutions/8447686/
//    simplanation-simple-explanation-by-cyber-dihz

// Approach : Greedy Prefix Matching with Minimum Suffix Length
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' the string length (count of digits in a given number)
// Time :  O(n)
// Space : O(n)

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
    } ()
};

// Multipliers to either subtract or add prime factors from the current state.
constexpr auto kConsume{-1};
constexpr auto kRestore{1};

constexpr auto kNoSolution{"-1"};
constexpr auto kZeroChr{'0'};
constexpr auto kTotPrimes{4};
constexpr auto kTotDigits{10};
constexpr auto kPrimes{std::array<int, 3>{{3, 5, 7}}};

// Precomputed prime factor counts (2, 3, 5, 7) for each digit from 0 to 9.
constexpr auto KDigitPrimes{std::array<std::array<int, kTotPrimes>, kTotDigits>{{
    {0,0,0,0}, {0,0,0,0}, {1,0,0,0}, {0,1,0,0}, {2,0,0,0}, 
    {0,0,1,0}, {1,1,0,0}, {0,0,0,1}, {3,0,0,0}, {0,2,0,0}
}}};

constexpr auto toChar{[] (auto const digit_) {
    return static_cast<char>(kZeroChr + digit_);
}};

constexpr auto toDigit{[] (auto const chr_) {
    return static_cast<int>(chr_ - kZeroChr);
}};

// Calculates the absolute minimum number of digits needed for given prime factors.
constexpr auto calcMinSuffLen{[] (
    std::array<int, kTotPrimes> const & primeExps_
) -> int {
    auto const needed2s{std::max(0, primeExps_[0])};
    auto const needed3s{std::max(0, primeExps_[1])};
    auto const needed5s{std::max(0, primeExps_[2])};
    auto const needed7s{std::max(0, primeExps_[3])};

    // Pack factors into 8s (2^3) and 9s (3^2) to minimize total length.
    auto length{needed2s / 3 + needed3s / 2 + needed5s + needed7s};
    auto const rem2{needed2s % 3};
    auto const rem3{needed3s % 2};

    // Handle leftover 2s and 3s optimally by combining them into 6, 4, 3, or 2.
    if(rem2 == 1 && rem3 == 1) {
        ++length;
    } else if(rem2 == 2 && rem3 == 1) {
        length += 2;
    } else {
        length +=
            (rem2 > 0 ? 1 : 0) +
            (rem3 > 0 ? 1 : 0)
        ;
    }

    return length;
}};

// Constructs the lexicographically smallest suffix of length len_ for required primes.
constexpr auto buildOptimalSuff{[] (
    std::array<int, kTotPrimes> const & primeExps_,
    int const len_
) -> std::string {
    auto const needed2s{std::max(0, primeExps_[0])};
    auto const needed3s{std::max(0, primeExps_[1])};
    auto const needed5s{std::max(0, primeExps_[2])};
    auto const needed7s{std::max(0, primeExps_[3])};
    
    // Base digit frequencies mapping primes to specific digits (5, 7, 8, 9).
    auto cnts{std::array<int, kTotDigits>{{
        0,        0, 0,        0,            0,
        needed5s, 0, needed7s, needed2s / 3, needed3s / 2
    }}};

    auto const rem2{needed2s % 3};
    auto const rem3{needed3s % 2};

    // Map prime remainders to the smallest possible combination of digits.
    if(rem2 == 1 && rem3 == 1) {
        cnts[6] = 1;
    } else if(rem2 == 2 && rem3 == 1) {
        cnts[2] = 1;
        cnts[6] = 1;
    } else {
        if(rem2 == 1) {
            cnts[2] = 1;
        } else if(rem2 == 2) {
            cnts[4] = 1;
        }

        if(rem3 == 1) {
            cnts[3] = 1;
        } 
    }

    // Pad unused suffix length with 1s to maintain exact requested length.
    auto const used{rs::fold_left(cnts | vs::drop(2), 0, std::plus{})};

    cnts[1] = len_ - used;

    auto suff{""s};
    suff.reserve(len_);

    // Construct final string in ascending digit order to ensure smallest permutation.
    for(auto const digit: vs::iota(1, kTotDigits)) {
        suff.append(cnts[digit], toChar(digit));
    }

    return suff;
}};

// Adjusts the active prime counts based on the factors of the supplied digit.
constexpr auto applyDigit{[] (
    std::array<int, kTotPrimes> & primeExps_,
    int const digit_,
    int const mult_
) -> void {
    for(auto const idx: vs::iota(0, kTotPrimes)) {
        primeExps_[idx] += mult_ * KDigitPrimes[digit_][idx];
    }
}}; 

} // namespace

class Solution final {
public:
    [[nodiscard]]
    static auto smallestNumber(
        std::string const & num_,
        long long targetProd_
    ) -> std::string;
};

auto Solution::smallestNumber(
    std::string const & num_,
    long long targetProd_
) -> std::string {
    // 1. Determine target prime requirements.
    auto targetPrimeExps{std::array<int, kTotPrimes>{}};
    targetPrimeExps[0] = std::countr_zero(static_cast<unsigned long long>(targetProd_));

    targetProd_ >>= targetPrimeExps[0];

    // Extract remaining prime factors (3, 5, 7) from the target product.
    for(auto const [idx, prime]: vs::enumerate(kPrimes)) {
        while(targetProd_ % prime == 0) {
            ++targetPrimeExps[idx + 1];
            targetProd_ /= prime;
        }
    }

    // 2. Reject impossible targets missing valid digit factors.
    if(targetProd_ > 1) {
        return kNoSolution;
    }

    auto const numLen{static_cast<int>(num_.size())};
    auto currPrimeExps{targetPrimeExps};

    auto firstZeroIdx{numLen - 1};
    auto hasZero{false};

    // 3. Scan the string to find the first zero and update prime state.
    for(auto const idx: vs::iota(0, numLen)) {
        if(num_[idx] == kZeroChr) {
            firstZeroIdx = idx;
            hasZero = true;
            break;
        }
        applyDigit(currPrimeExps, toDigit(num_[idx]), kConsume);
    }

    // 4. Return original string if it is already a valid answer.
    if(!hasZero && calcMinSuffLen(currPrimeExps) == 0) {
        return num_;
    }

    // 5. Restore prime state up to the first valid prefix before a zero.
    currPrimeExps = targetPrimeExps;
    for(auto const idx: vs::iota(0, firstZeroIdx)) {
        applyDigit(currPrimeExps, toDigit(num_[idx]), kConsume);
    }

    // 6. Backtrack to find the rightmost digit that can be safely incremented.
    for(auto const idx: vs::iota(0, firstZeroIdx + 1) | vs::reverse) {
        // Ensure we strictly increment the digit at the current index.
        auto const startDigit{(idx < numLen && num_[idx] != kZeroChr) ?
            toDigit(num_[idx]) + 1 : 1
        };

        for(auto const candidateDigit: vs::iota(startDigit, kTotDigits)) {
            applyDigit(currPrimeExps, candidateDigit, kConsume);

            auto const availableLen{numLen - idx - 1};

            // 7. Build and return the optimized suffix upon finding a match.
            if(calcMinSuffLen(currPrimeExps) <= availableLen) {
                auto res{num_.substr(0, idx)};
                res.reserve(numLen);

                res += toChar(candidateDigit);
                res += buildOptimalSuff(currPrimeExps, availableLen);

                return res;
            } 

            // Revert candidate digit application to check the next one.
            applyDigit(currPrimeExps, candidateDigit, kRestore);
        }

        // Restore prefix digit prime counts as we backtrack further left.
        if(idx > 0) {
            applyDigit(currPrimeExps, toDigit(num_[idx - 1]), kRestore);
        }
    }

    // 8. Fallback to generating a longer optimal string from scratch.
    auto const minLen{calcMinSuffLen(targetPrimeExps)};
    auto const targetLen{std::max(numLen + 1, minLen)};

    return buildOptimalSuff(targetPrimeExps, targetLen);
}
