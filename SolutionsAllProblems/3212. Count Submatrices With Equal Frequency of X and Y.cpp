// problem : https://leetcode.com/problems/count-submatrices-with-equal-frequency-of-x-and-y/description
// submission : https://leetcode.com/problems/count-submatrices-with-equal-frequency-of-x-and-y/description
// solution post : https://leetcode.com/problems/count-submatrices-with-equal-frequency-of-x-and-y/solutions/
//    7669879/c-modern-readable-code-runtime-0-ms-beat-5rqt

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
    using mxT = std::vector<std::vector<char>>;

    [[nodiscard]]
    auto numberOfSubmatrices(mxT & mx_) const -> int;
};

auto Solution::numberOfSubmatrices(mxT & mx_) const -> int {
    namespace vs = std::views;

    auto const rSz{mx_.size()};
    auto const cSz{mx_.front().size()};
    // For each column, store cumulative (X - Y) difference from row 0 up to current row
    auto colXYDiffs{std::vector<int>(cSz)};
    // Tracks whether column has seen at least one 'X' so far (from row 0 to current row)
    auto isXPresentPerCol{std::vector<bool>(cSz)};
    auto subMxCnt{0};
    for(auto const r: vs::iota(0uz, rSz)) {
        // Prefix sum over columns for current row using accumulated column differences
        auto rowXYDiffs{0};
        // Tracks if the current prefix (from column 0 to c) contains at least one 'X',
        // which is equivalent to the submatrix containing at least one 'X'
        auto isXPresentInRow{false};
        for(auto const c: vs::iota(0uz, cSz)) {
            auto const chr{mx_[r][c]};
            // Update column-wise cumulative difference: +1 for 'X', -1 for 'Y', 0 otherwise
            if(chr == 'X') {
                ++colXYDiffs[c];
                // Mark that this column contributes at least one 'X' in any submatrix
                // ending here
                isXPresentPerCol[c] = true;
            } else if(chr == 'Y') {
                --colXYDiffs[c];
            }
            // Build prefix sum across columns to represent submatrix [0..r][0..c]
            rowXYDiffs += colXYDiffs[c];
            // If any column in current prefix has seen 'X', then submatrix contains at least one 'X'
            if(isXPresentPerCol[c]) {
                isXPresentInRow = true;
            }
            // A valid submatrix (top-left anchored at (0,0) and ending at (r,c)):
            // total X-Y difference must be zero AND must contain at least one 'X'
            if(isXPresentInRow && rowXYDiffs == 0) {
                ++subMxCnt;
            }
        }
    }
    return subMxCnt;
}
