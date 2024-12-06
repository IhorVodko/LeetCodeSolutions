// problem :  https://leetcode.com/problems/maximum-number-of-integers-to-choose-from-a-range-i/description/
// submission : https://leetcode.com/problems/maximum-number-of-integers-to-choose-from-a-range-i/submissions/1471712792
// solution post : https://leetcode.com/problems/maximum-number-of-integers-to-choose-from-a-range-i/solutions/6119214/c-modern-readable-code-beats-100-runtime


// #include <bitset>
// #include <vector>


class Solution {
public:
    // let 'n' be an input length of banned numbers array,
    //   'm' - an inputed maximum number parameter
    // time complexity O(n + m)
    // space complexity O(n)
    // runtime 0 ms, beats 100.00 %
    int maxCount(
        std::vector<int> const & banned,
        int const maxNum,
        int maxSum
    ) const {
        auto notAllowed{std::bitset<10'001>{}};
        for(auto const num: banned) {
            notAllowed.set(num);
        }
        auto numToSelect{0};
        auto numsCount{0};
        for(auto numToSelect{1}; numToSelect <= maxNum; ++numToSelect) {
            if(notAllowed.test(numToSelect) ||
                maxSum - numToSelect < 0 
            ) {
                continue;
            }
            maxSum -= numToSelect;
            ++numsCount;
        }
        return numsCount;
    }
};
