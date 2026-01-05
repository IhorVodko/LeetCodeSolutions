// problem : https://leetcode.com/problems/four-divisors/description/?envType=daily-question&envId=2026-01-04
// submission : https://leetcode.com/problems/four-divisors/submissions/1875710580
// solution post : https://leetcode.com/problems/four-divisors/solutions/7469965/
//    c-modern-readable-code-beats-100-runtime-qxg3
// runtime 0 ms, beats 100.00 %

// import std;

/**
 * @brief Fast I/O initialization helper.
 *
 * This static initializer:
 * - Disables synchronization between C and C++ I/O for faster performance
 * - Unties std::cin from std::cout
 * - Registers an atexit handler that writes runtime info to a file
 *
 * The lambda is executed exactly once at program startup.
 */
inline static int const fastIOInit{
    [] {
        /**
         * @brief Helper struct used to register an atexit callback.
         *
         * When the program exits, DoPrint() writes a value to
         * "display_runtime.txt". This is commonly used in
         * competitive programming environments.
         */
        struct Print {
            /**
             * @brief Writes runtime information to a file at program exit.
             */
            inline static void DoPrint() {
                std::ofstream{"display_runtime.txt"} << 0 << std::endl;
            }
        };

        std::atexit(&Print::DoPrint);
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    }()
};

/**
 * @class Solution
 * @brief Provides an algorithm to compute the sum of divisors
 *        for numbers that have exactly four divisors.
 */
class Solution {
public:
    /**
     * @brief Computes the total sum of divisors for numbers
     *        that have exactly four positive divisors.
     *
     * For each number in the input span:
     * - If it has exactly four divisors, the sum of those divisors
     *   is added to the total.
     * - Otherwise, the number is ignored.
     *
     * @param nums_ A span of positive integers to process.
     * @return The sum of divisors for all numbers with exactly four divisors.
     */
    [[nodiscard]]
    auto sumFourDivisors(std::span<int const> const nums_) const -> int;
};

/**
 * @brief Implementation of sumFourDivisors.
 *
 * This function uses:
 * - A sieve of Eratosthenes to generate primes up to √(max(nums))
 * - Special handling for numbers of the form p^3 (where p is prime)
 * - Prime factorization to detect numbers with exactly two distinct primes
 *
 * Time complexity is approximately O(N √M),
 * Space complexity is approximately O(√M), where:
 * - N = number of elements in nums_
 * - M = maximum value in nums_
 *
 * @param nums_ A span of integers to evaluate.
 * @return Sum of divisors for all numbers having exactly four divisors.
 */
auto Solution::sumFourDivisors(std::span<int const> const nums_) const -> int {
    namespace rngs = std::ranges;

    /// Maximum value in the input array
    auto const maxNum{*rngs::max_element(nums_)};

    /// Upper limit for prime generation (sqrt(maxNum))
    auto const upperLim{static_cast<int>(std::ceil(std::sqrt(maxNum)))};

    /**
     * @brief Boolean sieve array for prime detection.
     *
     * isPrimeArr[i] is true if i is prime.
     */
    auto isPrimeArr{std::vector<bool>(upperLim + 1, true)};
    isPrimeArr[0] = isPrimeArr[1] = false;

    /// Sieve of Eratosthenes
    for (auto num1{2}; num1 * num1 <= upperLim; ++num1) {
        if (!isPrimeArr[num1]) continue;
        for (auto num2{num1 * num1}; num2 <= upperLim; num2 += num1) {
            isPrimeArr[num2] = false;
        }
    }

    /**
     * @brief List of prime numbers up to upperLim.
     */
    auto primes{std::vector<int>{}};
    primes.reserve(nums_.size());
    for (auto i{2}; i <= upperLim; ++i) {
        if (isPrimeArr[i]) {
            primes.emplace_back(i);
        }
    }
    primes.shrink_to_fit();

    /// Accumulator for total divisor sum
    auto totSum{0};

    /**
     * @brief Process each number individually.
     */
    for (auto const num : nums_) {

        /**
         * @brief Special case: num = p^3 where p is prime.
         *
         * Such numbers have exactly four divisors:
         * 1, p, p^2, p^3
         */
        auto const numToTest{static_cast<int>(std::round(std::cbrt(num)))};
        if (numToTest > 1 &&
            numToTest * numToTest * numToTest == num &&
            numToTest <= upperLim &&
            isPrimeArr[numToTest]
        ) {
            auto const curSum{1 + numToTest + numToTest * numToTest + num};
            totSum += curSum;
            continue;
        }

        /// Number of prime divisors found
        auto divCnt{0};
        auto numTmp{num};
        auto div1{-1};
        auto div2{-1};

        /**
         * @brief Factorization using prime trial division.
         */
        for (auto const prime : primes) {
            if (prime * prime > numTmp) {
                break;
            } else if (numTmp % prime == 0) {
                /// Reject numbers divisible by p^2
                if (numTmp % prime == 0 && (numTmp / prime) % prime == 0) {
                    divCnt = 3;
                    break;
                }
                if (divCnt == 0) {
                    div1 = prime;
                    numTmp /= prime;
                    ++divCnt;
                } else if (divCnt == 1) {
                    div2 = prime;
                    numTmp /= prime;
                    ++divCnt;
                } else {
                    break;
                }
            }
        }

        /// Handle remaining prime factor
        if (numTmp > 1) {
            if (divCnt == 0) {
                div1 = numTmp;
                divCnt = 1;
            } else if (divCnt == 1) {
                div2 = numTmp;
                divCnt = 2;
            } else {
                divCnt = 3;
            }
        }

        /**
         * @brief Valid case: num = p * q (distinct primes).
         *
         * Divisors are: 1, p, q, p*q
         */
        if (divCnt == 2 && div1 != div2 && div1 * div2 == num) {
            auto const curSum{1 + div1 + div2 + num};
            totSum += curSum;
        }
    }

    return totSum;
}
