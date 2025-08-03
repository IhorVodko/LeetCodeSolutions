// problem : https://leetcode.com/problems/maximum-fruits-harvested-after-at-most-k-steps/description
// submission : https://leetcode.com/problems/maximum-fruits-harvested-after-at-most-k-steps/submissions/1722276687
// solution post : https://leetcode.com/problems/maximum-fruits-harvested-after-at-most-k-steps/solutions/7040761/
//    c-modern-readable-code-beats-100-runtime-04qg

// #include <algorithm>
// #include <functional>
// #include <optional>
// #include <vector>

class Solution {
public:
    using fruitT = std::vector<int>;
    using fruitsT = std::vector<fruitT>;
// let 'n' be a count of the given fruit positions
// time complexity O(h)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    int maxTotalFruits(
        fruitsT const & fruits_,
        int const startPos_,
        int const stepsAllowed_
    );
private:
    int CalculateStepsRequired(
        int const windowStart_,
        int const windowEnd_
    );
    int mStartPos{};
    std::optional<std::reference_wrapper<const fruitsT>> mFruits;
};

int Solution::maxTotalFruits(
    fruitsT const & fruits_,
    int const startPos_,
    int const stepsAllowed_
) {
    mStartPos = startPos_;
    mFruits = fruits_;
    if(!mFruits.has_value()) {
        return -1;
    }
    auto & fruits{mFruits->get()};
    auto windowStart{0};
    auto windowEnd{0};
    auto const fruitsSz{fruits.size()};
    auto currFruitSum{0};
    auto maxFruitSum{0};
    while(windowEnd < fruitsSz) {
        auto const currFruitCount{fruits.at(windowEnd).at(1)};
        currFruitSum += currFruitCount;
        while(
            windowStart <= windowEnd &&
            CalculateStepsRequired(windowStart, windowEnd) > stepsAllowed_
        ) {
            auto const fruitCountToRemove(fruits.at(windowStart).at(1));
            currFruitSum -= fruitCountToRemove;
            ++windowStart;
        }
        maxFruitSum = std::max(maxFruitSum, currFruitSum);
        ++windowEnd;
    }
    return maxFruitSum;
}

int Solution::CalculateStepsRequired(
    int const windowStart_,
    int const windowEnd_
) {
    if(!mFruits.has_value()) {
        return -1;
    }
    auto & fruits{mFruits->get()};
    auto const fruitLeftPos_{fruits.at(windowStart_).at(0)};
    auto const fruitRightPos_{fruits.at(windowEnd_).at(0)};
    auto stepsRequired{0}; 
    if(fruitRightPos_ <= mStartPos) {
        stepsRequired = mStartPos - fruitLeftPos_;
    } else if(fruitLeftPos_ >= mStartPos) {
        stepsRequired = fruitRightPos_ - mStartPos;
    } else {
        auto const minStepsRequired{std::min(
            std::abs(mStartPos - fruitRightPos_),
            std::abs(mStartPos - fruitLeftPos_))};
        auto const fruitRangeSz{fruitRightPos_ - fruitLeftPos_};    
        stepsRequired = minStepsRequired + fruitRangeSz;
    }
    return stepsRequired;
}
