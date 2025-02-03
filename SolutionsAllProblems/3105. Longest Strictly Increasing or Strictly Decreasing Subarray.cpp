// problem : https://leetcode.com/problems/longest-strictly-increasing-or-strictly-decreasing-subarray/description/
// submission : https://leetcode.com/problems/longest-strictly-increasing-or-strictly-decreasing-subarray/submissions/1530174789
// solution post : https://leetcode.com/problems/longest-strictly-increasing-or-strictly-decreasing-subarray/solutions/6369538/c-modern-readable-code-beats-100-runtime-s2qe

// #include <algorithm>
// #include <vector>

// let 'n' be an input array length
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int longestMonotonicSubarray(
        std::vector<int> const & nums
    ) {
        auto subIncLength{1};
        auto subDecrLength{1};
        auto subLengthMax{std::numeric_limits<int>::min()};
        for(auto numCurr{nums.begin()}, numNext{nums.begin() + 1},
            end{nums.end()}; numNext < end; ++numCurr, ++numNext
        ) {
            if(*numCurr < *numNext) {
                if(subDecrLength > 1) {
                    subLengthMax = std::max(subLengthMax, subDecrLength);
                    subDecrLength = 1;
                }
                ++subIncLength;
            } else if(*numCurr > *numNext) {
                if(subIncLength > 1) {
                    subLengthMax = std::max(subLengthMax, subIncLength);
                    subIncLength = 1;
                }
                ++subDecrLength;
            } else {
                subLengthMax = std::max(subLengthMax, std::max(subIncLength,
                    subDecrLength));
                subIncLength = 1;
                subDecrLength = 1;
            }
        }
        return std::max(subLengthMax, std::max(subIncLength, subDecrLength));
    }
};
