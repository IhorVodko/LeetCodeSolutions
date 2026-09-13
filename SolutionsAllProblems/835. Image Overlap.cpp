// problem : https://leetcode.com/problems/image-overlap/description
// submission : https://leetcode.com/problems/image-overlap/submissions/2140947160
// solution post : https://leetcode.com/problems/image-overlap/solutions/8519954/simplanation-simple-explanation-by-cyber-tgnc

// Approach : 2D Convolution via Row Bitmasking
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the given square image (matrix) dimension 
// Time :  O(n^3)
// Space : O(N)

// import std;

// #include <algorithm>
// #include <bitset>
// #include <ios>
// #include <iostream>
// #include <ranges>
// #include <vector>

// #include <cstddef>

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

template<typename T_>
using vec1d = std::vector<T_>;
template<typename T_>
using vec2d = std::vector<std::vector<T_>>;

constexpr auto kMaxImgDim{30uz};

using imgRowMsk = std::bitset<kMaxImgDim>;

constexpr auto kBitShiftStep{1};

// Compress binary image row into a bitset for fast shift operations
constexpr auto buildImgRowMask{[] [[nodiscard]] (
    auto const rowMask_,
    auto const piexelVal_
) {
    auto const currBit{imgRowMsk{
        static_cast<size_t>(piexelVal_)
    }};

    return (rowMask_ << kBitShiftStep) | currBit;
}};

// 1. Convert 2D matrices to 1D arrays of bitsets representing image rows
constexpr auto buildImgMask{[] [[nodiscard]] (auto const & img_) {
    return 
        img_ |
        vs::transform([] (auto const & row_) {
            return rs::fold_left(row_, imgRowMsk{}, buildImgRowMask);
        }) |
        rs::to<std::vector>()
    ;
}};

// Disable standard I/O synchronization for performance
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
    static auto largestOverlap(
        vec2d<int> const & img1_,
        vec2d<int> const & img2_
    ) -> int;
};

auto Solution::largestOverlap(
    vec2d<int> const & img1_,
    vec2d<int> const & img2_
) -> int {
    // 2. Encode both images into row bitmasks
    auto const img1Mask{buildImgMask(img1_)};
    auto const img2Mask{buildImgMask(img2_)};

    auto const imgDim{static_cast<int>(img1_.size())};
    auto const shiftBounds{imgDim - 1};
    // 3. Generate all possible vertical and horizontal shift vectors
    auto const shiftRng{vs::iota(-1 * shiftBounds, shiftBounds + 1)};
    auto const shifts{vs::cartesian_product(shiftRng, shiftRng)};

    // 4. Calculate overlap for a specific row mapping given a 2D shift
    auto const calcImgRowOverlap{[&] [[nodiscard]] (
        auto const imgOverlapCnt_,
        auto const rowIdx_,
        auto const shift_
    ) {
        auto const [colShift, rowShift]{shift_};
        auto const shiftedRowIdx{rowIdx_ + rowShift};

        // Check if vertical shift keeps the row mapping within bounds
        if(shiftedRowIdx < 0 || shiftedRowIdx >= imgDim) {
            return imgOverlapCnt_;
        }

        auto const img1RowMask{img1Mask[rowIdx_]};
        auto const img2RowMask{img2Mask[shiftedRowIdx]};

        // Shift row bits horizontally based on the column translation delta
        auto const shiftedImg1RowMask{colShift >= 0 ?
            (img1RowMask >> colShift) :
            (img1RowMask << (-1 * colShift))
        };
        auto const rowOverlap{shiftedImg1RowMask & img2RowMask};

        return imgOverlapCnt_ + static_cast<int>(rowOverlap.count());
    }};

    // 5. Aggregate total overlap across all valid rows for a specific 2D shift
    auto const CalcMaxImgOverlap{[&] [[nodiscard]] (
        auto const maxImgOverlapCnt_,
        auto const shift_
    ) {
        auto const currImgOverlapCnt{rs::fold_left(
            vs::iota(0, imgDim),
            0,
            [&] (auto const imgOverlapCnt_, auto const rowIdx_) {
                return calcImgRowOverlap(imgOverlapCnt_, rowIdx_, shift_);
            }
        )};

        return rs::max(maxImgOverlapCnt_, currImgOverlapCnt);
    }};

    // 6. Find the maximum overlap across all evaluated shifts
    return rs::fold_left(shifts, 0, CalcMaxImgOverlap);
}
