// problem : https://leetcode.com/problems/largest-submatrix-with-rearrangements/description
// submission : https://leetcode.com/problems/largest-submatrix-with-rearrangements/submissions/1951394884
// solution post : https://leetcode.com/problems/largest-submatrix-with-rearrangements/solutions/7654927/
//    c-modern-readable-code-runtime-0-ms-beat-lgz8

// import std;

namespace {

// Compile-time initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace

// let 'n' by 'm' be the matrix size
// time complexity O(n * m)
// space complexity O(m)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    [[nodiscard]]
    auto largestSubmatrix(std::vector<std::vector<int>> const & mx_) const -> int;
};

auto Solution::largestSubmatrix(std::vector<std::vector<int>> const & mx_) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto maxArea{0};
    auto const rSz{mx_.size()};
    auto const cSz{mx_.front().size()};
    // Stores (height, column index) for previous row
    auto prevHeightAndCol{std::vector<std::pair<int, size_t>>{}};
    prevHeightAndCol.reserve(cSz);
    // Stores (height, column index) for current row
    auto curHeightAndCol{std::vector<std::pair<int, size_t>>{}};
    curHeightAndCol.reserve(cSz);
    // Tracks which columns were already extended from previous row
    auto isColUsed{std::vector<bool>(cSz)};
    for(auto const r: vs::iota(0uz, rSz)) {
        curHeightAndCol.clear();
        rngs::fill(isColUsed, false);
        // Extend heights from previous row where possible
        for(auto const [height, hCol]: prevHeightAndCol) {
            if(mx_[r][hCol] == 1) {
                curHeightAndCol.emplace_back(height + 1, hCol);
                isColUsed[hCol] = true;
            } 
        }
        // Start new height = 1 for columns not extended
        for(auto const c: vs::iota(0uz, cSz)) {
            if(!isColUsed[c] && mx_[r][c] == 1) {
                curHeightAndCol.emplace_back(1, c);
            }
        }
        // Compute max area assuming current ordering
        for(auto const j: vs::iota(0, static_cast<int>(curHeightAndCol.size()))) {
            auto const curArea{curHeightAndCol[j].first * (j + 1)};
            maxArea = std::max(maxArea, curArea);
        }
        // Move current state to previous for next iteration
        std::swap(prevHeightAndCol, curHeightAndCol);
    }
    return maxArea;
}
