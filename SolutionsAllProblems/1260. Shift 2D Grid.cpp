// problem : https://leetcode.com/problems/shift-2d-grid/description
// submission : https://leetcode.com/problems/shift-2d-grid/submissions/2074570419
// solution post : https://leetcode.com/problems/shift-2d-grid/solutions/8409265/modern-readable-code-optimal-time-comple-kd2u

// Approach : 1D View Cyclic Rotation
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' by 'm' be the grid size
// Time :  O(n * m)
// Space : O(1), auxiliary space

// import std;

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

using d2T = std::vector<std::vector<int>>;

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
    static auto shiftGrid(
        d2T & grid_,
        int shift_
    ) -> d2T;
};

auto Solution::shiftGrid(
    d2T & grid_,
    int shift_
) -> d2T {
    auto const totNums{grid_.size() * grid_.front().size()};

    // Skip redundant cycles
    if((shift_ %= totNums) == 0) {
        return grid_;
    }

    // Map 2D structure to a continuous 1D sequence
    auto flatGrid{grid_ | vs::join};
    // Identify the cut point for cyclic rotation
    auto pivot{rs::next(flatGrid.begin(), totNums - shift_)};

    rs::rotate(flatGrid, pivot);

    return grid_;
}
