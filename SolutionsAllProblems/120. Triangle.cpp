// problem : https://leetcode.com/problems/triangle/description
// submission : https://leetcode.com/problems/triangle/submissions/1782311190
// solution post : https://leetcode.com/problems/triangle/solutions/7223050/
//    c-modern-readable-code-beats-100-runtime-83sr

// import std;

// let 'n' be a height of the given triangle
// time complexity O(n^2)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %

class Solution {
public:
    using triangleT = std::vector<std::vector<int>>;

// let 'n' be a height of the given triangle
// time complexity O(n^2)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto minimumTotal(triangleT const & triangle_) const -> int;
};

auto Solution::minimumTotal(triangleT const & triangle_) const -> int {
    namespace views = std::views;
    using mxT = std::vector<std::vector<int>>;
    using intT = std::numeric_limits<int>;

    if(triangle_.empty()) {
        return intT::max();
    }
    if(triangle_.size() == 1) {
        return triangle_.at(0).at(0);
    }
    auto const rowsCnt{triangle_.size()};
    auto const colsCnt{triangle_.at(rowsCnt - 1).size()};
    auto minSumsPrev{std::vector<int>(colsCnt, intT::max())};
    minSumsPrev.at(0) = triangle_.at(0).at(0);
    auto minSumsCurr{std::vector<int>(colsCnt, intT::max())};
    auto minSum{intT::max()};
    for(auto const rIdx: views::iota(1u, rowsCnt)) {
        auto const & triangleRow{triangle_.at(rIdx)};
        auto const triangleRowSz{triangleRow.size()};
        for(auto const cIdx: views::iota(0u, triangleRowSz)) {
            auto minSumPrevRow{std::min(
                cIdx >= 1 ? minSumsPrev.at(cIdx - 1) : intT::max(),
                cIdx + 1 < triangleRowSz ? minSumsPrev.at(cIdx) : intT::max()
            )};
            auto & currMinSum{minSumsCurr.at(cIdx)}; 
            currMinSum = minSumPrevRow + triangleRow.at(cIdx); 
            if(rIdx + 1 == rowsCnt) {
                minSum = std::min(minSum, currMinSum);
            }
        }
        minSumsPrev = minSumsCurr;
        ranges::fill(minSumsCurr, intT::max());
    }
    return minSum;
}
