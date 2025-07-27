// problem : https://leetcode.com/problems/maximize-subarrays-after-removing-one-conflicting-pair/description/
// submission : https://leetcode.com/problems/maximize-subarrays-after-removing-one-conflicting-pair/submissions
//    /1713691318
// solution post : https://leetcode.com/problems/maximize-subarrays-after-removing-one-conflicting-pair
//    /solutions/7012886/c-modern-readable-code-optimal-time-comp-505i

// #include <algorithm>
// #include <limits>
// #include <ranges>
// #include <vector>

class Solution {
public:
    using pairT = std::vector<int>;
    using pairsT = std::vector<pairT>;
// let 'n' be a count of the given numbers
// time complexity O(n)
// space complexity O(n)
// runtime 56 ms, beats 90.00 %
    [[nodiscard]]
    long long maxSubarrays(
        int const numsCount_,
        pairsT const & conflictingPairs_
    ) const;
};

long long Solution::maxSubarrays(
    int const numsCount_,
    pairsT const & conflictingPairs_
) const {
    namespace ranges = std::ranges;
    namespace views = std::views;
    using intT = std::numeric_limits<int>;
    auto bMin1{std::vector<int>(numsCount_ + 1, intT::max())};
    auto bMin2{std::vector<int>(numsCount_ + 1, intT::max())};
    for(auto const & pair: conflictingPairs_) {
        auto const a{*ranges::min_element(pair)};
        auto const b{*ranges::max_element(pair)};
        if(bMin1.at(a) > b) {
            bMin2.at(a) = bMin1.at(a);
            bMin1.at(a) = b;
        } else if (bMin2.at(a) > b) {
            bMin2.at(a) = b;
        }
    }
    auto maxSubarrsCount{0ll};
    auto ib1{numsCount_};
    auto b2{intT::max()};
    auto subarrsDeletedCounts{std::vector<long long>(numsCount_ + 1, 0)};
    for(auto const idx: views::iota(1, numsCount_ + 1) | views::reverse) {
        if(bMin1.at(ib1) > bMin1.at(idx)) {
            b2 = std::min(b2, bMin1.at(ib1));
            ib1 = idx;
        } else {
            b2 = std::min(b2, bMin1.at(idx));
        }
        auto const currSubarrsCount{
            std::min(bMin1.at(ib1), numsCount_ + 1) -
            idx};
        maxSubarrsCount += currSubarrsCount;
        subarrsDeletedCounts.at(ib1) += std::min(
            std::min(b2, bMin2.at(ib1)), numsCount_ + 1) -
            std::min(bMin1.at(ib1), numsCount_ + 1);
    }
    maxSubarrsCount +=  *ranges::max_element(subarrsDeletedCounts);
    return maxSubarrsCount;
}
