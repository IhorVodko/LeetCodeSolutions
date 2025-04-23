// problem : https://leetcode.com/problems/count-the-number-of-ideal-arrays/description/
// submission : https://leetcode.com/problems/count-the-number-of-ideal-arrays/submissions/1616008318
// solution post : https://leetcode.com/problems/count-the-number-of-ideal-arrays/solutions/6681440/
//     c-modern-readable-code-optimal-time-comp-9huj

// #include <algorithm>
// #include <vector>

// let 'm' be a value of the 'maxValue_' parameter
// 'l' - value of the 'arrLength_' parameter
// p - count of distinct prime factors of 'maxValue_' parameter
// time complexity O((l + p) * p + m * p)
// space complexity O((l + log(m) * log(m))
// runtime 435 ms, beats 5.31 %
namespace Utility {
    auto constexpr kModVal{static_cast<int>(1e9 + 7)};
    auto constexpr kMaxArrLength{static_cast<int>(1e4 + 10)};
    auto constexpr kPrimeFactorsMaxCount{15};
}

class Solution {
public:
    int idealArrays(
        int const arrLength_,
        int const maxValue_
    ) const;
    Solution();
private:
    std::vector<std::vector<int>> mMx;
    std::vector<std::vector<int>> mPrimeFactorCounts;
    std::vector<int> mSieve;
};

int Solution::idealArrays(
    int const arrLength_,
    int const maxValue_
) const {
    using namespace Utility;
    auto arrsTotalCount{0ll};
    for(auto num{1}; num <= maxValue_; ++num) {
        auto arrsCount{1ll};
        for(auto const p: mPrimeFactorCounts[num]) {
            arrsCount = arrsCount * mMx.at(arrLength_ + p - 1).at(p) % kModVal;
        }
        arrsTotalCount = (arrsTotalCount + arrsCount) % kModVal;
    }
    return arrsTotalCount;
}

Solution::Solution():
    mMx(Utility::kMaxArrLength + Utility::kPrimeFactorsMaxCount,
        std::vector<int>(Utility::kPrimeFactorsMaxCount + 1, 0)),
    mPrimeFactorCounts(Utility::kMaxArrLength, std::vector<int>{}),
    mSieve(Utility::kMaxArrLength, 0)
{
    using namespace Utility;
    for(auto i{2}; i < mSieve.size(); ++i) {
        if(mSieve[i] != 0) {
            continue;
        }
        for(auto j{i}; j < mSieve.size(); j += i) {
            mSieve[j] = i;
        }
    }
    for(auto i{2}; i < mSieve.size(); ++i) {
        auto x{i};
        while(x > 1) {
            auto const p{mSieve.at(x)};
            auto cnt{0};
            while(x % p == 0) {
                x /= p;
                ++cnt;
            }
            mPrimeFactorCounts.at(i).emplace_back(cnt);
        }
    } 
    mMx.at(0).at(0) = 1;
    for(auto i{1}; i < mMx.size(); ++i) {
        mMx[i][0] = 1;
        for(auto j{1}; j <= std::min(i, kPrimeFactorsMaxCount); ++j) {
            mMx[i].at(j) = (mMx.at(i - 1).at(j) + mMx.at(i - 1).at(j - 1)) % kModVal;
        }
    }
}
