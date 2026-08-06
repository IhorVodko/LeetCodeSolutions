// problem : https://leetcode.com/problems/smallest-divisible-digit-product-i/description
// submission : https://leetcode.com/problems/smallest-divisible-digit-product-i/submissions/2097131401
// solution post : https://leetcode.com/problems/smallest-divisible-digit-product-i/solutions/8445869/
//    simplanation-simple-explanation-by-cyber-951o

// Approach : O(1) Mathematical GCD Factorization
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// Time :  O(1)
// Space : O(1)

// import std;

namespace {

auto constexpr kRadix{10};
auto constexpr kMaxDigit{9};
auto constexpr kMaxNum{100};

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace 

class Solution final {
public:
    [[nodiscard]]
    static auto smallestNumber(
        int num_, 
        int const div_
    ) -> int;
};

auto Solution::smallestNumber(
    int num_, 
    int const div_
) -> int {
    // Process single-digit numbers
    if( auto const quot{num_ / kRadix}; 
        quot == 0
    ) {
        // Round up to the next valid multiple
        if( auto const rem{num_ % div_};
            rem != 0
        ) {
            num_ += div_ - rem;
        }

        // Cap at 10 since a zero product is universally divisible
        return std::min(num_, kRadix);
    // Process two-digit numbers
    } else if(quot / kRadix == 0) {
        auto [tens, units]{std::div(num_, kRadix)};

        // Early return for zero products
        if(units == 0) {
            return num_;
        }

        // Isolate the missing factor required for divisibility
        auto const step{div_ / std::gcd(tens, div_)};
        // Snap units to the next multiple of the missing factor
        auto const nextUnits{(units + step - 1) / step * step};

        if(nextUnits <= kMaxDigit) {
            return (tens * kRadix) + nextUnits;
        }

        // Rollover to the next decade yields a zero product
        return (tens + 1) * kRadix;
    }

    // Default bound
    return kMaxNum;
}
