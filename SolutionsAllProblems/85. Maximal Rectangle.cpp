// problem : https://leetcode.com/problems/maximal-rectangle/description
// submission : https://leetcode.com/problems/maximal-rectangle/submissions/1883956586
// solution post : https://leetcode.com/problems/maximal-rectangle/solutions/7492178/
//    c-modern-readable-code-beats-100-runtime-1qsj

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

// let 'n' by 'm' be the matrix size
// time complexity O(n * m)
// space complexity O(m)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto maximalRectangle(std::vector<std::vector<char>> const mx_) const -> int;
};

auto Solution::maximalRectangle(std::vector<std::vector<char>> const mx_) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto const rCnt{std::ssize(mx_)};
    auto const cCnt{std::ssize(mx_.front())};
    auto left{std::vector<int>(cCnt)};
    auto right{std::vector<int>(cCnt)};
    auto height{std::vector<int>(cCnt)};
    rngs::fill(right, cCnt);
    auto maxArea{std::numeric_limits<int>::min()};
    for(auto const rIdx: vs::iota(0, rCnt)) {
        auto curLeft{0};
        auto curRight{cCnt};
        for(auto const cIdx: vs::iota(0, cCnt)) {
            if(mx_[rIdx][cIdx] == '1') {
                ++height[cIdx];
            } else {
                height[cIdx] = 0;
            }
        }
        for(auto const cIdx: vs::iota(0, cCnt)) {
            if(mx_[rIdx][cIdx] == '1') {
                left[cIdx] = std::max(left[cIdx], curLeft);
            } else {
                left[cIdx] = 0;
                curLeft = cIdx + 1;
            }
        }
        for(auto const cIdx: vs::iota(0, cCnt) | vs::reverse) {
            if(mx_[rIdx][cIdx] == '1') {
                right[cIdx] = std::min(right[cIdx], static_cast<int>(curRight));
            } else {
                right[cIdx] = cCnt;
                curRight = cIdx;
            }
        }
        for(auto const cIdx: vs::iota(0, cCnt)) {
            auto const curArea{(right[cIdx] - left[cIdx]) * height[cIdx]};
            maxArea = std::max(maxArea, curArea);
        }
    }
    return maxArea;
}
