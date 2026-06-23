// problem : https://leetcode.com/problems/number-of-zigzag-arrays-i/description
// submission : https://leetcode.com/problems/number-of-zigzag-arrays-i/submissions/2043795203
// solution post : https://leetcode.com/problems/number-of-zigzag-arrays-i/solutions/8354613/c-modern-readable-code-beats-100-runtime-u43o

// Approach : Prefix Sum Dynamic Programming
// Runtime : 89 ms, beats 100.00 %


// Complexity
// let 'n' be the zigzag array length
// 'm' - start of the allowed value range
// 'k' - end of the allowed value range
// Time :  O(n * (k - m))
// Space : O(k - m)

// import std;

class Solution final {
public:
    // Calculates valid zigzag permutations.
    [[nodiscard]]
    static auto zigZagArrays(
        int const arrLen_,
        int const numLowLim_,
        int const numUpLim_
    ) -> int;
};

auto Solution::zigZagArrays(
    int const arrLen_,
    int const numLowLim_,
    int const numUpLim_
) -> int {
    namespace vs = std::views;
    namespace rs = std::ranges;

    using ll = long long;

    // Modulo constraint defined by the problem bounds.
    auto constexpr kMod{1'000'000'007};

    // Total candidate numbers available within the allowed inclusive boundaries.
    auto const len{numUpLim_ - numLowLim_ + 1};

    // Guard clauses to handle edge cases where dynamic programming is unnecessary.
    if(len <= 0) return 0;
    if(arrLen_ == 1) return len;

    // State array tracking combinations ending at each respective relative value.
    // Seeded with 1s since an array of length 1 has exactly one valid state.
    auto dp{std::vector<int>(len, 1)};

    // Inline custom addition to bypass expensive modulo division on every step.
    auto constexpr ModAdd{[] (auto num1_, auto const num2_) {
        num1_ += num2_;
        return num1_ >= kMod ? num1_ - kMod : num1_; 
    }};

    // Expand combinations iteratively for each subsequent array position.
    for(auto const j: vs::iota(2, arrLen_ + 1)) {
        if(j % 2 == 0) {
            // Even indices demand an ascending step.
            // Prefix sum aggregates valid prior states that are strictly smaller.
            std::exclusive_scan(dp.begin(), dp.end(), dp.begin(), 0, ModAdd);
        } else {
            // Odd indices demand a descending step.
            // Suffix sum aggregates valid prior states that are strictly larger.
            std::exclusive_scan(dp.rbegin(), dp.rend(), dp.rbegin(), 0, ModAdd);
        }
    }

    // Aggregate all valid sequences of the target length for a single direction.
    auto arrTot{rs::fold_left(dp, 0, ModAdd)};

    // Multiply by 2 to mirror the result for both valid starting directions.
    return static_cast<int>((arrTot * 2ll) % kMod);
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
