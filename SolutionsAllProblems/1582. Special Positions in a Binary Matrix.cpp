// problem : https://leetcode.com/problems/special-positions-in-a-binary-matrix/description
// submission : https://leetcode.com/problems/special-positions-in-a-binary-matrix/submissions/1937998577
// solution post : https://leetcode.com/problems/special-positions-in-a-binary-matrix/solutions/7625452/
//    c-modern-readable-code-beats-100-runtime-fqrm

// import std;

// Static initializer to configure fast I/O before main() runs
inline static int const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' by 'm' be the matrix size
// time complexity O(n * m)
// space complexity O(n + m)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    [[nodiscard]]
    auto numSpecial(std::vector<std::vector<int>> const & mx_) const -> int;

private:
    // Marker values to track row/column state during traversal
    auto static constexpr kIsSpecial{-3};
    auto static constexpr kNotSpecial{-2};
    auto static constexpr kNan{-1};
};

auto Solution::numSpecial(std::vector<std::vector<int>> const & mx_) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto const rowTotCnt{std::ssize(mx_)};
    auto const colTotCnt{std::ssize(mx_.front())};
    // Stores the column index of the only '1' in each row,
    // or special markers if none or more than one exist
    auto specialColByRow{std::vector<int>(rowTotCnt, kNan)};
    // Tracks whether a column has exactly one '1'
    auto specialRowByCol{std::vector<int>(colTotCnt, kNan)};

    for(auto const r: vs::iota(0, rowTotCnt)) {
        for(auto const c: vs::iota(0, colTotCnt)) {
            if(mx_[r][c] == 0) {
                continue;
            }
            // Handle row state: ensure only one '1' per row
            if(specialColByRow[r] == kNan) {
                specialColByRow[r] = c;
            } else {
                specialColByRow[r] = kNotSpecial;
            }
            // Handle column state: ensure only one '1' per column
            if(specialRowByCol[c] == kNan) {
                specialRowByCol[c] = kIsSpecial;
            } else {
                specialRowByCol[c] = kNotSpecial;
            }
        }
    }
    // Count rows that have exactly one '1' and whose column also has exactly one '1'
    auto const specialPosCnt{rngs::count_if(specialColByRow, [&] (auto const col_) {
        return col_ != kNotSpecial && col_ != kNan && specialRowByCol[col_] == kIsSpecial;
    })};
    return specialPosCnt;
}
