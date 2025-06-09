// problem : https://leetcode.com/problems/verify-preorder-sequence-in-binary-search-tree/description 
// submission : https://leetcode.com/problems/verify-preorder-sequence-in-binary-search-tree/submissions/1658684927
// solution post : https://leetcode.com/problems/verify-preorder-sequence-in-binary-search-tree/solutions/6826378/
//    c-modern-readable-code-beats-100-runtime-09qx

// #include <limits>
// #include <vector>

class Solution {
public:
// let 'n' be a count of the given nums
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    bool verifyPreorder(std::vector<int> & preorderNums_) const;
};

bool Solution::verifyPreorder(std::vector<int> & preorderNums_) const {
    auto numLowerLimit_{std::numeric_limits<int>::min()} ;
    auto i{0};
    for(auto const num: preorderNums_) {
        while(i > 0 && preorderNums_.at(i - 1) < num) {
            numLowerLimit_ = preorderNums_.at(i - 1);
            --i;
        }
        if(num <= numLowerLimit_) {
            return false;
        }
        preorderNums_.at(i) = num;
        ++i;
    }
    return true;
}
