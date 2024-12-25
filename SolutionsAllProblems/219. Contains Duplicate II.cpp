// problem : https://leetcode.com/problems/contains-duplicate-ii/description/
// submission : https://leetcode.com/problems/contains-duplicate-ii/submissions/1488195512
// solution post : https://leetcode.com/problems/contains-duplicate-ii/solutions/6186374/c-modern-readable-code-beats-99-runtime-yk7wi

// #include <vector>
// #include <unordered_map>

// let 'n' be a parameter 'nums' length
// time complexity O(n)
// space complexity O(n)
// runtime 43 ms, beats 99.05 %
class Solution {
public:
    bool containsNearbyDuplicate(
        std::vector<int> const & nums,
        int const limit
    ) const {
        auto numsToIdxs{std::unordered_map<int, size_t>{}};
        auto num{0};
        for(auto idx{size_t{0}}; idx < nums.size(); ++idx) {
            num = nums.at(idx);
            if(!numsToIdxs.contains(num)) {
                numsToIdxs[num] = idx;  
                continue;
            }
            if(idx - numsToIdxs.at(num) <= limit) {
                return true;
            } else {
                numsToIdxs.at(num) = idx;
            }
        }
        return false;
    }
};
