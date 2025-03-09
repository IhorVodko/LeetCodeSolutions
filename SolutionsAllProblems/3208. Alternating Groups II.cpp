// problem : https://leetcode.com/problems/alternating-groups-ii/description/
// submission : https://leetcode.com/problems/alternating-groups-ii/submissions/1568503338
// solution post : https://leetcode.com/problems/alternating-groups-ii/solutions/6518648/
//     c-modern-readable-code-beats-98-runtime-vniic

// #include <vector>

// let 'a' be a length of the given array
// 'g' - required group length
// time complexity O(a + g)
// space complexity O(1)
// runtime 53 ms, beats 97.68 %
class Solution {
public:
    int numberOfAlternatingGroups(
        std::vector<int> const & colors_,
        int const groupSz_
    ) const {
        auto const colorsSz{colors_.size()};
        auto groupsCount{0};
        auto currGroupSz{1};
        auto prevColor{colors_.front()};
        for(auto i{1}; i < colorsSz + groupSz_ - 1; ++i) {
            auto const normilizedI{i % colorsSz};
            if(colors_[normilizedI] == prevColor) {
                currGroupSz = 1;
                prevColor = colors_[normilizedI];
                continue;
            }
            groupsCount += ++currGroupSz >= groupSz_ ? 1 : 0;
            prevColor = colors_[normilizedI];
        }
        return groupsCount;
    }
};
