// problem : https://leetcode.com/problems/maximum-erasure-value/description
// submission : https://leetcode.com/problems/maximum-erasure-value/submissions/1708738428
// solution post : https://leetcode.com/problems/maximum-erasure-value/solutions/6995813
//    /c-modern-readable-code-optimal-time-comp-6azp

// #include <algorithm>
// #include <limits>
// #include <numeric>
// #include <vector>

namespace Util {
    inline auto constexpr kNumMax{static_cast<unsigned>(10e4) + 1};
}

class Solution {
public:
// let 'n' be a count of the given numbers
// 'm' - max possible value of any input number 
// time complexity O(n)
// space complexity O(m)
// runtime 9 ms, beats 94.17 %
    [[nodiscard]]
    int maximumUniqueSubarray(std::vector<int> const & nums_) const;
};

int Solution::maximumUniqueSubarray(std::vector<int> const & nums_) const {
    using namespace Util;
    using uT = std::numeric_limits<unsigned>;
    auto const numsSz{nums_.size()};
    auto scoreMax{0};
    auto numLatestIdxs{std::array<unsigned, kNumMax>{}};
    numLatestIdxs.fill(uT::max());
    auto prefSums{std::vector<int>(numsSz + 1, 0)};
    std::partial_sum(nums_.begin(), nums_.end(), prefSums.begin() + 1);
    for(auto idxStart{0u}, idxEnd{0u}; idxEnd < numsSz; ++idxEnd) {
        auto const numCur{nums_.at(idxEnd)};
        if(numLatestIdxs.at(numCur) != uT::max()) {
            idxStart = std::max(idxStart, numLatestIdxs.at(numCur ) + 1);
        }
        auto const scoreCurr{prefSums.at(idxEnd + 1) - prefSums.at(idxStart)};
        scoreMax = std::max(scoreMax, scoreCurr);
        numLatestIdxs.at(numCur) = idxEnd;
    }
    return scoreMax;
}
