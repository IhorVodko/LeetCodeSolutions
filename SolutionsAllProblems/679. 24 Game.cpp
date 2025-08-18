// problem : https://leetcode.com/problems/24-game/description
// submission : https://leetcode.com/problems/24-game/submissions/1739764694
// solution post : https://leetcode.com/problems/24-game/solutions/7095952/
//    c-modern-readable-code-optimal-time-comp-2oib

// #include <cmath>
// #include <ranges>
// #include <vector>

namespace Util {
    inline auto constexpr kTargetVal{24.0};
    inline auto constexpr kTolerance{1e-9};
}

class Solution {
public:
// let 'n' be a count of cards given (at our problem it is fixed at 4)
// time complexity O(n^3 * 3^(n - 1) * n! * (n - 1)!)
// space complexity O(n^2)
// runtime 30 ms, beats 42.29 %
    [[nodiscard]]
    bool judgePoint24(std::vector<int> const & cardVals_) const;
private:
    [[nodiscard]]
    bool Is24Reachable(std::vector<double> cardVals_) const;
    [[nodiscard]]
    std::vector<double> generateCardVals(
        double const cardVal1_,
        double const cardVal2_
    ) const;
};

bool Solution::judgePoint24(std::vector<int> const & cardVals_) const {
    auto cardVals{std::vector<double>{cardVals_.begin(), cardVals_.end()}}; 
    return Is24Reachable(cardVals);
}

bool Solution::Is24Reachable(std::vector<double> cardVals_) const {
    namespace views = std::views;
    using namespace Util;
    auto const cardsSz{cardVals_.size()};
    if(cardsSz == 1) {
        auto const achivedVal{cardVals_.at(0)};
        auto const is24Reachable{
            std::fabs(achivedVal - kTargetVal) <
            kTolerance};
        return is24Reachable;
    }
    for(auto const cardIdx1: views::iota(0u, cardsSz)) {
        for(auto const cardIdx2: views::iota(cardIdx1 + 1, cardsSz)) {
            auto nextCardVals{std::vector<double>{}};
            for(auto const cardIdx3: views::iota(0u, cardsSz)) {
                if(cardIdx3 != cardIdx1 && cardIdx3 != cardIdx2) {
                    auto const cardVal{cardVals_.at(cardIdx3)};
                    nextCardVals.emplace_back(cardVal);
                }
            }
            auto const cardVal1{cardVals_.at(cardIdx1)};
            auto const cardVal2{cardVals_.at(cardIdx2)};
            for(auto const newCardVal: generateCardVals(cardVal1, cardVal2)) {
                nextCardVals.emplace_back(newCardVal);
                if(Is24Reachable(nextCardVals)) {
                    return true;
                }
                nextCardVals.pop_back();
            }
        }
    }
    return false;
}

std::vector<double> Solution::generateCardVals(
    double const cardVal1_,
    double const cardVal2_
) const {
    auto newCardVal{std::vector<double>{
        cardVal1_ + cardVal2_,
        cardVal1_ - cardVal2_,
        cardVal2_ - cardVal1_,
        cardVal1_ * cardVal2_}};
    if(cardVal1_) {
        newCardVal.emplace_back(cardVal2_ / cardVal1_);
    }
    if(cardVal2_) {
        newCardVal.emplace_back(cardVal1_ / cardVal2_);
    }
    return newCardVal;
}
