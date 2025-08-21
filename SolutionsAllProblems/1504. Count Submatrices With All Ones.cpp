// problem : https://leetcode.com/problems/count-submatrices-with-all-ones/description
// submission : https://leetcode.com/problems/count-submatrices-with-all-ones/submissions/1743291629
// solution post : https://leetcode.com/problems/count-submatrices-with-all-ones/solutions/7106797/
//    c-modern-readable-code-optimal-time-comp-0o6h

// #include <ranges>
// #include <stack>
// #include <vector>

class Solution {
public:
    using mxT = std::vector<std::vector<int>>;
// let 'c' by 'r'  be a size of the given matrix
// time complexity O(r * c)
// space complexity O(c)
// runtime 18 ms, beats 35.73 %
    [[nodiscard]]
    int numSubmat(mxT const & mx_) const;
};

int Solution::numSubmat(mxT const & mx_) const {
    namespace views = std::views;
    auto const cols{std::ssize(mx_.at(0))};
    auto heights{std::vector<int>(cols, 0)};
    auto submxCountTotal{0};
    for(auto const & row: mx_) {
        for(auto const cIdx: views::iota(0, cols)) {
            heights.at(cIdx) = (row.at(cIdx) == 0) ? 0 : heights.at(cIdx) + 1;
        }
        auto stck{std::stack<std::array<int, 3>>{}};
        stck.emplace(std::array{-1, 0, -1});
        for(auto const cIdx: views::iota(0, cols)) {
            auto const height{heights.at(cIdx)};
            while(!stck.empty() && stck.top().at(2) >= height) {
                stck.pop();
            }
            if(stck.empty()) {
                continue;
            }
            auto const & stckTop{stck.top()};
            auto const prevCIdx{stckTop.at(0)};
            auto const prevSubmxCount{stckTop.at(1)};
            auto const currSubmxCount{(cIdx - prevCIdx) * height};
            auto const submxCount{prevSubmxCount + currSubmxCount};
            stck.emplace(std::array{cIdx, submxCount, height});
            submxCountTotal += submxCount;

        }
    }
    return submxCountTotal;
}
