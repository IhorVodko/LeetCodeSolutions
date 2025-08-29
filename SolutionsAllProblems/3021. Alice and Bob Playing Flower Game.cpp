// problem : https://leetcode.com/problems/alice-and-bob-playing-flower-game/description/ 
// submission : https://leetcode.com/problems/alice-and-bob-playing-flower-game/submissions/1752521989
// solution post : https://leetcode.com/problems/alice-and-bob-playing-flower-game/solutions/7135407/
//    c-modern-readable-code-beats-100-runtime-xhif

class Solution {
public:
// let 'n' be a count of filrst line flowers given
// 'm' - second line flowers given
// time complexity O(1)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    long long flowerGame(
        int const firstLineMaxFlowers_,
        int const secondLineMaxFlowers_
    ) const;
};

long long Solution::flowerGame(
    int const firstLineMaxFlowers_,
    int const secondLineMaxFlowers_
) const {
    auto const pairsCount{
        static_cast<long long>(firstLineMaxFlowers_) *
        secondLineMaxFlowers_ /
        2
    };
    return pairsCount;
}
