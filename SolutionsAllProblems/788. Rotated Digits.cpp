// problem : https://leetcode.com/problems/rotated-digits/description/
// submission : https://leetcode.com/problems/rotated-digits/submissions/1994174536
// solution post : https://leetcode.com/problems/rotated-digits/solutions/8133640/c-modern-readable-code-beats-100-runtime-f0pu

// Approach : Brute Force with Digit Extraction
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the given number
// complexity :  O(n * log(n))
// complexity : O(n)

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
    // Rotated digits counter function declaration
    [[nodiscard]]
    auto rotatedDigits(auto const num_) const -> int;

private:
    // Checks if a single number is valid according to the rules
    [[nodiscard]] 
    auto IsNumGood(int num_) const -> bool;
};

auto Solution::rotatedDigits(auto const num_) const -> int {
    namespace vs = std::views;

    auto goodNumCnt{0};

    for(auto const num: vs::iota(1, num_ + 1)) {
        if(IsNumGood(num)) {
            ++goodNumCnt;
        }
    }

    return goodNumCnt;
}

auto Solution::IsNumGood(int num_) const -> bool {
    // Flag to track if the number contains a rotation-changing digit
    auto hasDiffDigit{false};

    // Loop through each digit of the number from right to left
    for(auto num{num_}; num > 0; num /= 10) {
        // Extract the rightmost digit of the current number
        auto digit{num % 10};

        // Check for invalid digits that break the rotation rules
        if(digit == 3 || digit == 4 || digit == 7) {
            return false;
        }

        // Check for valid digits that change their value upon rotation
        if(digit == 2 || digit == 5 || digit == 6 || digit == 9) {
            hasDiffDigit = true;
        } 
    }

    // Return true only if the number is valid and has changed its value
    return hasDiffDigit;
}
