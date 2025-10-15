// problem : https://leetcode.com/problems/coin-change/description/
// submission : https://leetcode.com/problems/coin-change/submissions/1802270493
// solution post : https://leetcode.com/problems/coin-change/solutions/7276960/
//    c-modern-readable-code-optimal-time-comp-oh2o

// import std;

// let 'c' be the number of coin values given
// 's' - the target sum
// time complexity O(c * s)
// space complexity O(s)
// runtime 32 ms, beats 56.80 %
class Solution {
public:
    [[nodiscard]]
    auto coinChange(
        std::vector<int> const & coins_,
        int const sum_
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

auto Solution::coinChange(
    std::vector<int> const & coins_,
    int const sum_
) const -> int {
    namespace vs = std::views;

    auto minCoinCntsDp{std::vector<int>(sum_ + 1, sum_ + 1)};
    minCoinCntsDp.at(0) = 0;
    for(auto const currSum: vs::iota(1, sum_ + 1)) {
        for(auto const coin: coins_) {
            if(coin <= currSum) {
                auto & minCoinCnt{minCoinCntsDp[currSum]};
                auto const nextSum{currSum - coin};
                auto const currCoinCnt{minCoinCntsDp.at(nextSum) + 1};
                minCoinCnt = std::min(minCoinCnt, currCoinCnt); 
            }
        }
    }
    auto const minCoinCnt{
        minCoinCntsDp[sum_] > sum_ ? -1 : minCoinCntsDp[sum_]
    };
    return minCoinCnt;
}
