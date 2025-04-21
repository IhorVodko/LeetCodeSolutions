// problem : https://leetcode.com/problems/count-the-hidden-sequences/description/
// submission : https://leetcode.com/problems/count-the-hidden-sequences/submissions/1613725985
// solution post : https://leetcode.com/problems/count-the-hidden-sequences/solutions/6674687/
//     c-modern-readable-code-beats-100-runtime-t767

// #include <algorithm>
// #include <vector>

// let 'n' be a count of given differences
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int numberOfArrays(
        std::vector<int>& diffs_,
        int const lowerLimit_,
        int const upperLimit_
        ) const;
};

int Solution::numberOfArrays(
    std::vector<int>& diffs_,
    int const lowerLimit_,
    int const upperLimit_
) const {
    auto smallestNum{0};
    auto largestNum{0};
    auto currentNum{0};
    auto const limitsRange{upperLimit_ - lowerLimit_};
    auto numsRange{0};
    for(auto const diff: diffs_) {
        currentNum += diff;
        smallestNum = std::min(smallestNum, currentNum);
        largestNum = std::max(largestNum, currentNum);
        numsRange = largestNum - smallestNum; 
        if(numsRange > limitsRange) {
            return 0;
        }
    }
    return limitsRange - numsRange + 1; 
}
