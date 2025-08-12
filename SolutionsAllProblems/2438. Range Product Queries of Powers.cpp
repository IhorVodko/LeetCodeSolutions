// problem : https://leetcode.com/problems/range-product-queries-of-powers/description
// submission : https://leetcode.com/problems/range-product-queries-of-powers/submissions/1732415083
// solution post : https://leetcode.com/problems/range-product-queries-of-powers/solutions/7071559/
//    c-modern-readable-code-beats-100-runtime-y3v1

// #include <bit>
// #include <ranges>
// #include <vector>

namespace Util {
    inline auto constexpr kModVal{static_cast<int>(1e9) + 7};
}

class Solution {
public:
    using queryT = std::vector<int>;
    using queriesT = std::vector<queryT>;
// let 's' be a given targetSum number
// 'q' - length of the given gueries
// time complexity O(log2(s)^2 + q) 
// space complexity O(log2(s)^2) 
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    std::vector<int> productQueries(
        int const targetSum_,
        queriesT const & queries_
    ) const;
};

std::vector<int> Solution::productQueries(
    int const targetSum_,
    queriesT const & queries_
) const {
    namespace ranges = std::ranges;
    namespace views = std::views;
    using namespace Util;
    auto numPows{std::vector<int>{}};
    auto targetSum{static_cast<size_t>(targetSum_)};
    while(targetSum > 0) {
        auto const num{std::bit_floor(targetSum)};
        numPows.emplace_back(num);
        targetSum -= num;
    }
    ranges::reverse(numPows);
    auto const numPowsSz{numPows.size()};
    auto precomputedProducts{std::vector<std::vector<int>>(
        numPowsSz, 
        std::vector<int>(numPowsSz, 0)
    )};
    for(auto const numIdxStart: views::iota(0u, numPowsSz)) {
        auto product{1};
        for(auto const numIdxEnd: views::iota(numIdxStart, numPowsSz)) {
            product =
                (static_cast<long long>(product) *
                    numPows.at(numIdxEnd))
                % kModVal;
            precomputedProducts.at(numIdxStart).at(numIdxEnd) = product;
        }
    }
    auto const queriesSz{queries_.size()};
    auto products{std::vector<int>{}};
    products.reserve(queriesSz);
    for(auto const & query: queries_) {
        auto const powIdxStart{query.at(0)};
        auto const powIdxEnd{query.at(1)};
        auto const product{precomputedProducts.at(powIdxStart).at(powIdxEnd)};
        products.emplace_back(product);
    }
    return products;
}
