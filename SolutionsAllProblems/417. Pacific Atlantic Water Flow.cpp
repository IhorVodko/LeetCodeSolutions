// problem : https://leetcode.com/problems/pacific-atlantic-water-flow/description
// submission : https://leetcode.com/problems/pacific-atlantic-water-flow/submissions/1794426961
// solution post : https://leetcode.com/problems/pacific-atlantic-water-flow/solutions/7256807/
//    c-modern-readable-code-beats-100-runtime-0hkk

// import std;

class Solution {
public:
    using mxT = std::vector<std::vector<int>>;
    using RcT = std::vector<int>;

// let 'n' be the number of the given heights 
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto pacificAtlantic(std::vector<RcT> const & heights_) const -> mxT;

private:
    using maxRowColSz = std::integral_constant<int, 200>;
    using maskT =
        std::array<std::bitset<maxRowColSz::value>, maxRowColSz::value>;
    using cellT = std::pair<int, int>;
    using movesT = std::array<std::pair<int, int>, 4>;

    [[nodiscard]]
    auto DoBfs(
        std::queue<cellT> & cellsQ,
        std::vector<RcT> const & heights_
    ) const -> maskT;

    inline static bool const kIsFastIO{
        [] () {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return true;
        } ()
    };
    inline static movesT constexpr kMoves{{
        {-1, 0}, {0, -1}, {0, 1}, {1, 0}
    }};
};

auto Solution::pacificAtlantic(std::vector<RcT> const & heights_) const -> mxT {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    if(heights_.empty() || heights_.at(0).empty()) {
        return {};
    }
    auto const rCnt{std::ssize(heights_)};
    auto cCnt{std::ssize(heights_.at(0))};
    auto pacificQ{std::queue<cellT>{}};
    auto atlanticQ{std::queue<cellT>{}};
    for(auto const r: vs::iota(0, rCnt)) {
        pacificQ.emplace(r, 0);
        atlanticQ.emplace(r, cCnt - 1);
    }
    for(auto const c: vs::iota(0, cCnt)) {
        pacificQ.emplace(0, c);
        atlanticQ.emplace(rCnt - 1, c);
    }
    auto const pacificMask{DoBfs(pacificQ, heights_)};
    auto const atlanticMask{DoBfs(atlanticQ, heights_)};
    auto intersectionCells{std::vector<std::vector<int>>{}};
    intersectionCells.reserve(rCnt * cCnt);
    for(auto const r: vs::iota(0, rCnt)) {
        for(auto const c: vs::iota(0, cCnt)) {
            if(pacificMask.at(r).test(c) && atlanticMask.at(r).test(c)) {
                intersectionCells.emplace_back(std::initializer_list{r, c});
            }
        }
    }
    return intersectionCells;
}

auto Solution::DoBfs(
    std::queue<cellT> & cellsQ,
    std::vector<RcT> const & heights_
) const -> maskT {
    auto const rCnt{std::ssize(heights_)};
    auto cCnt{std::ssize(heights_.at(0))};
    auto visitedMask{maskT{}};
    while(!cellsQ.empty()) {
        auto const [currR, currC]{cellsQ.front()};
        cellsQ.pop();
        visitedMask.at(currR).set(currC);
        for(auto const [rOffset, yOffset]: kMoves) {
            auto const nextR{currR + rOffset};
            auto const nextC{currC + yOffset};
            if( nextR < 0 || nextR >= rCnt ||
                nextC < 0 || nextC >= cCnt ||
                visitedMask.at(nextR).test(nextC) ||
                heights_.at(nextR).at(nextC) < heights_.at(currR).at(currC)
            ) {
                continue;
            }
            cellsQ.emplace(nextR, nextC);
        }
    }
    return visitedMask;
}
