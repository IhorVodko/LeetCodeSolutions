// problem : https://leetcode.com/problems/count-largest-group/description/
// submission : https://leetcode.com/problems/count-largest-group/submissions/1616023626
// solution post : https://leetcode.com/problems/count-largest-group/solutions/6681488/
//     c-modern-readable-code-beats-100-runtime-4rc5

// #include <algorithm>
// #include <limits>
// #include <unordered_map>

namespace Utility {
    auto constexpr kRadix{10};
}

// let 'n' be a value of the given number
// time complexity O(n * log(n))
// space complexity O(log(n))
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int countLargestGroup(int const numMax_) const;
};

int Solution::countLargestGroup(int const numMax_) const {
    using namespace Utility;
    auto sumToCount{std::unordered_map<int, size_t>{}};
    auto sumCountMax{std::numeric_limits<size_t>::min()};
    for(auto num{1}; num <= numMax_; ++num) {
        auto sum{0};
        auto numCurr{num};
        while(numCurr > 0) {
            sum += numCurr % kRadix;
            numCurr /= kRadix;
        }
        sumCountMax = std::max(sumCountMax, ++sumToCount[sum]);
    }
    return std::count_if(sumToCount.cbegin(), sumToCount.cend(),
        [=](auto const & sumAndCount) {return sumAndCount.second == sumCountMax;});
}
