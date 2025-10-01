// problem : https://leetcode.com/problems/water-bottles/description/
// submission : https://leetcode.com/problems/water-bottles/submissions/1788301646
// solution post : https://leetcode.com/problems/water-bottles/solutions/7239836/
//    c-modern-readable-code-beats-100-runtime-6ifd

// import std;

class Solution {
public:
// let 'n' be the count of the given bottles
// time complexity O(1)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto numWaterBottles(
        int const bottlesCntInit_,
        int const bottlesExchangeRate_
    ) const -> int;

private:
    inline static bool const kIsFastIO{
        [] () {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return true;
        } ()
    };
};

auto Solution::numWaterBottles(
    int const bottlesCntInit_,
    int const bottlesExchangeRate_
) const -> int {
    assert(bottlesExchangeRate_ > 1);
    auto const bottlesExtraCnt{
        (bottlesCntInit_ - 1) / (bottlesExchangeRate_ - 1)};
    auto const bottlesCntFinal{bottlesCntInit_ + bottlesExtraCnt};
    return bottlesCntFinal;
}
