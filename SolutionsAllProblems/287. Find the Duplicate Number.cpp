// problem : https://leetcode.com/problems/find-the-duplicate-number/description/
// submission : https://leetcode.com/problems/find-the-duplicate-number/submissions/1635591689
// solution post : https://leetcode.com/problems/find-the-duplicate-number/solutions/6750354/
//    c-modern-readable-code-beats-100-by-cybe-k4s7

// #include <vector>

class Solution {
public:
// let 'n' be a length of the given array
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    int findDuplicate(std::vector<int> const & nums_) const;
};

int Solution::findDuplicate(std::vector<int> const & nums_) const {
    auto slowP{nums_.at(0)};
    auto fastP{slowP};
    do {
        slowP = nums_.at(slowP);
        fastP = nums_.at(nums_.at(fastP));
    } while(slowP != fastP);
    slowP = nums_.at(0);
    while(slowP != fastP) {
        slowP = nums_.at(slowP);
        fastP = nums_.at(fastP);
    }
    return slowP;
}
