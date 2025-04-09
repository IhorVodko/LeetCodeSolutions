// problem : https://leetcode.com/problems/minimum-operations-to-make-array-values-equal-to-k/description/
// submission : https://leetcode.com/problems/minimum-operations-to-make-array-values-equal-to-k/submissions/1601882281
// solution post : https://leetcode.com/problems/minimum-operations-to-make-array-values-equal-to-k/solutions/6633838/
//     c-modern-readable-code-beats-99-runtime-cd2tp

// #include <bitset>
// #include <vector>

// let 'n' be a count of given numbers
// time complexity O(n)
// space complexity O(n)
// runtime 3 ms, beats 99.06 %
class Solution {
public:
    int minOperations(
        std::vector<int> const & nums_,
        int const targetVal_
    ) const;
};

int Solution::minOperations(
    std::vector<int> const & nums_,
    int const targetVal_
) const {
    auto numsSeen{std::bitset<101>{}};
    for(auto const num: nums_) {
        if(num < targetVal_) {
            return -1;
        } 
        numsSeen.set(num);
    }
    return numsSeen.count() - (numsSeen.test(targetVal_) ? 1 : 0);
}
