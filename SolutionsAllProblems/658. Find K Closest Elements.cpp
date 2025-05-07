// problem : https://leetcode.com/problems/find-k-closest-elements/description/
// submission : https://leetcode.com/problems/find-k-closest-elements/submissions/1627889658
// solution post : https://leetcode.com/problems/find-k-closest-elements/solutions/6723321/
//    c-modern-readable-code-beats-100-runtime-mi9f

// #include <vector>

class Solution {
public:
// let 'n' be a length of the given array
// 'm' - count of the closest numbers given
// time complexity O(log2(n - m))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    std::vector<int> findClosestElements(
        std::vector<int> const & nums_,
        int const numsCount_,
        int const target_
    ) const;
};

std::vector<int> Solution::findClosestElements(
    std::vector<int> const & nums_,
    int const numsCount_,
    int const target_
) const {
    auto const begin{nums_.begin()};
    auto const end{nums_.end()};
    auto left{begin};
    for(auto right{end - numsCount_},
        mid{begin + (end - numsCount_ - begin) / 2}; left < right;
        mid = left + (right - left) / 2
    ) {
        if(target_ - *mid > *(mid + numsCount_) - target_) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return {left, left + numsCount_};
}
