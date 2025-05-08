// problem : https://leetcode.com/problems/find-minimum-time-to-reach-last-room-ii/description/
// submission : https://leetcode.com/problems/find-minimum-time-to-reach-last-room-ii/submissions/1628693687
// solution post : https://leetcode.com/problems/find-minimum-time-to-reach-last-room-ii/solutions/6726082/
//    c-modern-readable-code-optimal-time-comp-94bs

// #include <algorithm>
// #include <queue>
// #include <utility>
// #include <vector>

namespace Utility {
    auto constexpr kMoves{std::array<std::pair<int, int>, 4>{{
        {-1, 0}, {0, -1}, {1, 0}, {0, 1}
    }}};
}

class Solution {
public:
    using Arr2T = std::vector<std::vector<int>>;
    using RoomT = std::pair<int, int>;
// let 'r' be a row count of the given grid
// 'c' - column count
// time complexity O(r * c * log2(r * c))
// space complexity O(r * c)
// runtime 266 ms, beats 69.83 %
    int minTimeToReach(Arr2T const & moveTime_) const;
private:
    bool IsRoomInTheDungeon(
        RoomT const & cell_,
        Arr2T const & grid_
    ) const; 
};

int Solution::minTimeToReach(Arr2T const & moveTime_) const {
    using namespace Utility;
    auto const rCounts{moveTime_.size()};
    auto const cCounts{moveTime_.at(0).size()};
    auto const rTarget{rCounts - 1};
    auto const cTarget{cCounts - 1}; 
    auto minTimes{Arr2T(rCounts,
        std::vector<int>(cCounts, std::numeric_limits<int>::max()))};
    minTimes[0][0] = 0;
    auto cmp{[&] (RoomT const & lhs_, RoomT const & rhs_) {
        return minTimes[lhs_.first][lhs_.second] >
            minTimes[rhs_.first][rhs_.second]; }};
    auto roomsAndTimes{std::priority_queue<
        RoomT, std::vector<RoomT>, decltype(cmp)>{cmp}};
    roomsAndTimes.emplace(0, 0);
    while(!roomsAndTimes.empty()) {
        auto const [rCurr, cCurr]{roomsAndTimes.top()};
        if(rCurr == rTarget && cCurr == cTarget) {
            return minTimes[rCurr][cCurr];
        }
        roomsAndTimes.pop();
        for(auto const [rOffset, cOffset]: kMoves) {
            auto const rNext{rCurr + rOffset}; 
            auto const cNext{cCurr + cOffset};
            if(!IsRoomInTheDungeon({rNext, cNext}, moveTime_)) {
                continue;
            }
            auto const timeNew{
                std::max(minTimes[rCurr][cCurr], moveTime_[rNext][cNext]) +
                (rCurr + cCurr) % 2 + 1};
            auto & timeCurr{minTimes[rNext][cNext]};
            if(timeCurr > timeNew) {
                timeCurr = timeNew;
                roomsAndTimes.emplace(rNext, cNext);
            }
        }
    }
    return -1;
}

bool Solution::IsRoomInTheDungeon(
    RoomT const & cell_,
    Arr2T const & grid_
) const {
    auto const [r, c]{cell_};
    auto const rCounts{grid_.size()};
    auto const cCounts{grid_.at(0).size()};
    return 0 <= r && r < rCounts && 0 <= c && c < cCounts; 
}
