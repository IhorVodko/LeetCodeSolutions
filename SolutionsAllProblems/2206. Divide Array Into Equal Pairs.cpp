// problem : https://leetcode.com/problems/divide-array-into-equal-pairs/description/ 
// submission : https://leetcode.com/problems/divide-array-into-equal-pairs/submissions/1578379051
// solution post : https://leetcode.com/problems/divide-array-into-equal-pairs/solutions/6552974/
//     c-modern-readable-code-beats-100-runtime-rc8n

// #include <bitset>
// #include <vector>

// let 'n' be a length of the given array
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    bool divideArray(std::vector<int> const & nums_) const {
        auto numCounts{std::bitset<501>{}};
        for(auto const num: nums_) {
            numCounts.flip(num);
        } 
        return numCounts.none();
    }
};
