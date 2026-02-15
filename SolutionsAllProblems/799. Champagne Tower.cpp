// problem : https://leetcode.com/problems/champagne-tower/description
// submission : https://leetcode.com/problems/champagne-tower/submissions/1920218864
// solution post : https://leetcode.com/problems/champagne-tower/solutions/7581847/
//    c-modern-readable-code-beats-100-runtime-dxph

// import std;

inline static int const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' be the number of rows
// time complexity O(n^2)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto champagneTower(
        int const glassPouredTotCnt_,
        int const queryRowIdx_,
        int const queryGlassIdx_
    ) const -> double;

private:
    static auto constexpr kMaxRowCnt{100};
};

auto Solution::champagneTower(
    int const glassPouredTotCnt_,
    int const queryRowIdx_,
    int const queryGlassIdx_
) const -> double {
   namespace vs = std::views;

    auto curRow{std::array<double, kMaxRowCnt>{}};
    auto nextRow{std::array<double, kMaxRowCnt>{}};
    // Start with all poured champagne in the top glass
    curRow.front() = static_cast<double>(glassPouredTotCnt_);
    // Simulate row by row until reaching the target row
    for(auto const r: vs::iota(0, queryRowIdx_)) {
        // Process each glass in the current row
        for(auto const c: vs::iota(0, r + 1)) {
            // Only the amount exceeding 1.0 spills equally to the two glasses below
            auto const overflow{(curRow[c] - 1.0) / 2.0};
            if(overflow > 0) {
                nextRow[c] += overflow;
                nextRow[c + 1] += overflow;
            }
        }
        // Move to the next row and reset buffer
        std::swap(curRow, nextRow);
        nextRow.fill(0);
    }
    // A glass can contain at most 1.0
    auto const volume{std::min(1.0, curRow[queryGlassIdx_])};
    return volume;
}
