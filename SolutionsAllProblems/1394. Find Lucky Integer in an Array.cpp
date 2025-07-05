// problem : https://leetcode.com/problems/find-lucky-integer-in-an-array/description/
// submission : https://leetcode.com/problems/find-lucky-integer-in-an-array/submissions/1687685660
// solution post : https://leetcode.com/problems/find-lucky-integer-in-an-array/solutions/6925116/
//    c-modern-readable-code-beats-100-runtime-f0p7

// #include <vector>
// #include <unordered_map>

class Solution {
public:
// let 'n' be a count of the given numbers
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    int findLucky(std::vector<int> const & nums_) const;
};

int Solution::findLucky(std::vector<int> const & nums_) const {
    auto numToCount{std::unordered_map<int, size_t>{}};
    for(auto const num: nums_) {
        ++numToCount[num];
    }
    auto numLucky{-1};
    for(auto const [num, count]: numToCount) {
        if(num == count) {
            numLucky = std::max(numLucky, num);
        }
    }
    return numLucky;
}
