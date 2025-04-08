// problem : https://leetcode.com/problems/minimum-number-of-operations-to-make-elements-in-array-distinct/description/
// submission : https://leetcode.com/problems/minimum-number-of-operations-to-make-elements-in-array-distinct/
//     submissions/1600829931
// solution post : 

// #include <bitset>
// #include <vector>

// let 'n' be a count of the numbers given
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int minimumOperations(std::vector<int> const & nums_) const;
};

int Solution::minimumOperations(std::vector<int> const & nums_) const {
    auto seenNums{std::bitset<101>{}};
    for(auto numIt{nums_.rbegin()}, numsEnd{nums_.rend()}; numIt < numsEnd;
        ++numIt
    ) {
        if(seenNums.test(*numIt)) {
            return (numsEnd - numIt - 1) / 3 + 1;
        }
        seenNums.set(*numIt); 
    }
    return 0;
}
