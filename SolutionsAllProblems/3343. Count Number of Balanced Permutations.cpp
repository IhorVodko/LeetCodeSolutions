// problem : https://leetcode.com/problems/count-number-of-balanced-permutations/description/
// submission : https://leetcode.com/problems/count-number-of-balanced-permutations/submissions/1629628758
// solution post : https://leetcode.com/problems/count-number-of-balanced-permutations/solutions/6729004/
//    c-modern-readable-code-optimal-time-comp-xw48

// #include <algorithm>
// #include <string>
// #include <vector>

namespace Utility {
    auto constexpr kMod{static_cast<int>(1e9) + 7};
}

class Solution {
public:
    using Arr2dT = std::vector<std::vector<long long>>;
// let 'n' be a length of the given string
// 's' - sum of the numbers in the given string
// time complexity O(n^2 * s)
// space complexity O(n^2 + n * s)
// runtime 211 ms, beats 35.59 %
    int countBalancedPermutations(std::string const & nums_) const;
};

int Solution::countBalancedPermutations(std::string const & nums_) const {
    using namespace Utility;
    auto sumTotal{0};
    auto const numsCount{static_cast<int>(nums_.size())};
    auto numCounts{std::vector<int>(10, 0)};
    for(auto const numCh: nums_) {
        auto const num{numCh - '0'};
        ++numCounts.at(num);
        sumTotal += num;
    }
    if(sumTotal % 2 != 0) {
        return 0;
    }
    auto const sumTarget{sumTotal / 2};
    auto oddIdxsCount{(numsCount + 1) / 2};
    auto permOddIdxsCounts{Arr2dT(oddIdxsCount + 1,
        std::vector<long long>(oddIdxsCount + 1, 0))};
    auto permCounts{Arr2dT(sumTarget + 1,
        std::vector<long long>(oddIdxsCount + 1, 0))};
    for(auto i{0}; i <= oddIdxsCount; ++i) {
        permOddIdxsCounts.at(i).at(i) = permOddIdxsCounts.at(i).at(0) = 1;
        for(auto j{1}; j < i; ++j) {
            permOddIdxsCounts.at(i).at(j) = (permOddIdxsCounts.at(i - 1).at(j) +
                permOddIdxsCounts.at(i - 1).at(j - 1)) % kMod;
        }
    }
    permCounts.at(0).at(0) = 1;
    auto sumPartial{0};
    auto sum{0};
    for(auto i{0}; i <= 9; ++i) {
        sumPartial += numCounts.at(i);
        sum += i * numCounts.at(i);
        for(auto permsOddCount{std::min(sumPartial, oddIdxsCount)};
            permsOddCount >= std::max(0, sumPartial - (numsCount - oddIdxsCount));
            --permsOddCount
        ) {
            auto permsEvenCount{sumPartial - permsOddCount};
            for(auto curr{std::min(sum, sumTarget)};
                curr >= std::max(0, sum - sumTarget); --curr
            ) {
                auto permsTotalCount{0ll};
                for(auto j{std::max(0, numCounts.at(i) - permsEvenCount)};
                    j <= std::min(numCounts.at(i), permsOddCount) && 
                    i * j <= curr; ++j 
                ) {
                    auto ways{permOddIdxsCounts.at(permsOddCount).at(j) *
                        permOddIdxsCounts.at(permsEvenCount).at(
                            numCounts.at(i) - j) % kMod};
                    permsTotalCount = (permsTotalCount + ways *
                        permCounts.at(curr - i * j).at(permsOddCount - j) % kMod) % kMod;
                }
                permCounts.at(curr).at(permsOddCount) = permsTotalCount % kMod;
            }
        }
    }
    return permCounts.at(sumTarget).at(oddIdxsCount);
}
