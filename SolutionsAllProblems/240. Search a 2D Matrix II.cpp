// problem : https://leetcode.com/problems/search-a-2d-matrix-ii/description/
// submission : https://leetcode.com/problems/search-a-2d-matrix-ii/submissions/1717324450
// solution post : https://leetcode.com/problems/search-a-2d-matrix-ii/solutions/7025303
//    /c-modern-readable-code-optimal-time-comp-jlm9

// #include <algorithm>
// #include <ranges>
// #include <vector>

class Solution {
public:
    using mxT = std::vector<std::vector<int>>;
// let 'r' - be a columns' count of the given matrix
// 'c' - rows' count of the given matrix
// time complexity O(log2(r) * log2(c))
// space complexity O(1)
// runtime 54 ms, beats 54.28 %
    [[nodiscard]]
    bool searchMatrix(
        mxT const & mx_,
        int const target_
    ) const;
};

bool Solution::searchMatrix(
    mxT const & mx_,
    int target_
) const {
    namespace ranges = std::ranges;
    auto const ubIt{ranges::upper_bound(
        mx_,
        target_,
        std::less{},
        [] (auto const & row_) {return row_.back();}
    )};
    if(ubIt != mx_.begin() && (ubIt - 1)->back() == target_) {
        return true;
    }
    auto const lbIt{ranges::lower_bound(
        ranges::subrange{ubIt, mx_.end()},
        target_,
        std::less{},
        [] (auto const & row_) {return row_.front();}
    )};
    if(lbIt != mx_.end() && lbIt->front() == target_) {
        return true;
    }
    for(auto const & row: ranges::subrange(ubIt, lbIt)) {
        if(ranges::binary_search(row, target_)) {
            return true;
        }
    }
    return false;

}
