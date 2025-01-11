// problem : https://leetcode.com/problems/4sum-ii/description/
// submission : https://leetcode.com/problems/4sum-ii/submissions/1505446684
// solution post : https://leetcode.com/problems/4sum-ii/solutions/6266538/c-modern-readable-code-optimal-time-comp-wgws

// #include <vector>
// #include <unordered_map>

// let 'n' be a parameter 'nums1', 'nums2', 'nums3', 'nums4' length
// time complexity O(n^2)
// space complexity O(1)
// runtime 95 ms, beats 76.76 %
class Solution {
public:
    int fourSumCount(
        std::vector<int> const & nums1,
        std::vector<int> const & nums2,
        std::vector<int> const & nums3,
        std::vector<int> const & nums4
    ) const {
        auto sums12Counts{std::unordered_map<int, size_t>{}};
        for(auto n1 : nums1) {
            for(auto n2 : nums2) {
                ++sums12Counts[n1 + n2]; 
            }
        }
        auto sumsCount{0};
        auto sum{0};
        for(auto n3 : nums3) {
            for(auto n4 : nums4) {
                sum = -1 * (n3 + n4);
                if(sums12Counts.contains(sum)) {
                    sumsCount += sums12Counts.at(sum); 
                }
            }
        }
        return sumsCount;
    }
};
