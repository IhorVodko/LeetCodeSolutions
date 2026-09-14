// problem : https://leetcode.com/problems/rectangle-overlap/description
// submission : https://leetcode.com/problems/rectangle-overlap/submissions/2141537968
// solution post : https://leetcode.com/problems/rectangle-overlap/solutions/8521098/simplanation-simple-explanation-by-cyber-82k3

// Approach : Separating Axis Theorem (1D Projections)
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// Time :  O(1)
// Space : O(1)

// import std;

// #include <ios>
// #include <iostream>
// #include <vector>

namespace {

// Optimize standard I/O stream operations performance.
[[maybe_unused]]
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
    static auto isRectangleOverlap(
        std::vector<int> const & rect1_,
        std::vector<int> const & rect2_
    ) -> bool;
};

auto Solution::isRectangleOverlap(
    std::vector<int> const & rect1_,
    std::vector<int> const & rect2_
) -> bool {
    // 1. Extract boundary coordinates for the first rectangle.
    auto const rect1x1{rect1_[0]};
    auto const rect1y1{rect1_[1]};
    auto const rect1x2{rect1_[2]};
    auto const rect1y2{rect1_[3]};

    // 2. Extract boundary coordinates for the second rectangle.
    auto const rect2x1{rect2_[0]};
    auto const rect2y1{rect2_[1]};
    auto const rect2x2{rect2_[2]};
    auto const rect2y2{rect2_[3]};
    
    // 3. Verify if rectangles lack overlap by finding any separating axis.
    return !(
        // First rectangle is strictly to the left.
        rect1x2 <= rect2x1 ||
        // First rectangle is strictly to the right.
        rect1x1 >= rect2x2 ||
        // First rectangle is strictly below.
        rect1y2 <= rect2y1 ||
        // First rectangle is strictly above.
        rect1y1 >= rect2y2
    );
}
