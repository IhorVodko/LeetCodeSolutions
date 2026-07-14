// problem : https://leetcode.com/problems/find-the-number-of-subsequences-with-equal-gcd/description
// submission : https://leetcode.com/problems/find-the-number-of-subsequences-with-equal-gcd/submissions/2067738185
// solution post : https://leetcode.com/problems/find-the-number-of-subsequences-with-equal-gcd/solutions/8397422/
//    modern-readable-code-optimal-time-comple-pimp

// Approach : Dynamic Programming with State Space Flattening and Precomputation
// Runtime : 83 ms, beats 92.17 %

// Complexity analysis
// let 'n' be the count of given numbers
// 'm' - maximum given value
// Time :  O(n * m^2)
// Space : O(m^2)

// import std;

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

auto constexpr kMod{1'000'000'007};
auto constexpr kMaxNum{200};

// Modulo addition helper.
auto constexpr addMod{[] (int lhs_, int const rhs_) {
    lhs_ += rhs_;
    return lhs_ >= kMod ? lhs_ - kMod : lhs_;
}};

// Precompute GCDs to avoid recalculation in DP loop.
auto const kGcdTable{[] {
    auto table{std::array<std::array<int, kMaxNum + 1>, kMaxNum + 1>{}};

    for(auto const j1: vs::iota(0, kMaxNum + 1)) {
        for(auto const j2: vs::iota(0, kMaxNum + 1)) {
            if(j1 == 0) {
                table[j1][j2] = j2;
            } else if (j2 == 0) {
                table[j1][j2] = j1;
            } else {
                table[j1][j2] = std::gcd(j1, j2);
            }
        }
    }

    return table;
}()};

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
    static auto subsequencePairCount(std::vector<int> const & nums_) -> int;
};

auto Solution::subsequencePairCount(std::vector<int> const & nums_) -> int {
    auto const maxVal{rs::max(nums_)};
    auto const stride{maxVal + 1};
    // Flattened 2D state size.
    auto const totStates{stride * stride};

    auto dp{std::vector<int>(totStates)};
    auto nextDp{std::vector<int>(totStates)};

    // Base case: both subsequences are empty (gcd 0).
    dp[0] = 1;

    for(auto const num: nums_) {
        // Option 1: skip the current number. Carry over states where num is skipped.
        rs::copy(dp, nextDp.begin());

        for(auto const [idx, cnt]: vs::enumerate(dp)) {
            if(cnt == 0) {
                continue;
            }

            auto const gcd1{static_cast<int>(idx) / stride};
            auto const gcd2{static_cast<int>(idx) % stride};

            // Option 2: Append current number to the first subsequence
            auto const nextGcd1{kGcdTable[gcd1][num]};
            auto const idx1{nextGcd1 * stride + gcd2};
            nextDp[idx1] = addMod(nextDp[idx1], cnt);

            // Option 3: Append current number to the second subsequence
            auto const nextGcd2{kGcdTable[gcd2][num]};
            auto const idx2{gcd1 * stride + nextGcd2};
            nextDp[idx2] = addMod(nextDp[idx2], cnt);
        }

        dp.swap(nextDp);
    }

    // Sum states where both have the same non-zero GCD.
    return rs::fold_left(
        vs::iota(1, stride) |
            vs::transform([&] (auto const gcd_) { return dp[gcd_ * stride + gcd_]; }),
        0,
        addMod
    );
}
