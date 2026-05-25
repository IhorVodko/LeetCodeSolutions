// problem : https://leetcode.com/problems/jump-game-v/description/
// submission : https://leetcode.com/problems/jump-game-v/submissions/2012724787
// solution post : https://leetcode.com/problems/jump-game-v/solutions/8293015/c-modern-readable-code-beats-100-runtime-crf0

// Approach : Dynamic Programming with Monotonic Stack
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the length of the array of numbers
// complexity :  O(n)
// complexity : O(n)

// import std;

class Solution final {
public:
    [[nodiscard]]
    static auto maxJumps(
        std::vector<int> const & nums_,
        int const distUpLim_
    ) -> int;
};

auto Solution::maxJumps(
    std::vector<int> const & nums_,
    int const distUpLim_
) -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto const numsSz{static_cast<int>(nums_.size())};
    // Base DP state: staying at the initial index counts as 1 jump
    auto maxJumpCnts{std::vector<int>(numsSz, 1)};
    // Tracks indices of strictly decreasing heights to find taller neighbors
    auto decrStck{std::vector<int>{}};
    decrStck.reserve(numsSz);

    for(auto const currIdx: vs::iota(0, numsSz + 1)) {
        // Valley found; process jumps from taller boundaries to this valley
        while(!decrStck.empty() &&
            (currIdx == numsSz || nums_[decrStck.back()] < nums_[currIdx])
        ) {
            auto const num{nums_[decrStck.back()]};
            // Group contiguous equal heights to prevent jumping between them
            auto const rIt{rngs::find_if_not(
                decrStck.crbegin(), decrStck.crend(),
                [&] (auto const idx_) { return nums_[idx_] == num; }
            )};
            auto const firstEqual{rIt.base()};
            auto const hasLeft{firstEqual != decrStck.cbegin()};
            // Identify the nearest taller height on the left
            auto const leftBound{hasLeft ? *(firstEqual - 1) : -1};

            // Update max jumps from valid left and right bounding peaks
            for(auto const subIdx: rngs::subrange(firstEqual, decrStck.cend())) {
                if(currIdx < numsSz && currIdx - subIdx <= distUpLim_) {
                    auto & maxJumpCnt{maxJumpCnts[currIdx]};
                    maxJumpCnt = std::max(maxJumpCnt, maxJumpCnts[subIdx] + 1);
                }
                if(hasLeft && subIdx - leftBound <= distUpLim_) {
                    auto & maxJmpCnt{maxJumpCnts[leftBound]};
                    maxJmpCnt = std::max(maxJmpCnt, maxJumpCnts[subIdx] + 1);
                }
            }

            decrStck.erase(firstEqual, decrStck.end());
        }

        if(currIdx < numsSz) {
            decrStck.emplace_back(currIdx);
        }
    }

    return rngs::max(maxJumpCnts);
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
