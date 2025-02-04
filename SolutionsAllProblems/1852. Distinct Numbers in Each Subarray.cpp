// problem : https://leetcode.com/problems/distinct-numbers-in-each-subarray/description/
// submission : https://leetcode.com/problems/distinct-numbers-in-each-subarray/submissions/1531454472
// solution post : https://leetcode.com/problems/distinct-numbers-in-each-subarray/solutions/6375778/c-modern-readable-code-optimal-time-comp-gaxd

// #include <vector>
// #include <unordered_map>

// let 'n' be a length of the given array
// time complexity O(n)
// space complexity O(1)
// runtime 254 ms, beats 45.06 %
class Solution {
public:
    std::vector<int> distinctNumbers(
        std::vector<int> const & nums,
        int const subArrLength
    ) const {
        auto const numsSz{nums.size()};
        auto distinctNumsCounts{std::vector<int>(numsSz - subArrLength + 1,
            -1)};
        auto numToCount{std::unordered_map<int, int>{}};
        for(auto i{0}; i < subArrLength; ++i) {
            ++numToCount[nums.at(i)];
        }
        distinctNumsCounts.at(0) = numToCount.size(); 
        for(auto i{1}; i < numsSz - subArrLength + 1; ++i) {
            if(nums.at(i - 1) == nums.at(i + subArrLength - 1)) {
                distinctNumsCounts.at(i) = distinctNumsCounts.at(i - 1);
                continue;;
            } 
            if(--numToCount.at(nums.at(i - 1)) == 0) {
               numToCount.erase(nums.at(i - 1)); 
            }
            ++numToCount[nums.at(i + subArrLength - 1)];
            distinctNumsCounts.at(i) = numToCount.size();
        }
        return distinctNumsCounts;
    }
};
