// problem : https://leetcode.com/problems/make-lexicographically-smallest-array-by-swapping-elements/description/
// submission : https://leetcode.com/problems/make-lexicographically-smallest-array-by-swapping-elements/submissions/1519962067
// solution post : https://leetcode.com/problems/make-lexicographically-smallest-array-by-swapping-elements/solutions/6327618/c-modern-readable-code-optimal-time-comp-lwpp

// #include <algorithm>
// #include <cmath>
// #include <list>
// #include <vector>
// #include <unordered_map>

// let 'n' be a parameter 'nums' length
// time complexity O(n * log(n))
// space complexity O(n)
// runtime 384 ms, beats 16.21 %
class Solution {
public:
    std::vector<int> lexicographicallySmallestArray(
        std::vector<int> & nums,
        int const limit
    ) const {
        if(nums.size() == 1) {
            return nums;
        }
        auto numsSorted{nums};    
        std::sort(numsSorted.begin(), numsSorted.end());
        auto numsToGroups{std::unordered_map<int, size_t>{}};
        numsToGroups[numsSorted.at(0)] = 1;
        auto groupsToHeaps{std::unordered_map<size_t, std::list<int>>{}};
        groupsToHeaps[1].emplace_back(numsSorted.at(0));
        for(auto prevNum{numsSorted.cbegin()}, currNum{numsSorted.cbegin() + 1},
            end{numsSorted.cend()}; currNum < end; ++prevNum, ++currNum
        ) {
            if(std::abs(*prevNum - *currNum) <= limit) {
                groupsToHeaps[groupsToHeaps.size()].emplace_back(*currNum);
            } else {
                groupsToHeaps[groupsToHeaps.size() + 1].emplace_back(*currNum);
            }
            numsToGroups[*currNum] = groupsToHeaps.size();
        }
        for(auto & num: nums) {
            num = groupsToHeaps.at(numsToGroups.at(num)).front(); 
            groupsToHeaps.at(numsToGroups.at(num)).pop_front();
        }
        return nums;
    }
};
