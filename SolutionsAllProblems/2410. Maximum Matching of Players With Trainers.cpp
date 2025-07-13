// problem : https://leetcode.com/problems/maximum-matching-of-players-with-trainers/description
// submission : https://leetcode.com/problems/maximum-matching-of-players-with-trainers/submissions/1696560359
// solution post : https://leetcode.com/problems/maximum-matching-of-players-with-trainers/solutions/6954154/
//    c-modern-readable-code-optimal-time-comp-d7i3

// #include <algorithm>
// #include <vector>

class Solution {
public:
// let 'p' be a count of the given players
// let 't' - of the given trainers
// time complexity O(p * log2(p) + t * log2(t))
// space complexity O(sort)
// runtime 29 ms, beats 55.28 %
    [[nodiscard]]
    int matchPlayersAndTrainers(
        std::vector<int> & playerVals_,
        std::vector<int> & trainerVals_
    ) const;
};

int Solution::matchPlayersAndTrainers(
    std::vector<int> & playerVals_,
    std::vector<int> & trainerVals_
) const {
    namespace ranges = std::ranges;
    ranges::sort(playerVals_);
    ranges::sort(trainerVals_);
    auto matchCounter{0};
    for(
        auto playerVal{playerVals_.cbegin()}, playerValsEnd{playerVals_.cend()},
            trainerVal{trainerVals_.cbegin()}, trainerValsEnd{trainerVals_.cend()};
        playerVal < playerValsEnd && trainerVal < trainerValsEnd;
        ++trainerVal
    ) {
        if(*playerVal <= *trainerVal) {
            ++matchCounter;
            ++playerVal;
        }
    }
    return matchCounter;
}
