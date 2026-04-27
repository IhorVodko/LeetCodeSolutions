// problem : https://leetcode.com/problems/check-if-there-is-a-valid-path-in-a-grid/description/
// submission : https://leetcode.com/problems/check-if-there-is-a-valid-path-in-a-grid/submissions/1989728893
// solution post : https://leetcode.com/problems/check-if-there-is-a-valid-path-in-a-grid/solutions/8105456/
//    c-modern-readable-code-beats-100-runtime-45sx

// Approach : State Machine Simulation (Deterministic Finite Automaton)
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' by 'm' be the grid size
// complexity :  O(n * m)
// complexity : O(n * m)

// import std;

namespace {

// Compile-time initializer to configure fast I/O before main() runs
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
    template<typename T_>
    using mxT = std::vector<std::vector<T_>>;

    // Main function to check for a valid path
    [[nodiscard]]
    auto hasValidPath(mxT<int> const & grid_) const -> bool;

private:
    // Enum for directions (state tracking)
    enum class Dir {n, e, s, w, cnt, invalid};
    // Maximum possible length of the grid side
    static auto constexpr kMaxGridSide{300};
    // Maximum iterations to prevent infinite loops
    static auto constexpr kMaxIter{kMaxGridSide * kMaxGridSide};
    // Array mapping directions to row and col offsets
    static auto constexpr kOffsets{
        std::array<std::pair<int, int>, std::to_underlying(Dir::cnt)>{{
            {-1, 0}, {0, 1}, {1, 0}, {0, -1}
    }}};
    // Total number of street piece types
    static auto constexpr kStCnt{6};
    // Transition table mapping outgoing dir per street type and incoming dir
    static auto constexpr kNextStTransitions{
        std::array<std::array<Dir, std::to_underlying(Dir::cnt)>, kStCnt>{{
        {{Dir::invalid, Dir::e,         Dir::invalid,   Dir::w      }},
        {{Dir::n,       Dir::invalid,   Dir::s,         Dir::invalid}},
        {{Dir::w,       Dir::s,         Dir::invalid,   Dir::invalid}},
        {{Dir::e,       Dir::invalid,   Dir::invalid,   Dir::s      }},
        {{Dir::invalid, Dir::n,         Dir::w,         Dir::invalid}},
        {{Dir::invalid, Dir::invalid,   Dir::e,         Dir::n      }}
    }}};

    // Helper function to simulate traversal starting in the given direction
    [[nodiscard]]
    inline auto Traverse(
        Dir const dir_,
        mxT<int> const & grid_
    ) const -> bool;
};

auto Solution::hasValidPath(mxT<int> const & grid_) const -> bool {
    using enum Dir;

    auto const rSz{std::ssize(grid_)};
    auto const cSz{std::ssize(grid_.front())};

    // If grid is 1x1, the path is trivially valid
    if (rSz == 1 && cSz == 1) {
        return true;
    }

    // Switch based on the starting cell street type
    switch(grid_.front().front()) {
        case 1 :
        case 6 :
            // Initially direct us east
            return Traverse(e, grid_);
        case 2 :
        case 3 :
            // Initially direct us south
            return Traverse(s, grid_);
        case 4 :
            // Can branch south or east
            return Traverse(s, grid_) || Traverse(e, grid_);
        case 5 :
            // No valid starting direction
            return false;
    }

    // Default return for unsupported cases
    return false;
}

auto Solution::Traverse(
    Dir const dir_,
    mxT<int> const & grid_
) const -> bool {
    using enum Dir;

    auto const rSz{std::ssize(grid_)};
    auto const cSz{std::ssize(grid_.front())};
    auto isVisited{mxT<bool>(rSz, std::vector(cSz, false))};
    auto dir{dir_};
    auto currR{0};
    auto currC{0};
    auto nextR{-1};
    auto nextC{-1};
    // Counter to restrict max iterations, a safety net
    auto iterCnt{0};

    // Loop continuously to trace the path
    while(true && iterCnt++ <= kMaxIter) {
        // Return true if the target cell is reached
        if(currR == rSz - 1 && currC == cSz - 1) {
            return true;
        }

        isVisited[currR][currC] = true;

        // Get row and col offsets for current direction
        auto const [offsetR, offsetC]{kOffsets[std::to_underlying(dir)]};

        nextR = currR + offsetR;
        nextC = currC + offsetC;

        // Check for out-of-bounds or already visited cells (avoid cycle)
        if(nextR < 0 || nextR >= rSz || nextC < 0 || nextC >= cSz ||
            isVisited[nextR][nextC]
        ) {
            return false;
        }

        auto const nextSt{grid_[nextR][nextC]};

        // Update direction based on transition table
        dir = kNextStTransitions[nextSt - 1][std::to_underlying(dir)];

        // If the transition is invalid, the path fails
        if(dir == invalid) {
            return false;
        }

        currR = nextR;
        currC = nextC;
    }

    // Fallback return, though conceptually unreachable
    return false;  
}
