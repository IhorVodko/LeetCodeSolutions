// problem : https://leetcode.com/problems/find-the-safest-path-in-a-grid/description/
// submission : https://leetcode.com/problems/find-the-safest-path-in-a-grid/submissions/2052374812
// solution post : https://leetcode.com/problems/find-the-safest-path-in-a-grid/solutions/8369740/
//    modern-readable-code-optimal-time-comple-epve

// Approach : Multi-Source BFS with Dijkstra's Algorithm (Max-Heap)
// Runtime : 330 ms, beats 80.96 %

// Complexity
// let 'n' be the dimension of the grid
// Time :  O(n^2 * log(n))
// Space : O(n^2)

// import std;

namespace {

template <typename T_>
using gridT = std::vector<std::vector<T_>>;
using posT = std::pair<int, int>;

// State for max-heap prioritizing higher safeness
struct PathState final {
    auto operator<(PathState const & other_) const -> bool {
        return mSafeness < other_.mSafeness;
    }

    int mSafeness{};
    int mR{};
    int mC{};
};

static auto constexpr kOffsets{std::to_array<posT>({
    {-1, 0}, {0, 1}, {1, 0}, {0, -1}
})};
static auto constexpr kIsThief{1};
static auto constexpr kUnvisited{-1};

// Generates valid adjacent grid coordinates lazily
static auto constexpr GetNextPositions{[] (
    auto const r_,
    auto const c_,
    auto const rcTot_
) {
    namespace vs = std::views;

    return 
        kOffsets |
        vs::transform([=] (auto const & offset_) {
            return std::pair{r_ + offset_.first, c_ + offset_.second};
        }) |
        vs::filter([=](auto const & nextPos_) {
            auto const [nextR, nextC]{nextPos_};
            return 0 <= nextR && nextR < rcTot_ && 0 <= nextC && nextC < rcTot_;
    });
}};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    static auto maximumSafenessFactor(gridT<int> const & thiefGrid_) -> int;

private:
    [[nodiscard]]
    static auto ComputeSafenessGrid(
        gridT<int> const & thiefGrid_
    ) -> gridT<int>;
};

auto Solution::maximumSafenessFactor(gridT<int> const & thiefGrid_) -> int {
    namespace vs = std::views;

    // Early exit if start or end is occupied
    if(thiefGrid_.front().front() == kIsThief || thiefGrid_.back().back() == kIsThief) {
        return 0;
    }

    // Precompute minimum distances to nearest thieves
    auto const safenessGrid{ComputeSafenessGrid(thiefGrid_)};

    auto const rcTot{std::ssize(thiefGrid_)};
    // Max-heap to explore safest paths first
    auto maxPq{std::priority_queue<PathState>{}};
    maxPq.emplace(safenessGrid[0][0], 0, 0);

    auto isPosVisited{gridT<bool>(rcTot, std::vector<bool>(rcTot))};
    isPosVisited[0][0] = true;

    while(!maxPq.empty()) {
        auto const [currSafeness, currR, currC]{maxPq.top()};
        maxPq.pop();

        // Target reached
        if(currR == rcTot - 1 && currC == rcTot - 1) {
            return currSafeness;
        }

        for(auto const [nextR, nextC]: GetNextPositions(currR, currC, rcTot)) {
            if(isPosVisited[nextR][nextC]) {
                continue;
            }
            isPosVisited[nextR][nextC] = true;
            // Safeness is constrained by the path's weakest link
            auto const pathSafeness{std::min(currSafeness, safenessGrid[nextR][nextC])};
            maxPq.emplace(pathSafeness, nextR, nextC);
        }
    }

    return 0;
}

auto Solution::ComputeSafenessGrid(
    gridT<int> const & thiefGrid_
) -> gridT<int> {
    namespace vs = std::views;

    auto const rcTot{std::ssize(thiefGrid_)};
    auto safenessGrid{gridT<int>(rcTot, std::vector(rcTot, kUnvisited))};
    auto bfsQ{std::queue<posT>{}};
    auto const allPositions{vs::cartesian_product(vs::iota(0, rcTot), vs::iota(0, rcTot))};

    // Initialize multi-source BFS with all thief locations
    for(auto const [r, c]: allPositions) {
        if(thiefGrid_[r][c] != kIsThief) {
            continue;
        }
        safenessGrid[r][c] = 0;
        bfsQ.emplace(r, c);
    }

    // Calculate shortest distance from any thief to each cell
    while(!bfsQ.empty()) {
        auto const [currR, currC]{bfsQ.front()};
        bfsQ.pop();

        for(auto const [nextR, nextC]: GetNextPositions(currR, currC, rcTot)) {
            if(safenessGrid[nextR][nextC] != kUnvisited) {
                continue;
            }
            safenessGrid[nextR][nextC] = safenessGrid[currR][currC] + 1;
            bfsQ.emplace(nextR, nextC);
        }
    }

    return safenessGrid;
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
