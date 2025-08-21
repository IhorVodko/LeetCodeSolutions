// problem : https://leetcode.com/problems/count-square-submatrices-with-all-ones/description
// submission : https://leetcode.com/problems/count-square-submatrices-with-all-ones/submissions/1743234715
// solution post : https://leetcode.com/problems/count-square-submatrices-with-all-ones/solutions/7106635/
//    c-modern-readable-code-optimal-time-comp-u28v

// #include <algorithms>
// #include <ranges>
// #include <vector>

class Solution {
public:
    using mxT = std::vector<std::vector<int>>;
// let 'r' by 'c' be a size of the given matrix
// time complexity O(r * c)
// space complexity O(c)
// runtime 5 ms, beats 64.80 %
    [[nodiscard]] 
    int countSquares(vector<vector<int>> & mx_) const;
};

int Solution::countSquares(vector<vector<int>> & mx_) const {
    namespace views = std::views;
    auto const rowCount{mx_.size()};
    auto const colCount{mx_.at(0).size()};
    auto mxCountTotal{0};
    auto prevMxCount{0};
    auto mxCounts{std::vector<int>(colCount + 1, 0)};
    for(auto const r: views::iota(1u, rowCount + 1)) {
        for(auto const c: views::iota(1u, colCount + 1)) {
            if(mx_.at(r - 1).at(c - 1) == 1) {
                auto tempMxCount{mxCounts.at(c)};
                mxCounts.at(c) =
                    1 +
                    std::min(
                        prevMxCount,
                        std::min(mxCounts.at(c - 1), mxCounts.at(c))
                    )
                ;
                prevMxCount = tempMxCount;
                mxCountTotal += mxCounts.at(c);
            } else {
                mxCounts.at(c) = 0;
            }
        }
    }
    return mxCountTotal;
}
