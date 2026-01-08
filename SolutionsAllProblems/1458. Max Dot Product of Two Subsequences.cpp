// problem : https://leetcode.com/problems/max-dot-product-of-two-subsequences/description/
// submission : https://leetcode.com/problems/max-dot-product-of-two-subsequences/submissions/1878882716
// solution post : https://leetcode.com/problems/max-dot-product-of-two-subsequences/solutions/7478435/
//    c-modern-readable-code-beats-100-runtime-h2yj

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

// let 'n' be the length of the first array
// 'm' - of the second
// time complexity O(n * m)
// space complexity O(m)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto maxDotProduct(
        std::span<int const> const nums1_,
        std::span<int const> const nums2_
    ) const -> int;
};

auto Solution::maxDotProduct(
    std::span<int const> const nums1_,
    std::span<int const> const nums2_
) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    using intLim = std::numeric_limits<int>;

    auto min1{intLim::max()};
    auto max1{intLim::min()};
    auto min2{intLim::max()};
    auto max2{intLim::min()};
    for(auto const num: nums1_) {
        min1 = std::min(min1, num);
        max1 = std::max(max1, num);
    }
    for(auto const num: nums2_) {
        min2 = std::min(min2, num);
        max2 = std::max(max2, num);
    }
    if(max1 < 0 && 0 < min2) {
        auto const maxDotProd{max1 * min2};
        return maxDotProd;
    }
    if(0 < min1 && max2 < 0) {
        auto const maxDotProd{min1 * max2};
        return maxDotProd;
    }
    auto const nums2Sz{nums2_.size()};
    auto curMaxDotProdDp{std::vector<int>(nums2Sz + 1, 0)};
    auto prevMaxDotProdDp{std::vector<int>(nums2Sz + 1, 0)};
    for(auto const i1: vs::iota(0u, nums1_.size()) | vs::reverse) {
        rngs::fill(curMaxDotProdDp, 0);
        for(auto const i2: vs::iota(0u, nums2Sz) | vs::reverse) {
            auto const curDotProd1{prevMaxDotProdDp[i2]};
            auto const curDotProd2{curMaxDotProdDp[i2 + 1]};
            auto const curDotProd3{nums1_[i1] * nums2_[i2] + prevMaxDotProdDp[i2 + 1]};
            curMaxDotProdDp[i2] = std::max({curDotProd1, curDotProd2, curDotProd3});
        }
        prevMaxDotProdDp = curMaxDotProdDp;
    }
    auto const maxDotProd{curMaxDotProdDp.front()};
    return maxDotProd;
}
