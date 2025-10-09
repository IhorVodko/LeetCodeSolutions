// problem : https://leetcode.com/problems/successful-pairs-of-spells-and-potions/description/
// submission : https://leetcode.com/problems/successful-pairs-of-spells-and-potions/submissions/1796521982
// solution post : https://leetcode.com/problems/successful-pairs-of-spells-and-potions/solutions/7262070/
//    c-modern-readable-code-optimal-time-comp-1mz3

// import std;

class Solution {
public:
// let 'p' be the number of the given potions
// 's' - of the given spells
// time complexity O((p + s) * log(p))
// space complexity O(log(p))
// runtime 35 ms, beats 95.03 %
    [[nodiscard]]
    auto successfulPairs(
        std::vector<int> & spells_,
        std::vector<int> & potions_,
        long long success_
    ) const -> std::vector<int>;

private:
    inline static bool const kIsFastIO{
        [] () {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return true;
        } ()
    };
};

auto Solution::successfulPairs(
    std::vector<int> & spells_,
    std::vector<int> & potions_,
    long long success_
) const -> std::vector<int> {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto const spellsSz{std::ssize(spells_)};
    auto const potionsSz{std::ssize(potions_)};
    auto pairCnts{std::vector<int>(spellsSz, -1)};
    rngs::sort(potions_);
    auto const minPotion{potions_.at(0)};
    auto const maxPotion{potions_.at(potionsSz - 1)};
    auto const potionsEnd{potions_.cend()};
    for(auto const idx: vs::iota(0, spellsSz)) {
        auto const spell{spells_.at(idx)};
        auto lowerBound{success_ / spell};
        if(success_ % spell != 0 && success_ > spell) {
            ++lowerBound;
        }
        if(lowerBound <= minPotion) {
            pairCnts.at(idx) = potionsSz;
        } else if(lowerBound > maxPotion) {
            pairCnts.at(idx) = 0;
        } else {
            auto const lowerBoundIt{rngs::lower_bound(potions_, lowerBound)};
            auto const validPotionsCnt{potionsEnd - lowerBoundIt};
            pairCnts.at(idx) = validPotionsCnt;
        }
    }
    return pairCnts;
}
