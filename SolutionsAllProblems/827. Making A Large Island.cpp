// problem : https://leetcode.com/problems/making-a-large-island/description/
// submission : https://leetcode.com/problems/making-a-large-island/submissions/1526664101
// solution post : https://leetcode.com/problems/making-a-large-island/solutions/6353303/c-modern-readable-code-optimal-time-comp-rjgs

// #include <algorithm>
// #include <queue>
// #include <vector>
// #include <unordered_map>
// #include <unordered_set>

// let 'n' be a length of the given grid
// time complexity O(n)
// space complexity O(n)
// runtime 323 ms, beats 28.73 %
namespace Utility{
    auto constexpr waterCell{0};
    auto constexpr islandCell{1}; 
}

class Solution {
public:
    template<typename T>
    using Mx = std::vector<std::vector<T>>;
    int largestIsland(Mx<int> & grid) const;
    Solution(): 
        moves{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}
    {}
private:
    bool IsValidCell(
        int const r,
        int const c,
        int const gridSz 
    ) const;
    std::unordered_map<int, int> CalculateIslandAreas(Mx<int> & grid) const;
    int CalculateIslandArea(
        Mx<int> & grid,
        int const r,
        int const c,
        int const islandNum
    ) const;
    int calculateMaxIslandArea(
        Mx<int> const & grid,
        std::unordered_map<int, int> const & islandToArea
    ) const;
    int CalculateNewlyFormedIslandArea(
        Mx<int> const & grid,
        int const r,
        int const c,
        std::unordered_map<int, int> const & islandToArea
    ) const;
    std::vector<std::pair<int, int>> moves;
};

int Solution::largestIsland(Mx<int> & grid) const {
    using namespace  Utility;
    if(grid.size() == 1) {
        return 1;
    }
    auto const gridSz{grid.size()};
    auto islandToArea{CalculateIslandAreas(grid)};
    if(islandToArea.empty()) {
        return 1;
    }
    if(islandToArea.size() == 1) {
        auto const area{islandToArea.begin()->second};
        return area == gridSz * gridSz ? area : area + 1;
    }
    return calculateMaxIslandArea(grid, islandToArea);
}

bool Solution::IsValidCell(
    int const r,
    int const c,
    int const gridSz 
) const {
    return 0 <= r && r < gridSz && 0 <= c && c < gridSz;
}
std::unordered_map<int, int> Solution::CalculateIslandAreas(
    Mx<int> & grid
) const {
    using namespace Utility;
    auto islandToArea{std::unordered_map<int, int>{}};
    auto const gridSz{grid.size()};
    auto islandNum{-1};
    for(auto r{0}; r < gridSz; ++r) {
        for(auto c{0}; c < gridSz; ++c) {
            if(grid.at(r).at(c ) != islandCell) {
                continue;
            }
            islandNum = islandToArea.size() + 2;
            islandToArea[islandNum] = CalculateIslandArea(grid, r, c,
                islandNum);
        }
    } 
    return islandToArea;
}
int Solution::CalculateIslandArea(
    Mx<int> & grid,
    int const r,
    int const c,
    int const islandNum
) const {
    using namespace Utility;
    auto const gridSz{grid.size()};
    auto cells{std::queue<std::pair<int, int>>{}};
    cells.push({r, c});
    grid.at(r).at(c) = islandNum;
    auto islandArea{0};
    while(!cells.empty()) {
        auto const [r, c]{cells.front()};
        cells.pop();
        ++islandArea;
        for(auto const & move: moves) {
            auto rNext{r + move.first};
            auto cNext{c + move.second};
            if(!IsValidCell(rNext, cNext, gridSz) || 
                grid.at(rNext).at(cNext) != islandCell
            ) {
                continue;
            }
            grid.at(rNext).at(cNext) = islandNum;
            cells.push({rNext, cNext});
        }
    }
    return islandArea;
}
int Solution::calculateMaxIslandArea(
    Mx<int> const & grid,
    std::unordered_map<int, int> const & islandToArea
) const {
    using namespace Utility;
    auto maxIslandArea{-1};
    auto const gridSz{grid.size()};
    for(auto r{0}; r < gridSz; ++r) {
        for(auto c{0}; c < gridSz; ++c) {
            if(grid.at(r).at(c) != waterCell) {
                continue;
            }
            maxIslandArea = std::max(maxIslandArea,
                CalculateNewlyFormedIslandArea(grid, r, c, islandToArea));
        }
    }
    return maxIslandArea + 1;
}
int Solution::CalculateNewlyFormedIslandArea(
    Mx<int> const & grid,
    int const r,
    int const c,
    std::unordered_map<int, int> const & islandToArea
) const {
    using namespace Utility;
    auto islandArea{0};
    auto visitedIslandNums{std::unordered_set<int>{}};
    auto const gridSz{grid.size()};
    for(auto const & move: moves) {
        auto const rNext{r + move.first};
        auto const cNext{c + move.second};
        if(!IsValidCell(rNext, cNext, gridSz) ||
            grid.at(rNext).at(cNext) == waterCell ||
            visitedIslandNums.contains(grid.at(rNext).at(cNext))
        ) {
            continue;
        }
        visitedIslandNums.emplace(grid.at(rNext).at(cNext));
        islandArea += islandToArea.at(grid.at(rNext).at(cNext));
    }
    return islandArea;
}
