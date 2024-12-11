// problem : https://leetcode.com/problems/maximum-beauty-of-an-array-after-applying-operation/description/
// submission : https://leetcode.com/problems/maximum-beauty-of-an-array-after-applying-operation/submissions/1476447164
// solution post : https://leetcode.com/problems/maximum-beauty-of-an-array-after-applying-operation/solutions/6137254/c-modern-readable-code/


// #include <algorithm>
// #include <iterator>
// #include <vector>


class Solution {
public:
    // let 'n' be a 'nums' array length
    // time complexity O(n*log(n))
    // space complexity O(std::sort)
    // runtime 43 ms, beats 83.67 %
    int maximumBeauty(
        std::vector<int> & nums,
        int const diff
    ) const {
        std:sort(nums.begin(), nums.end());
        auto const maxDiff{2 * diff} ;
        auto maxBeautyLength{long{1}};
        auto sequenceStart{nums.cbegin()};
        for(auto num{nums.cbegin()}, end{nums.cend()}; num < end; ++num) {
            if(*num - *sequenceStart <= maxDiff) {
                continue;
            }
            maxBeautyLength = std::max(std::distance(sequenceStart, num),
                maxBeautyLength);
            while (*num - *++sequenceStart > maxDiff) {}
        }
        return std::max(maxBeautyLength,
            std::distance(sequenceStart, nums.cend()));
    }
};
