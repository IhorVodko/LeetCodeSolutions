// problem : https://leetcode.com/problems/minimum-cost-of-buying-candies-with-discount/description
// submission : https://leetcode.com/problems/minimum-cost-of-buying-candies-with-discount/submissions/2019351269
// solution post : https://leetcode.com/problems/minimum-cost-of-buying-candies-with-discount/solutions/8307105/
//    c-modern-readable-code-beats-100-runtime-kdup

// Approach : Greedy Sorting
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the number of candies
// complexity :  O(n * log(n))
// complexity : O(log(n)), auxiliary space

// import std;

class Solution final {
public:
    [[nodiscard]]
    static auto minimumCost(std::vector<int> & costs_) -> int;
};

auto Solution::minimumCost(std::vector<int> & costs_) -> int {
    namespace vs = std::views;
    namespace rs = std::ranges;

    // Grouping the priciest items ensures optimal savings on the third.
    rs::sort(costs_, std::greater{});

    // Skip the free item in every group of three consecutive elements.
    auto paidCandies =
        vs::iota(0uz, costs_.size()) |
        vs::filter([] (auto const j_) { return j_ % 3 != 2; }) |
        vs::transform([&] (auto const j_) { return costs_[j_]; });
    ;

    // Accumulate the final checkout price.
    return rs::fold_left(paidCandies, 0, std::plus{});
}

namespace {

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace
