// problem : https://leetcode.com/problems/apply-operations-to-maximize-score/description
// submission : https://leetcode.com/problems/apply-operations-to-maximize-score/submissions/1592313462
// solution post : https://leetcode.com/problems/apply-operations-to-maximize-score/solutions/6600932/
//     c-modern-readable-code-optimal-time-comp-5yts

// #include <algorithm>
// #include <queue>
// #include <vector>
// #include <stack>

namespace Utility {
    auto constexpr kMod{static_cast<int>(1e9 + 7)};
}

// let 'n' be a numbers count given
// 'o' - count of operations given
// 'm' - maximum number among given
// time complexity O(n * (sqrt(m) + log(n))
// space complexity O(n)
// runtime 305 ms, beats 49.65 %
class Solution {
public:
    int maximumScore(
        std::vector<int> const & nums,
        int const operationsAvailableCount
    ) const {
        using namespace Utility;
        auto numsCount{nums.size()};
        auto primeScores{std::vector<int>(numsCount, 0)};
        for(auto index{0}; index < numsCount; ++index) {
            auto num{nums[index]};
            for(auto factor{2}; factor <= static_cast<int>(std::sqrt(num));
                ++factor
            ) {
                if(num % factor == 0) {
                    ++primeScores[index];
                    while(num % factor == 0) {
                        num /= factor;
                    }
                }
            }
            if(num >= 2) {
                ++primeScores[index];
            }
        }
        auto nextDominantIdx{std::vector<int>(numsCount, numsCount)};
        auto prevDominantIdx{std::vector<int>(numsCount, -1)};
        auto decresingPrimeScoreIndxs{std::stack<int>{}};
        for(auto index{0}; index < numsCount; ++index) {
            while(!decresingPrimeScoreIndxs.empty() && 
                primeScores.at(decresingPrimeScoreIndxs.top()) <
                    primeScores[index]
            ) {
                auto topIndex{decresingPrimeScoreIndxs.top()};
                decresingPrimeScoreIndxs.pop();
                nextDominantIdx[topIndex] = index;
            }
            if(!decresingPrimeScoreIndxs.empty()) {
                prevDominantIdx[index] = decresingPrimeScoreIndxs.top();
            }
            decresingPrimeScoreIndxs.push(index);
        } 
        auto subarraysCount{std::vector<long long>(numsCount, 0)};
        for(auto index{0}; index < numsCount; ++index) {
            subarraysCount[index] = static_cast<long long>(
                nextDominantIdx[index] - index) *
                (index - prevDominantIdx[index]);
        }
        auto processingQueue{std::priority_queue<std::pair<int, int>>{}};
        for(auto index{0}; index < numsCount; ++index) {
            processingQueue.emplace(nums[index], index);
        }
        auto score{1LL};
        auto operationsUsedCount{0};
        while(operationsUsedCount < operationsAvailableCount) {
            auto const [num, index]{processingQueue.top()};
            processingQueue.pop();
            auto operationsCount{std::min(
                static_cast<long long>(operationsAvailableCount) -
                    operationsUsedCount,
                subarraysCount[index])};
            score = (score * FindPower(num, operationsCount)) % kMod;
            operationsUsedCount += operationsCount;
        }
        return score;
    }
private:
    long long FindPower(
        long long base,
        long long exponent
    ) const {
        using namespace Utility;
        auto power{1LL};
        while(exponent > 0) {
            if(exponent % 2 == 1) {
                power = ((power * base) % kMod);
            }
            base = (base * base) % kMod;
            exponent /= 2;
        }
        return power;
    }
};
