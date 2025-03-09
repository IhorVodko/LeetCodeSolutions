// problem : https://leetcode.com/problems/minimum-recolors-to-get-k-consecutive-black-blocks/description/
// submission : https://leetcode.com/problems/minimum-recolors-to-get-k-consecutive-black-blocks/submissions/1567347323
// solution post : https://leetcode.com/problems/minimum-recolors-to-get-k-consecutive-black-blocks/solutions/6518411/
//     c-modern-readable-code-beats-100-runtime-wi2k

// #include <algorithm>
// #include <string>

// let 'n' be a length of the given array
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int minimumRecolors(
        std::string const blocks_,
        int const k_
    ) const {
        auto currWhiteCount{size_t{0}};
        auto beginCharIt{blocks_.begin()};
        auto endCharIt{blocks_.begin()};
        while(endCharIt - beginCharIt < k_) {
            if(*endCharIt == 'W') {
                ++currWhiteCount;
            }
            ++endCharIt;
        }
        auto minWhiteCount{currWhiteCount};
        for(auto end{blocks_.end()}; endCharIt < end; ++beginCharIt,
            ++endCharIt
        ) {
            if(*beginCharIt == 'W' && *endCharIt == 'B') {
                minWhiteCount = std::min(minWhiteCount, --currWhiteCount);
            } else if(*beginCharIt == 'B' && *endCharIt == 'W') {
                minWhiteCount  = std::min(minWhiteCount, ++currWhiteCount);
            }
        }
        return minWhiteCount;
    }
};
