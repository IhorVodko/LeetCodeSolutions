// problem : https://leetcode.com/problems/target-sum/description/
// submission : https://leetcode.com/problems/target-sum/submissions/1489194365
// solution post : https://leetcode.com/problems/target-sum/solutions/6190667/c-modern-readable-code-by-cyberartist-974x

// #include <algorithm>
// #include <cmath>
// #incldue <vector>

// let 'n' be a parameter 'nums' length
// 's' - sum of numbers in 'nums'
// time complexity O(n * s)
// space complexity O(s)
// runtime 14 ms, beats 61.28 %
class Solution {
public:
    int findTargetSumWays(
        std::vector<int> const & nums,
        int const target
    ) {
        numsSum = std::accumulate(nums.cbegin(), nums.cend(), 0);
        auto cacheSize{static_cast<size_t>(2 * numsSum + 1)};
        cachedSums.assign(cacheSize, 0);
        ++cachedSums.at(ToIdx(nums.front()));
        ++cachedSums.at(ToIdx(-1 * nums.front()));
        auto thisStepSums{std::vector<int>(cacheSize, 0)};
        for(auto num{nums.cbegin() + 1}, end(nums.cend()); num < end; ++num) {
            std::fill(thisStepSums.begin(), thisStepSums.end(), 0);
            for(auto prevSum = -1 * numsSum; prevSum <= numsSum; ++prevSum) {
                if(isCached(prevSum)) {
                    thisStepSums.at(ToIdx(prevSum + *num)) +=
                        cachedSums.at(ToIdx(prevSum));
                    thisStepSums.at(ToIdx(prevSum - *num)) += 
                        cachedSums.at(ToIdx(prevSum));
                }
            }
            cachedSums = thisStepSums;
        }
        return std::abs(target) > numsSum ? 0 : cachedSums.at(ToIdx(target));
    }
    Solution() :
        numsSum{0}
    {}
private:
    int ToIdx(int const num) const {
        return num + numsSum;
    }
    bool isCached(int const sum) const {
        return cachedSums.at(ToIdx(sum)) > 0;
    }
    int numsSum;
    std::vector<int> cachedSums;
};
