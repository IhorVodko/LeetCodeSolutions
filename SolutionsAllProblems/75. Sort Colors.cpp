// problem : https://leetcode.com/problems/sort-colors/description/
// submission : https://leetcode.com/problems/sort-colors/submissions/1638466608
// solution post : https://leetcode.com/problems/sort-colors/solutions/6760317/
//    c-modern-readable-code-beats-100-by-cybe-zwc8

// #include <vector>

namespace Utility {
    auto constexpr kRed{0};
    auto constexpr kWhite{1};
    auto constexpr kBlue{2};
}

class Solution {
public:
// let 'n' be a length of the given array
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    void sortColors(std::vector<int> & nums_) const;
};

void Solution::sortColors(std::vector<int> & nums_) const {
    using namespace Utility;
    auto const begin{nums_.begin()};
    auto const end{nums_.end()};
    auto redIt{begin};
    auto readerIt{begin};
    auto blueIt{end - 1};
    while(readerIt <= blueIt) {
        if(*readerIt == kRed) {
            std::swap(*redIt++, *readerIt++);
        } else if(*readerIt == kBlue) {
            std::swap(*readerIt, *blueIt--);
        } else {
            ++readerIt;
        }
    }
 }
