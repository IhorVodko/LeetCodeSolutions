// problem : https://leetcode.com/problems/find-all-k-distant-indices-in-an-array/description/
// submission : https://leetcode.com/problems/find-all-k-distant-indices-in-an-array/submissions/1675035206
// solution post : https://leetcode.com/problems/find-all-k-distant-indices-in-an-array/solutions/6880981/
//    c-modern-readable-code-beats-100-runtime-g8yb

// #include <algorithms>
// #include <ranges>
// #include <vector>

class Solution {
public:
// let 'n' be a count of the given numbers
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    std::vector<int> findKDistantIndices(
        std::vector<int> & nums_,
        int const keyVal_,
        int const maxDistance_
    ) const;
};

std::vector<int> Solution::findKDistantIndices(
    std::vector<int> & nums_,
    int const keyVal_,
    int const maxDistance_
) const {
    namespace views = std::views;
    auto const numsSz{static_cast<int>(nums_.size())};
    auto first{-1};
    auto last{-1};
    auto resultIdxs{std::vector<int>{}};
    resultIdxs.reserve(numsSz);
    for(auto const i: views::iota(0, numsSz)) {
        auto const num{nums_.at(i)};
        if(num != keyVal_) {
            continue;
        }
        auto const firstCurr{std::max(0, i - maxDistance_)};
        auto const lastCurr{std::min(i + maxDistance_, numsSz - 1)};
        auto const firstIdx{last < firstCurr ? firstCurr : (last + 1)};
        for(auto const i2: views::iota(firstIdx, lastCurr + 1)) {
            resultIdxs.emplace_back(i2);
        }
        last = lastCurr;
    }
    return resultIdxs;
}
