// problem : https://leetcode.com/problems/intersection-of-two-arrays-ii/description/
// submission : https://leetcode.com/problems/intersection-of-two-arrays-ii/submissions/1487413157
// solution post : https://leetcode.com/problems/intersection-of-two-arrays-ii/solutions/6182378/c-modern-readable-code-beats-100-runtime-rbso


// #include <vector>
// #include <unordered_map>

class Solution {
public:
    // let 'n1' be a parameter 'nums1' length
    // 'n2' - a parameter 'nums2' length
    // time complexity O(n1 + n2)
    // space complexity O(min(n1, n2))
    // runtime 0 ms, beats 100.00 %
    std::vector<int> intersect(
        std::vector<int> & nums1,
        std::vector<int> & nums2
    ) const {
        if(nums1.size() > nums2.size()) {
            std::swap(nums1, nums2);
        }
        auto numsToFreqs{std::unordered_map<int, size_t>{}};
        for(auto const num: nums1) {
            ++numsToFreqs[num];
        }  
        auto out{nums1.begin()};
        for(auto const num: nums2) {
            if(numsToFreqs[num] > 0) {
                *out++ = num;
                --numsToFreqs[num];
            }
        }
        return {nums1.begin(), out};
    }
};
