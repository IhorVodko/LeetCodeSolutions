// problem : https://leetcode.com/problems/grid-game/description/
// submission : https://leetcode.com/problems/grid-game/submissions/1515728228
// solution post : https://leetcode.com/problems/grid-game/solutions/6310996/c-modern-readable-code-beats-100-runtime-zhnn

// #include <algorithm>
// #include <limits>
// #include <vector>

// let 'n' be a coungt of columns of parameter 'grid'
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    using Mx = std::vector<std::vector<int>>;
    long long gridGame(Mx const & grid) const {
        auto row1Sum{std::accumulate(grid.at(0).begin(), grid.at(0).end(),
            0LL)};
        auto row2Sum{0LL};
        auto const & row1{grid.at(0)};
        auto const & row2{grid.at(1)};
        auto minSum{std::numeric_limits<long long int>::max()};
        for(auto movesDownIdx{size_t{0}}; movesDownIdx < grid.at(0).size();
            ++movesDownIdx
        ) {
            row1Sum -= row1.at(movesDownIdx);
            minSum = std::min(minSum, std::max(row1Sum, row2Sum));
            row2Sum += row2.at(movesDownIdx);
        }
        return minSum;
    }
};
