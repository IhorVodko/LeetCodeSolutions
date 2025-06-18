// problem : https://leetcode.com/problems/divide-array-into-arrays-with-max-difference/description/
// submission : https://leetcode.com/problems/divide-array-into-arrays-with-max-difference/submissions/1668364748
// solution post : https://leetcode.com/problems/divide-array-into-arrays-with-max-difference/solutions/6858202/
//    c-modern-readable-code-optimal-time-comp-1nw7

// #include <ranges>
// #include <vector>

#include <ranges>

namespace Util {
    constinit auto const kDivisor{3};
}

class Solution {
public:
    using Arr2T = std::vector<std::vector<int>>;
// let 'n' be a length of the given array
// time complexity O(n * log2(n))
// space complexity O(n)
// runtime 40 ms, beats 90.19 %
    [[nodiscard]]
    Arr2T divideArray(
        std::vector<int> & nums_,
        int const diffMax_
    ) const;
};

Solution::Arr2T Solution::divideArray(
    std::vector<int> & nums_,
    int const diffMax_
) const {
    using namespace Util;
    namespace ranges = std::ranges;
    namespace views = std::views;
    ranges::sort(nums_);
    auto nums3{Arr2T{}};
    nums3.reserve(nums_.size() / kDivisor);
    for(auto && subArr: nums_ | views::chunk(kDivisor)) {
        auto const diff{subArr.back() - subArr.front()};
        if(diff > diffMax_) {
            return {};
        }
        nums3.emplace_back(subArr.begin(), subArr.end());
    }
    return nums3;
}
