// problem : https://leetcode.com/problems/longest-nice-subarray/description/
// submission : https://leetcode.com/problems/longest-nice-subarray/submissions/1578430753
// solution post : https://leetcode.com/problems/longest-nice-subarray/solutions/6553110/
//     c-modern-readable-code-beats-100-runtime-bcrx

// #include <algorithm>
// #include <bitset>
// #include <vector>

// let 'n' be a length of the given array
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int longestNiceSubarray(std::vector<int> & nums_) const {
        using bitsT = std::bitset<sizeof(unsigned) * 8>;
        auto constexpr zeroesBits{bitsT{}};
        auto bitsUsed{bitsT{}};
        auto maxLengthSubArr{1};
        auto currLengthSubArr{0};
        auto const zeroes{bitsT{}};
        for(auto idx{0}; idx - currLengthSubArr <
            nums_.size() - maxLengthSubArr;
        ) {
            if((bitsUsed & bitsT{static_cast<unsigned>(nums_[idx])}) == 
                zeroesBits
            ) {
                bitsUsed |= bitsT{static_cast<unsigned>(nums_[idx])};
                ++currLengthSubArr; 
                maxLengthSubArr = std::max(maxLengthSubArr, currLengthSubArr);
                ++idx;
            } else {
                bitsUsed ^= bitsT{static_cast<unsigned long long>(
                    nums_.at(idx - currLengthSubArr))};
                --currLengthSubArr;
            }
        }
        return maxLengthSubArr;
    }
};
