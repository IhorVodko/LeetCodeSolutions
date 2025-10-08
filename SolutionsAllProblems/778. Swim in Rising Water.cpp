// problem : https://leetcode.com/problems/swim-in-rising-water/description/?envType=daily-question&envId=2025-10-06
// submission : https://leetcode.com/problems/swim-in-rising-water/submissions/1795455037
// solution post : https://leetcode.com/problems/swim-in-rising-water/solutions/7259488/
//    c-modern-readable-code-beats-100-runtime-8gow

// import std;

class Solution {
public:
    using mxT = std::vector<std::vector<int>>;

// let 'n' be the given matrix dimensions size
// time complexity O(n * log(n))
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto swimInWater(mxT & mx_) const -> int;

private:
    using movesT = std::array<std::pair<int, int>, 4>;

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
    inline static int constexpr kSeen{-1};
};

auto Solution::swimInWater(mxT & mx_) const -> int {
    using pqElemT = std::array<int, 3>;

    assert(mx_.size() == mx_.at(0).size() && !mx_.empty());
    auto const rcCnt{std::ssize(mx_)};

    auto cellsPq{std::priority_queue<
        pqElemT,
        std::vector<pqElemT>,
        std::greater<pqElemT>
    >{}};
    cellsPq.emplace(pqElemT{mx_.at(0).at(0), 0, 0});
    auto minTime{0};
    auto const targetCell{rcCnt - 1};
    mx_.at(0).at(0) = kSeen;
    while(!cellsPq.empty()) {
        auto const [currTime, r, c]{cellsPq.top()};
        cellsPq.pop();
        minTime = std::max(minTime, currTime);
        if(r == c && c == targetCell) {
            return minTime;
        }
        for(auto  const [rOffset, cOffset]: kMoves) {
            auto const nextR{r + rOffset};
            auto const nextC{c + cOffset};
            if( 0 <= nextR && nextR < rcCnt &&
                0 <= nextC && nextC < rcCnt &&
                mx_.at(nextR).at(nextC) != kSeen
            ) {
                cellsPq.emplace(pqElemT{
                    mx_.at(nextR).at(nextC),
                    nextR,
                    nextC
                });
                mx_.at(nextR).at(nextC) = kSeen;
            }
        }
    }
    return minTime; 
}
