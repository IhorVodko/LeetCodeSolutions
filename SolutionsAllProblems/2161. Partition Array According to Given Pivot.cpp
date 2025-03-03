// problem : https://leetcode.com/problems/partition-array-according-to-given-pivot/description/  
// submission : https://leetcode.com/problems/partition-array-according-to-given-pivot/submissions/1561705104
// solution post : https://leetcode.com/problems/partition-array-according-to-given-pivot/solutions/6491577/
//     c-modern-readable-code-optimal-time-comp-xtrl

// #include <limits>
// #include <vector>

// let 'n' be a length of the given array
// time complexity O(n)
// space complexity O(n)
// runtime 4 ms, beats 80.60 %
class Solution {
public:
    std::vector<int> pivotArray(
        std::vector<int> const & nums,
        int const pivot
    ) const {
        auto const numsSz{nums.size()};
        auto sortedArr{std::vector<int>(numsSz,
            std::numeric_limits<int>::max())};
        auto lessIdx{size_t{0}};
        auto greaterIdx{numsSz - 1};
        for(auto i{size_t{0}}, j{numsSz - 1}; i < numsSz && j >= 0; ++i, --j) {
            if(nums[i] < pivot) {
                sortedArr.at(lessIdx) = nums[i];
                ++lessIdx;
            }
            if(nums[j] > pivot) {
                sortedArr.at(greaterIdx) = nums[j];
                --greaterIdx;
            }
        }
        while(lessIdx <= greaterIdx) {
            sortedArr.at(lessIdx) = pivot;
            ++lessIdx;
        }
        return sortedArr;
    }
};
