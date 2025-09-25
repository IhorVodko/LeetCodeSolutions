// problem : https://leetcode.com/problems/delete-and-earn/description
// submission : https://leetcode.com/problems/delete-and-earn/submissions/1782207902
// solution post : https://leetcode.com/problems/delete-and-earn/solutions/7222727/
//    c-modern-readable-code-beats-100-runtime-af7j

// import std;

class Solution {
public:
// let 'c' be a count of the given numbers
// 'n' - maximum of the given numbers
// time complexity O(c + min(n, c * log(c)))
// space complexity O(c)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto deleteAndEarn(std::vector<int> & nums_) const -> int;

private:
    [[nodiscard]]
    inline auto IsApproach1Faster(
        int const maxNum_,
        int const numsSz_
    ) const -> bool;
    auto DoApproach1(
        std::unordered_map<int, int> const & numToPoints_,
        int const maxNum_
    ) const -> int;
    auto DoApproach2(
        std::vector<int> & nums_,
        std::unordered_map<int, int> const & numToPoints_
    ) const -> int;

    inline static bool const kIsFastIO{
        [] () {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return true;
        } ()
    };
};

auto Solution::deleteAndEarn(std::vector<int> & nums_) const -> int {
    using intT = std::numeric_limits<int>;

    auto const numsSz{nums_.size()};
    auto numToPoints{std::unordered_map<int, int>{}};
    numToPoints.reserve(numsSz);
    auto maxNum{intT::min()};
    for(auto const num: nums_) {
        numToPoints[num] += num;
        maxNum = std::max(maxNum, num);
    }
    auto pointsEarnedPrevPrev{0};
    auto pointsEarnedPrev{0};
    if(IsApproach1Faster(maxNum, numsSz)) {
        auto const maxPointsEarned{DoApproach1(numToPoints, maxNum)};
        return maxPointsEarned;
    }
    auto const maxPointsEarned{DoApproach2(nums_, numToPoints)};
    return maxPointsEarned;
    
}

auto Solution::IsApproach1Faster(
    int const maxNum_,
    int const numsSz_
) const -> bool {
    auto const isApproach1Faster{
        maxNum_ < numsSz_ + numsSz_ * std::log(numsSz_) / std::log(2)
    };
    return isApproach1Faster;
}

auto Solution::DoApproach1(
    std::unordered_map<int, int> const & numToPoints_,
    int const maxNum_
) const -> int {
    namespace views = std::views;

    auto pointsEarnedPrevPrev{0};
    auto pointsEarnedPrev{0};
    for(auto const num: views::iota(0, maxNum_ + 1)) {
        auto const pointsEarnedTemp{pointsEarnedPrev};
        auto pointsEarnedCurr{0};
        if( auto const numToPointsIt{numToPoints_.find(num)};
            numToPointsIt != numToPoints_.end()
        ) {
            pointsEarnedCurr = numToPointsIt->second;
        }
        pointsEarnedPrev = std::max(
            pointsEarnedPrev,
            pointsEarnedPrevPrev + pointsEarnedCurr
        );
        pointsEarnedPrevPrev = pointsEarnedTemp;
    }
    return pointsEarnedPrev;
}

auto Solution::DoApproach2(
    std::vector<int> & nums_,
    std::unordered_map<int, int> const & numToPoints_
) const -> int {
    namespace ranges = std::ranges;

    ranges::sort(nums_);
    auto pointsEarnedPrevPrev{0};
    auto pointsEarnedPrev{0};
    for(auto const num: nums_ | views::take(numToPoints_.size())) {
        auto const pointsEarnedTemp{pointsEarnedPrev};
        if( auto numToPointsIt{numToPoints_.find(num - 1)};
            numToPointsIt != numToPoints_.end()
        ) {
            auto const pointsEarnedCurr{
                pointsEarnedPrevPrev + numToPointsIt->second};
            pointsEarnedPrev = std::max(
                pointsEarnedPrev,
                pointsEarnedCurr
            );
        } else {
            pointsEarnedPrev += numToPoints_.at(num);
        }
        pointsEarnedPrevPrev = pointsEarnedTemp;
    }
    return pointsEarnedPrev;
}
