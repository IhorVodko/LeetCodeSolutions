// problem : https://leetcode.com/problems/unique-3-digit-even-numbers/description
// submission : https://leetcode.com/problems/unique-3-digit-even-numbers/submissions/2138551027
// solution post : https://leetcode.com/problems/unique-3-digit-even-numbers/solutions/8515802/simplanation-simple-explanation-by-cyber-p3rt

// Approach : Combinatorics and Frequency Counting
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the count of numbers given
// Time :  O(n)
// Space : O(1)

// import std;

// #include <algorithm>
// #include <ios>
// #include <iostream>
// #include <array>
// #include <ranges>
// #include <tuple>
// #include <vector>

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

constexpr auto kRadix{10};

// Helper to evaluate if digit is present in our candidate pool
constexpr auto isDigitAvailable{[] (auto const digitAndCnt_) {
    return std::get<1>(digitAndCnt_) > 0;
}};

// Initializer to configure fast I/O before main() runs
[[maybe_unused]]
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
    static auto totalNumbers(std::vector<int> const & digits_) -> int;
};

auto Solution::totalNumbers(std::vector<int> const & digits_) -> int {
    auto cntPerDigit{std::array<int, kRadix>{}};
    // 1. Build frequency map of provided digits
    for(auto const digit: digits_) {
        ++cntPerDigit[digit];
    }

    // 2. Count distinct digits available to be used in the tens place
    auto const uniqueDigitsCnt{rs::count_if(cntPerDigit, [] (auto const cnt_) {
        return cnt_ > 0;
    })};

    // 3. Extract non-zero candidate digits for the hundreds place
    auto notZeroDigitsAvailable{
        cntPerDigit | vs::enumerate | vs::drop(1) | vs::filter(isDigitAvailable) 
    };
    // 4. Extract even candidate digits for the units place
    auto evenDigitsAvailable{
        cntPerDigit | vs::enumerate | vs::stride(2) | vs::filter(isDigitAvailable)
    };
    auto numCnt{0};

    // 5. Evaluate all valid pairs of hundreds and units candidates
    for(auto const [firstDigit, firstDigitCnt]: notZeroDigitsAvailable) {
        for(auto const [thirdDigit, thirdDigitCnt] : evenDigitsAvailable) {
            if(firstDigit == thirdDigit) {
                // Ensure sufficient copies exist to populate both outer positions
                if(firstDigitCnt <= 1) {
                    continue;
                }

                // 6. Add permutations for identical outer digits accounting for exhaustion
                numCnt += uniqueDigitsCnt - (firstDigitCnt == 2 ? 1 : 0);
            } else {
                // 7. Add permutations for distinct outer digits accounting for exhaustion
                numCnt +=
                    uniqueDigitsCnt -
                    (firstDigitCnt == 1 ? 1 : 0) -
                    (thirdDigitCnt == 1 ? 1 : 0)
                ;
            }
        }
    } 

    return numCnt;
}
