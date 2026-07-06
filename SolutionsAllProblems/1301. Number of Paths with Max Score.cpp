// problem : https://leetcode.com/problems/number-of-paths-with-max-score/description
// submission : https://leetcode.com/problems/number-of-paths-with-max-score/submissions/2058207235
// solution post : https://leetcode.com/problems/number-of-paths-with-max-score/solutions/8380141/
//    modern-readable-code-optimal-time-comple-u7x7

// Approach : 2D Dynamic Programming (Bottom-Up Tabulation)
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the side length of the square board
// Time :  O(n^2)
// Space : O(n^2)

// import std;

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

template <typename T_>
using vec2T = std::vector<std::vector<T_>>;

auto constexpr kMod{1'000'000'007};
auto constexpr kBlocked{'X'};
auto constexpr kStart{'S'};
auto constexpr kEnd{'E'};
auto constexpr kChrDigitFirst{'0'};

struct PathState final {
    int score{-1};
    int wayCnt{};
};

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    }()
};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    static auto pathsWithMaxScore(
        std::vector<std::string> const & board_
    ) -> std::vector<int>;
};

auto Solution::pathsWithMaxScore(
    std::vector<std::string> const & board_
) -> std::vector<int> {
    auto const rcTot{std::ssize(board_)};
    auto dp{vec2T<PathState>(rcTot, std::vector<PathState>(rcTot))};
    auto const lastRC{rcTot - 1};

    // Base case: the starting position contributes no score and has one valid
    // path.
    dp[lastRC][lastRC] = {0, 1};

    for (auto const currR : vs::iota(0, rcTot) | vs::reverse) {
        for (auto const currC : vs::iota(0, rcTot) | vs::reverse) {
            if ((currR == lastRC && currC == lastRC) ||
                board_[currR][currC] == kBlocked
            ) {
                continue;
            }

            auto bestState{PathState{}};
            auto & [bestScore, bestWayCnt]{bestState};

            // Evaluates a transition to one of the three reachable successor
            // cells.
            auto const relax{[&] (int const nextR_, int const nextC_) {
                if (nextR_ >= rcTot || nextC_ >= rcTot) {
                    return;
                }

                auto const & nextState{dp[nextR_][nextC_]};
                auto const [nextScore, nextWayCnt]{nextState};

                if (nextWayCnt > 0 && nextScore > bestScore) {
                    bestState = nextState;
                } else if (nextScore == bestScore) {
                    bestWayCnt += nextWayCnt;

                    if (bestWayCnt >= kMod) {
                        bestWayCnt -= kMod;
                    }
                }
            }};

            // Explore all possible moves towards the starting position.
            relax(currR + 1, currC);
            relax(currR, currC + 1);
            relax(currR + 1, currC + 1);

            // Cells unreachable from the starting position remain invalid.
            if (bestWayCnt == 0) {
                continue;
            }

            // Only digit cells contribute to the accumulated score.
            if (board_[currR][currC] != kEnd) {
                bestScore += board_[currR][currC] - kChrDigitFirst;
            }

            dp[currR][currC] = bestState;
        }
    }

    auto const & bestPathState{dp[0][0]};

    return {bestPathState.wayCnt == 0 ? 0 : bestPathState.score, bestPathState.wayCnt};
}
