// problem : https://leetcode.com/problems/find-minimum-time-to-reach-last-room-i/description/
// submission : https://leetcode.com/problems/find-minimum-time-to-reach-last-room-i/submissions/1627995216
// solution post : https://leetcode.com/problems/find-minimum-time-to-reach-last-room-i/solutions/6723695/
//    c-modern-readable-code-beats-98-runtime-gmetv

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
    using qValueT = std::pair<RoomT, int>;
// let 'r' be a row count of the given grid
// 'c' - column count
// time complexity O(r * c * log2(r * c));
// space complexity O(r * c)
// runtime 11 ms, beats 98.02 %
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
    auto cmp{[] (auto const & lhs_, auto const & rhs_) {
        return lhs_.second > rhs_.second; }};
    auto roomsAndTimes{std::priority_queue<
        qValueT, std::vector<qValueT>, decltype(cmp)>{cmp}};
    roomsAndTimes.emplace(RoomT{0, 0}, 0);
    auto minTimes{Arr2T(rCounts, 
        std::vector<int>(cCounts, std::numeric_limits<int>::max()))};
    minTimes[0][0] = 0;
    while(!roomsAndTimes.empty()) {
        auto const [roomCurr, _]{roomsAndTimes.top()};
        auto const [rCurr, cCurr]{roomCurr};
        roomsAndTimes.pop();
        for(auto const [rOffset, cOffset]: kMoves) {
            auto const rNext{rCurr + rOffset}; 
            auto const cNext{cCurr + cOffset};
            if(!IsRoomInTheDungeon({rNext, cNext}, moveTime_)) {
                continue;
            }
            auto const timeNew{
                std::max(minTimes[rCurr][cCurr], moveTime_[rNext][cNext]) + 1};
            auto & timeCurr{minTimes[rNext][cNext]};
            if(timeCurr > timeNew) {
                roomsAndTimes.emplace(RoomT{rNext, cNext}, timeNew);
                timeCurr = timeNew;
            }
        }
    }
    return minTimes[rCounts - 1][cCounts - 1];
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
