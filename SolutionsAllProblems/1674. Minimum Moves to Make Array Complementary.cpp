// problem : https://leetcode.com/problems/minimum-moves-to-make-array-complementary/description
// submission : https://leetcode.com/problems/minimum-moves-to-make-array-complementary/submissions/2002342346
// solution post : https://leetcode.com/problems/minimum-moves-to-make-array-complementary/
//    solutions/8216816/c-modern-readable-code-beats-100-runtime-7o4c

// Approach :
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the count of numbers
// 'm' - given upper limit for the numbers
// complexity :  O(n + m)
// complexity : O(m)

// import std;

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

class Solution final {
public:
    [[nodiscard]]
    auto minMoves(
        std::vector<int> const & nums_,
        int const numUpLim_
    ) const -> int;

private:
    static auto constexpr kMinSum{2};
};

auto Solution::minMoves(
    std::vector<int> const & nums_,
    int const numUpLim_
) const -> int {
    namespace vs = std::views;

    auto const numsSz{std::ssize(nums_)};

    // Early pre-check for the best-case scenario
    auto isComplementary{true};
    for(auto const sum{nums_[0] + nums_[numsSz - 1]};
        auto const j: vs::iota(1, numsSz / 2)
    ) {
        if (nums_[j] + nums_[numsSz - j - 1] != sum) {
            isComplementary = false;
            break;
        }
    }
    if(isComplementary){
        return 0;
    }

    // Difference array to track the change in moves at specific sum boundaries.
    auto moveCntDiffArr{std::vector<int>(2 * numUpLim_ + 2)};
    for(auto const j: vs::iota(0, numsSz / 2)) {
        auto const num1{nums_[j]};
        auto const num2{nums_[numsSz - j - 1]};
        auto const sum{num1 + num2};
        auto const minNum{std::min(num1, num2)};
        auto const maxNum{std::max(num1, num2)};

        // Base case: it takes 2 moves to reach any sum starting from kMinSum.
        moveCntDiffArr[kMinSum] += 2;
        // From minNum + 1, we only need 1 move (change the larger number).
        moveCntDiffArr[minNum + 1] -= 1;
        // At the exact sum of the pair, 0 moves are needed.
        moveCntDiffArr[sum] -= 1;
        // Past the exact sum, we need 1 move again (change the smaller number).
        moveCntDiffArr[sum + 1] += 1;
        // Past maxNum + upLim_, 1 move is not enough; 2 moves are required.
        moveCntDiffArr[maxNum + numUpLim_ + 1] += 1;
    }

    auto minMoveCnt{static_cast<int>(numsSz)};
    for(auto currMoveCnt{0};
        auto const sum: vs::iota(kMinSum, 2 * numUpLim_ + 1)
    ) {
        // Accumulates interval differences to derive exact moves for the current sum
        currMoveCnt += moveCntDiffArr[sum];
        minMoveCnt = std::min(minMoveCnt, currMoveCnt);
    }

    return minMoveCnt;
}
