// problem : https://leetcode.com/problems/fruits-into-baskets-iii/description
// submission : https://leetcode.com/problems/fruits-into-baskets-iii/submissions/1725576658
// solution post : https://leetcode.com/problems/fruits-into-baskets-iii/solutions/7051028/
//    c-modern-readable-code-by-cyberartist-qyh5

// #include <algorithm>
// #include <ranges>
// #include <vector>

#include <ranges>

class Solution {
public:
// let 'n' be a count of the given fruit types
// time complexity O(n * sqrt(n))
// space complexity O(sqrt(n))
// runtime 1330 ms, beats 5.01 %
// current approack is a square root decomposition but the most optimal approuch for this problem
// is a segment tree and binary search
    int numOfUnplacedFruits(
        std::vector<int> const & fruits_,
        std::vector<int> & baskets_
    ) const;
};

int Solution::numOfUnplacedFruits(
    std::vector<int> const & fruits_,
    std::vector<int> & baskets_
) const {
    namespace views = std::views;
    auto const basketsSz{baskets_.size()};
    auto const sectionSz{static_cast<size_t>(std::sqrt(basketsSz))};
    auto const sectionCount{(basketsSz + sectionSz - 1) / sectionSz};
    auto unplacedFruits{0};
    auto maxBasketsPerSection{std::vector<int>(sectionCount)};
    for(auto const idx: views::iota(0u, basketsSz)) {
        auto sectionIdx{idx / sectionSz};
        auto & maxBasket{maxBasketsPerSection.at(sectionIdx)};
        auto const currBasket{baskets_.at(idx)};
        maxBasket = std::max(maxBasket, currBasket);
    }
    for(auto const fruit: fruits_) {
        auto isFuitLeft{true};
        for(auto const section: views::iota(0u, sectionCount)) {
            if(maxBasketsPerSection.at(section) < fruit) {
                continue;
            }
            auto isFuitUnplaced{true};
            maxBasketsPerSection.at(section) = 0;
            for(auto const sectionIdx: views::iota(0u, sectionSz)) {
                auto basketIdx{section * sectionSz + sectionIdx};
                if( basketIdx < basketsSz && 
                    baskets_.at(basketIdx) >= fruit &&
                    isFuitUnplaced
                ) {
                    baskets_.at(basketIdx) = 0;
                    isFuitUnplaced = false;   
                }
                if(basketIdx < basketsSz) {
                    maxBasketsPerSection.at(section) = std::max(
                        maxBasketsPerSection.at(section),
                        baskets_.at(basketIdx));
                }
            }
            isFuitLeft = false;
            break;
        }
        unplacedFruits += isFuitLeft ? 1 : 0;
    }
    return unplacedFruits;
}
