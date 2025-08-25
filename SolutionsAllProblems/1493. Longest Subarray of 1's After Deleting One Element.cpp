// problem : https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/description
// submission : https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/submissions/1747714751
// solution post : https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/solutions/7120816/
//  c-modern-readable-code-beats-100-runtime-ax0o

// #include <algorithm>
// #include <ranges>
// #include <vector>

class Solution {
public:
// let 'n' be a count of the given numbers
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    int longestSubarray(std::vector<int> const & nums_) const;
};

int Solution::longestSubarray(std::vector<int> const & nums_) const {
    namespace views = std::views;
    auto const numsSz{nums_.size()};
    auto zeroCount{0u};
    auto maxWindowSz{0u};
    auto windowStartIdx{0u};
    for(auto const idx: views::iota(0u, numsSz)) {
        if(nums_.at(idx) == 0) {
            ++zeroCount;
        }
        while(zeroCount > 1 && windowStartIdx < idx) {
            if(nums_.at(windowStartIdx) == 0) {
                --zeroCount;
            }
            ++windowStartIdx;
        }
        auto const currWindowSz{idx - windowStartIdx}; 
        maxWindowSz = std::max(maxWindowSz, currWindowSz);
    }
    return maxWindowSz;
}
