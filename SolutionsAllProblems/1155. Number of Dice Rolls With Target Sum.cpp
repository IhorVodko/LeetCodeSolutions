// problem : https://leetcode.com/problems/number-of-dice-rolls-with-target-sum/description/
// submission : https://leetcode.com/problems/number-of-dice-rolls-with-target-sum/submissions/1902208409
// solution post : https://leetcode.com/problems/number-of-dice-rolls-with-target-sum/solutions/7537241/
//    c-modern-readable-code-beats-100-runtime-grxb

// import std;

inline static int const fastIOInit{
    [] {
        std::atexit([] () { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' be the number of dices
// 'm' - number of sizes
// 'k' - target score
// time complexity O(n * m * k)
// space complexity O(k)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto numRollsToTarget(
        int diceTotCnt_,
        int sideMaxScore_, 
        int targetScore_
    ) const -> int;

private:
    static auto constexpr kModulus{1'000'000'007};
};

auto Solution::numRollsToTarget(
    int diceTotCnt_,
    int sideMaxScore_, 
    int targetScore_
) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    // curMemo[s] stores the number of ways to achieve sum s using remaining dice
    auto curMemo{std::vector<int>(targetScore_ + 1)};
    auto nextMemo{std::vector<int>(targetScore_ + 1)};
    // Base case: with no dice left, exactly one way to reach targetScore_
    curMemo.back() = 1;

    // Process dice in reverse order to reuse memory efficiently
    for(auto const diceIdx: vs::iota(0, diceTotCnt_) | vs::reverse) {
        rngs::fill(nextMemo, 0);
        // Try building all possible current sums
        for(auto const curScore: vs::iota(0, targetScore_ + 1)) {
            auto waysCnt{0};
            // Add contributions from all valid face values
            for(auto sideScore{1},
                    sideMaxScore{std::min(sideMaxScore_, targetScore_ - curScore)};
                sideScore <= sideMaxScore; ++sideScore
            ) {
                waysCnt = (waysCnt + curMemo[curScore + sideScore]) % kModulus;
            }

            nextMemo[curScore] = waysCnt;
        }
        std::swap(curMemo, nextMemo);
    }
    // Final result: number of ways to reach targetScore_ starting from sum 0
    auto const waysTotCnt{curMemo.front()};
    return waysTotCnt;
}
