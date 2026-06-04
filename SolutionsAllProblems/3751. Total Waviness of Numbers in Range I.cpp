// problem : https://leetcode.com/problems/total-waviness-of-numbers-in-range-i/description 
// submission : https://leetcode.com/problems/total-waviness-of-numbers-in-range-i/submissions/2022315373
// solution post : https://leetcode.com/problems/total-waviness-of-numbers-in-range-i/solutions/8313517/
//    c-modern-readable-code-optimal-time-comp-8fyr

// Approach : Sequential Range Evaluation with Local Extrema Detection
// Runtime : 5 ms, beats 90.30 %

// Complexity
// let 'n' be the number of numbers in the range
// 'M' - upper bound of the range
// complexity :  O(n * log(M))
// complexity : O(1)

// import std;

class Solution final {
public:
    static auto totalWaviness(
        int const numLoLim_,
        int const numUpLim_
    ) -> int;

private:
    static auto constexpr kFirstValidNum{101};
    static auto constexpr kRadix{10};
};

auto Solution::totalWaviness(
    int const numLoLim_,
    int const numUpLim_
) -> int {
    namespace vs = std::views;

    // Minimum 3 digits required for wave triplet.
    if(numUpLim_ < kFirstValidNum) {
        return 0;
    }
    
    // Clamp lower bound for valid triplet sizes.
    auto const optimalNumLowLim{std::max(numLoLim_, kFirstValidNum)};

    // Evaluates wave-like digit triplets in integer.
    auto const CntWaviness{[] (int const num_) -> int {
        auto cnt{0};
        auto [newNum1, rDigit]{std::div(num_, kRadix)};
        auto [newNum2, midDigit]{std::div(newNum1, kRadix)};
        
        // Scan remaining digits leftwards.
        while(newNum2 > 0) {
            auto const [newNum3, lDigit]{std::div(newNum2, kRadix)};
            
            // Detect local extrema defining wave.
            if((lDigit > midDigit && midDigit < rDigit) ||
               (lDigit < midDigit && midDigit > rDigit)) {
                ++cnt;
            }
            
            rDigit = midDigit;
            midDigit = lDigit;
            newNum2 = newNum3;
        }

        return cnt;
    }};

    // Define valid evaluation sequence bounds.
    auto const numRng{vs::iota(optimalNumLowLim, numUpLim_ + 1)};

    // Aggregate wave occurrences across sequence.
    return std::transform_reduce(
        numRng.begin(), numRng.end(),
        0,
        std::plus{},
        CntWaviness
    );
}

namespace {

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace
