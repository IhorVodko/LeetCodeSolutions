// problem : https://leetcode.com/problems/fruit-into-baskets/description
// submission : https://leetcode.com/problems/fruit-into-baskets/submissions/1724563441
// solution post : https://leetcode.com/problems/fruit-into-baskets/solutions/7047976/
//    c-modern-readable-code-optimal-time-comp-carj

// #include <algorithm>
// #include <vector>
// #include <unordered_map>

namespace Util {
    inline auto constexpr kMaxCountUniqueFruits{2u};
}

class Solution {
public:
// let 'n' be a count of the given fruits
// time complexity O(n)
// space complexity O(1)
// runtime 35 ms, beats 75.62 %
    [[nodiscard]]
    int totalFruit(std::vector<int> const & fruits_) const;
};

int Solution::totalFruit(std::vector<int> const & fruits_) const {
    using namespace Util;
    auto fruitToCount{std::unordered_map<int, size_t>{}};
    auto maxFruitCount{0u};
    auto const fruitsSz{fruits_.size()};
    for(auto leftIdx{0u}, rightIdx{0u}; rightIdx < fruitsSz; ++rightIdx) {
        auto const currFruit{fruits_.at(rightIdx)};
        ++fruitToCount[currFruit];
        while(fruitToCount.size() > kMaxCountUniqueFruits) {
            auto const leftFruit{fruits_.at(leftIdx)};
            --fruitToCount.at(leftFruit);
            if(fruitToCount.at(leftFruit) == 0) {
                fruitToCount.erase(leftFruit);
            }     
            ++leftIdx;
        }
        auto const currFruitCount{rightIdx - leftIdx + 1};
        maxFruitCount = std::max(maxFruitCount, currFruitCount);
    }
    return maxFruitCount;
}
