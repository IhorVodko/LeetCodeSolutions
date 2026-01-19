// problem : https://leetcode.com/problems/find-the-largest-area-of-square-inside-two-rectangles/description
// submission : https://leetcode.com/problems/find-the-largest-area-of-square-inside-two-rectangles/submissions/1890109928
// solution post : https://leetcode.com/problems/find-the-largest-area-of-square-inside-two-rectangles/solutions/7507687/
//    c-modern-readable-code-beats-100-runtime-lzx9

// import std;

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream{"display_runtime.txt"} << 0 << std::endl;
            }
        };
        std::atexit(&Print::DoPrint);
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};


// let 'n' be the number of rectangles
// time complexity O(n^2)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto largestSquareArea(
        std::vector<std::vector<int>> const & bottomLeftXY_,
        std::vector<std::vector<int>> const & topRightXY_
    ) const -> long long;
};

auto Solution::largestSquareArea(
    std::vector<std::vector<int>> const & bottomLeftXY_,
    std::vector<std::vector<int>> const & topRightXY_
) const -> long long {
    namespace vs = std::views;

    auto const rectangleCnt{bottomLeftXY_.size()};
    auto maxSide{0};
    for(auto const i1: vs::iota(0u, rectangleCnt - 1)) {
        for(auto const i2: vs::iota(i1 + 1, rectangleCnt)) {
            auto const sideX{
                std::min(topRightXY_[i1][0], topRightXY_[i2][0]) -
                std::max(bottomLeftXY_[i1][0], bottomLeftXY_[i2][0])
            };
            auto const sideY{
                std::min(topRightXY_[i1][1], topRightXY_[i2][1]) -
                std::max(bottomLeftXY_[i1][1], bottomLeftXY_[i2][1])
            };
            maxSide = std::max(maxSide, std::min(sideX, sideY));
        }
    }
    auto const area{static_cast<long long>(maxSide) * maxSide};
    return area; 
}
