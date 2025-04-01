// problem : https://leetcode.com/problems/partition-labels/description/
// submission : https://leetcode.com/problems/partition-labels/submissions/1593342784
// solution post : https://leetcode.com/problems/partition-labels/solutions/6604255/
//     c-modern-readable-code-beats-100-runtime-bdr3

// #include <algorithm>
// #include <string>
// #include <vector>

// let 'n' be a length of the given string
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    std::vector<int> partitionLabels(std::string const & str_) const {
        auto chrsLastIdxs{std::vector<int>(26, 0)};
        auto const chrsCount{str_.size()};
        for(auto i{0}; i < chrsCount; ++i) {
            chrsLastIdxs.at(str_[i] - 'a') = i;
        }
        auto partitionEndIdx{0};
        auto partitionStartIdx{0};
        auto partitionSizes{std::vector<int>{}};
        for(auto i{0}; i < chrsCount; ++i) {
            partitionEndIdx = std::max(partitionEndIdx,
                chrsLastIdxs.at(str_[i] - 'a'));
            if(i == partitionEndIdx) {
                partitionSizes.emplace_back(i - partitionStartIdx + 1);
                partitionStartIdx = i + 1;
            }
        }
        return partitionSizes;
    }
};
