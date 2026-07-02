// problem : https://leetcode.com/problems/find-a-safe-walk-through-a-grid/description
// submission : https://leetcode.com/problems/find-a-safe-walk-through-a-grid/submissions/2053571029
// solution post : https://leetcode.com/problems/find-a-safe-walk-through-a-grid/solutions/8371943/
//    modern-readable-code-optimal-time-comple-h0bp

// Approach : 0-1 Breadth-First Search (0-1 BFS)
// Runtime : 3 ms, beats 97.84 %

// Complexity
// let 'n' by 'm' be grid size
// Time :  O(n * m)
// Space : O(n * m)

// import std;

namespace {

using gridT = std::vector<std::vector<int>>;
using posT = std::pair<int, int>;

auto constexpr kIntMax{std::numeric_limits<int>::max()};
auto constexpr kOffsets{std::to_array<posT>({
    {-1, 0}, {0, 1}, {1, 0}, {0, -1}
})};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    static auto findSafeWalk(
        gridT const & grid_,
        int const health_
    ) -> bool;
};

auto Solution::findSafeWalk(
    gridT const & grid_,
    int const health_
) -> bool {
    namespace rs = std::ranges;
    namespace vs = std::views;

    if (grid_[0][0] >= health_) {
        return false;
    }

    auto const rTot{std::ssize(grid_)};
    auto const destR{rTot - 1};
    auto const cTot{std::ssize(grid_.front())};
    auto const destC{cTot - 1};

    // Track minimum damage taken to reach each cell
    auto minDmg{gridT(rTot, std::vector(cTot, kIntMax))};
    minDmg[0][0] = grid_[0][0];

    // 0-1 BFS queue
    auto dq{std::deque<posT>{}};
    dq.emplace_front(0, 0);

    while(!dq.empty()) {
        auto const [currR, currC]{dq.front()};
        dq.pop_front();

        // First pop of destination guarantees minimum damage path
        if(currR == destR && currC == destC) {
            return true;
        }

        // Lazy evaluation of valid adjacent cells
        auto validMoves{
            kOffsets |
            vs::transform([&] (auto const & offset_) {
                auto const [rOff, cOff]{offset_};
                return posT{currR + rOff, currC + cOff};
            }) |
            vs::filter([&] (auto const & nextPos_) {
                auto const [nextR, nextC]{nextPos_};
                if(nextR < 0 || rTot <= nextR || nextC < 0 || cTot <= nextC) {
                    return false;
                }
                auto const nextDmg{minDmg[currR][currC] + grid_[nextR][nextC]};
                // Prune paths that exceed health or are suboptimal
                return nextDmg < health_ && nextDmg < minDmg[nextR][nextC];
            })
        };

        // process current cell heighbours
        rs::for_each(validMoves, [&] (auto const & pos_) {
            auto const [nextR, nextC]{pos_};
            auto const nextGridVal{grid_[nextR][nextC]};

            minDmg[nextR][nextC] = minDmg[currR][currC] + nextGridVal;

            // 0-weight moves prioritized over 1-weight moves
            if(nextGridVal == 0) {
                dq.emplace_front(nextR, nextC);
            } else {
                dq.emplace_back(nextR, nextC);
            }
        });
    }  

    return false;
}

namespace {

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace
