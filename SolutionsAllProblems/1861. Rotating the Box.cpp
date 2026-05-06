// problem : https://leetcode.com/problems/rotating-the-box/description
// submission : https://leetcode.com/problems/rotating-the-box/submissions/1996627594
// solution post : https://leetcode.com/problems/rotating-the-box/solutions/8153830/c-modern-readable-code-beats-100-runtime-rlq8

// Approach : Two-Pass Counting and Mapping
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' by 'm' be the grid size
// complexity :  O(n * m)
// complexity : O(1)

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
    using arr2d = std::vector<std::vector<char>>;

    [[nodiscard]]
    auto rotateTheBox(arr2d const & grid_) const -> arr2d;

private:
    static auto constexpr kStone{'#'};
    static auto constexpr kObstacle{'*'};    
    static auto constexpr kEmpty{'.'};
};

auto Solution::rotateTheBox(arr2d const & grid_) const -> arr2d {
    namespace vs = std::views;

    auto const rSz{std::ssize(grid_)};
    auto const cSz{std::ssize(grid_.front())};
    auto rotatedGrid{arr2d(cSz, std::vector(rSz, kEmpty))};

    // Place collected stones above the most recent obstacle or floor
    auto const PlaceStones{
        [&] (auto & stoneCnt_, auto r_, auto const c_) {
            while(stoneCnt_-- > 0) {
                rotatedGrid[r_--][c_] = kStone;
            }
            stoneCnt_ = 0;
    }};

    for(auto const r: vs::iota(0, rSz)) {
        auto stoneCnt{0};
        auto const rotatedC{rSz - r - 1};

        for(auto const c: vs::iota(0, cSz)) {
            if( auto const cell{grid_[r][c]};
                cell == kStone
            ) {
                ++stoneCnt;
            } else if(cell == kObstacle) {
                rotatedGrid[c][rotatedC] = kObstacle;
                PlaceStones(stoneCnt, c - 1, rotatedC);
            }
        }

        PlaceStones(stoneCnt, cSz - 1, rotatedC);
    }

    return rotatedGrid;
}
