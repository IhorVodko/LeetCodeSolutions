// problem : https://leetcode.com/problems/merge-two-2d-arrays-by-summing-values/description/
// submission : https://leetcode.com/problems/merge-two-2d-arrays-by-summing-values/submissions/1561652976
// solution post : https://leetcode.com/problems/merge-two-2d-arrays-by-summing-values/solutions/6491402/
//     c-modern-readable-code-beats-100-runtime-mag8

// #include <vector>

// let 'a1' be a length of the given first array
// 'a2' - of the second array
// time complexity O(a1 + a2)
// space complexity O(a1 + a2)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    using Arr2T =  vector<vector<int>>;
    Arr2T mergeArrays(
        Arr2T const & nums1,
        Arr2T const & nums2
    ) const {
        auto const nums1Sz{nums1.size()};
        auto const nums2Sz{nums2.size()};
        auto num1{0};
        auto num2{0};
        auto mergedArray{Arr2T{}};
        mergedArray.reserve(nums1Sz + nums2Sz);
        while (num1 < nums1Sz && num2 < nums2Sz) {
            if (nums1[num1][0] < nums2[num2][0]) {
                mergedArray.emplace_back(nums1[num1]);
                ++num1;
            } else if (nums1[num1][0] == nums2[num2][0]) {
                mergedArray.emplace_back(
                    std::vector<int>{nums1[num1][0], nums1[num1][1] + nums2[num2][1]});
                ++num1;
                ++num2;
            } else {
                mergedArray.emplace_back(nums2[num2]);
                ++num2;
            }
        }
        while (num1 < nums1Sz) {
            mergedArray.emplace_back(nums1[num1]);
            ++num1;
        }
        while (num2 < nums2Sz) {
            mergedArray.emplace_back(nums2[num2]);
            ++num2;
        }
        return mergedArray;
    }
};
