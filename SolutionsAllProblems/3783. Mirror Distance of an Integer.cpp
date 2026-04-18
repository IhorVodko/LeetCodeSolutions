// problem : https://leetcode.com/problems/mirror-distance-of-an-integer/description 
// submission : https://leetcode.com/problems/mirror-distance-of-an-integer/submissions/1982033839
// solution post : https://leetcode.com/problems/mirror-distance-of-an-integer/solutions/7987151/
//    c-modern-readable-code-beats-100-runtime-tj85

// Approach : Mathematical Digit Reversal
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the input number
// complexity :  O(log(n))
// complexity : O(1)

// import std;

namespace {

// Compile-time initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    // Calculates the absolute difference between the number and its reverse.
    auto mirrorDistance(int const num_) const noexcept -> int;

private:
    // Constant representing the base 10 radix used for digit extraction.
    static auto constexpr kRadix{10};

    // Helper method to reverse the digits of the provided integer.
    inline auto Reverse(int num_) const noexcept -> int;   
};

// Main method implementation to compute the mirror distance.
auto Solution::mirrorDistance(int const num_) const noexcept -> int {
    // Reverse the input number using the helper method.
    auto const revNum{Reverse(num_)};
    auto mirrDist{std::abs(num_ - revNum)};

    return mirrDist;
}

// Helper method implementation to reverse an integer.
auto Solution::Reverse(int num_) const noexcept -> int {
    auto revNum{0};

    while(num_ > 0) {
        // Extract the quotient and the remainder (current digit).
        auto const [nextNum, digit]{std::div(num_, kRadix)};

        // Append the extracted digit to the reversed number.
        revNum = revNum * kRadix + digit;
        // Update the current number to the remaining digits.
        num_ = nextNum;
    }
    
    return revNum;
}
