// problem : https://leetcode.com/problems/max-chunks-to-make-sorted/description/
// submission : https://leetcode.com/problems/max-chunks-to-make-sorted/submissions/1483012635
// solution post : https://leetcode.com/problems/max-chunks-to-make-sorted/solutions/6164526/c-modern-readable-code-beats-100-runtime-ffih


// #include <algorithm>
// #include <vector>


class Solution {
public:
    // let 'n' be a parameter 'arr' length
    // time complexity O(n)
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
    int maxChunksToSorted(std::vector<int> const & arr) const {
        auto chunks{0};
        auto numMax{0};
        for(auto num{arr.cbegin()}, end{arr.cend()}; num < end; ++num) {
            numMax = std::max(*num, numMax);
            if(numMax == std::distance(arr.cbegin(), num)) {
                ++chunks;
            }
        }
        return chunks;
    }
};
