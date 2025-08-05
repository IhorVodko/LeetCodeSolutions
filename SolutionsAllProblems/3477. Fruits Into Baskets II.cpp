// problem : https://leetcode.com/problems/fruits-into-baskets-ii/description
// submission : https://leetcode.com/problems/fruits-into-baskets-ii/submissions/1724798237
// solution post : https://leetcode.com/problems/fruits-into-baskets-ii/solutions/7048683
//    /c-modern-readable-code-beats-100-runtime-uw2a

// #include <vector>

class Solution {
public:
// let 'n' be a count of the given fruit types
// time complexity O(n^2)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    int numOfUnplacedFruits(
        std::vector<int> const & fruits_,
        std::vector<int> & baskets_
    ) const;
};

int Solution::numOfUnplacedFruits(
    std::vector<int> const & fruits_,
    std::vector<int> & baskets_
) const {
    auto unplacedFruits{0};
    for(auto const fruitCount: fruits_) {
        auto isMissed{true};
        for(auto & basketSz: baskets_) {
            if(basketSz >= fruitCount) {
                basketSz = 0;
                isMissed = false;
                break;
            }
        }
        unplacedFruits += isMissed ? 1 : 0;
    }
    return unplacedFruits;
}
