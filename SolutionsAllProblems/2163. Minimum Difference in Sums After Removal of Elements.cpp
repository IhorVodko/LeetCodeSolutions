// problem : https://leetcode.com/problems/minimum-difference-in-sums-after-removal-of-elements/description
// submission : https://leetcode.com/problems/minimum-difference-in-sums-after-removal-of-elements/submissions
//    /1702428725
// solution post : https://leetcode.com/problems/minimum-difference-in-sums-after-removal-of-elements
//    /solutions/6974317/c-modern-readable-code-optimal-time-comp-m1ki

// #include <algorithm>
// #include <ranges>
// #include <vector>

class Solution {
public:
// let 'n' be a count of the given numbers
// time complexity O(n * log2(n))
// space complexity O(n)
// runtime 127 ms, beats 87.63 %
    [[nodiscard]]
    long long minimumDifference(std::vector<int> const & nums_) const;
};

long long Solution::minimumDifference(std::vector<int> const & nums_) const {
    namespace views = std::views;
    auto const numsSzThird{ std::ssize( nums_) / 3};
    auto nums1( std::vector<long long>( numsSzThird + 1, -1));
    auto sum1{ 0ll};
    auto numsMax{ std::priority_queue<int>{}};
    auto const numsBegin(nums_.begin());
    for(auto const num: views::counted( numsBegin, numsSzThird)) {
        sum1 += num;
        numsMax.emplace( num);
    }
    nums1.at( 0) = sum1;
    for(auto const idx: views::iota( numsSzThird, numsSzThird * 2)) {
        auto const num{ nums_.at( idx)};
        sum1 += num;
        numsMax.emplace( num);
        sum1 -= numsMax.top();
        numsMax.pop();
        nums1.at( idx - (numsSzThird - 1)) = sum1;
    }
    auto sum2{ 0ll};
    auto numsMin{ std::priority_queue<int, std::vector<int>, std::greater<>>{}};
    auto const begin2Idx{ numsSzThird * 2};
    auto const end2Idx{ numsSzThird * 3};
    auto const nums2Sz{ end2Idx - begin2Idx};
    for(auto const num: views::counted( numsBegin + begin2Idx, nums2Sz)) {
        sum2 += num;
        numsMin.emplace( num);
    }
    auto minDiff{ nums1.at(numsSzThird) - sum2};
    for(auto const idx:
            views::iota(numsSzThird, numsSzThird * 2)
        |   views::reverse
    ) {
        auto const num{ nums_.at( idx)};
        sum2 += num;
        numsMin.emplace( num);
        sum2 -= numsMin.top();
        numsMin.pop();
        auto const currDiff{ nums1.at( idx - numsSzThird) - sum2};
        minDiff = std::min( minDiff, currDiff);
    }
    return minDiff;
}
