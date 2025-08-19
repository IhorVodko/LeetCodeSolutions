// problem : https://leetcode.com/problems/number-of-zero-filled-subarrays/description
// submission : https://leetcode.com/problems/number-of-zero-filled-subarrays/submissions/1740911438
// solution post : https://leetcode.com/problems/number-of-zero-filled-subarrays/solutions/7099859
//    /c-modern-readable-code-beats-100-runtime-91qe

// #include <vector>

class Solution {
public:
// let 'n' be count of the given numbers
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    long long zeroFilledSubarray(std::vector<int> const & nums_) const;
};

long long Solution::zeroFilledSubarray(std::vector<int> const & nums_) const {
    auto totalCount{0ll};
    auto currWindowCount{0ll};
    for(auto const num: nums_) {
        if(num == 0) {
            ++currWindowCount;
        } else {
            currWindowCount = 0;
        }
        totalCount += currWindowCount;
    }
    return totalCount;
}
