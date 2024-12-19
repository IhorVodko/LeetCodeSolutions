// problem : https://leetcode.com/problems/intersection-of-two-arrays/description/
// submission : https://leetcode.com/problems/intersection-of-two-arrays/submissions/1483109123
// solution post : https://leetcode.com/problems/intersection-of-two-arrays/solutions/6164961/c-modern-readable-code-beats-100-runtime-vuag


// #include <vector>


class Solution {
public:
    // let 'n' be a parameter 'nums1' length
    // 'm' - a parameter 'nums2' length
    // time complexity O(n * long(n) + m * log(m))
    // space complexity O(n + m)
    // runtime 0 ms, beats 100.00 %
    std::vector<int> intersection(
        std::vector<int> & nums1,
        std::vector<int> & nums2
    ) const {
        auto intersection{std::vector<int>{}};
        intersection.reserve(std::min(nums1.size(), nums2.size()));
        std::sort(nums1.begin(), nums1.end());
        std::sort(nums2.begin(), nums2.end());
        for(auto n1{nums1.cbegin()}, end1{nums1.cend()}, n2{nums2.cbegin()},
            end2{nums2.cend()}; n1 < end1 && n2 < end2;
        ) {
            if(*n1 == *n2) {
                intersection.emplace_back(*n1);
                while(++n1 < end1 && *n1 == intersection.back()) {}
                while(++n2 < end2 && *n2 == intersection.back()) {}
                continue;
                
            }
            if (*n1 < *n2) {
                while(++n1 < end1 && *n1 < *n2) {}
                continue;
            }
            if (*n1 > *n2) {
                while(++n2 < end2 && *n1 > *n2) {}
                continue;
            }
        }
        return intersection;
    }
};
