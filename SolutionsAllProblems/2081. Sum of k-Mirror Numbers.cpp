// problem : https://leetcode.com/problems/sum-of-k-mirror-numbers/description
// submission : https://leetcode.com/problems/sum-of-k-mirror-numbers/submissions/1673855853
// solution post : https://leetcode.com/problems/sum-of-k-mirror-numbers/solutions/6877042/
//    c-modern-readable-code-optimal-time-comp-rm7v

// #include <array>

namespace Util {
    inline constexpr auto kDigitsCountMax{100};
    inline constexpr auto kRadix10{10};
}

class Solution {
public:
// Based on the problem's constraints, for a given n and k, it is difficult to determine the range of the nth k-mirror
// number. In this problem, the worst case is when n=30, k=7, and the corresponding number is 64454545446.
// time complexity O(sqrt(10^10))
// space complexity O(1)
// runtime 155 ms, beats 75.44 %
    long long kMirror(
        int const radix_,
        int const numsCount_
    );
private:
    bool IsPalindrome(long long const num_);
    std::array<int,  Util::kDigitsCountMax> mDigits;
    int mRadix;
};

long long Solution::kMirror(
    int const radix_,
    int const numsCount_
) {
    using namespace  Util;
    mRadix = radix_;
    auto left{1};
    auto numsCountCurr{0};
    auto sum{0ll};
    while(numsCountCurr < numsCount_) {
        auto const right{left * kRadix10};
        for(auto const caseType: {0, 1}) {
            for(auto numHalf{left}; numHalf < right && numsCountCurr < numsCount_;
                ++numHalf
            ) {
                auto numFull{static_cast<long long>(numHalf)};
                auto numHalfChanged{caseType == 0 ? numHalf / kRadix10 : numHalf};
                while(numHalfChanged > 0) {
                    numFull = (numFull * kRadix10) + (numHalfChanged % kRadix10);
                    numHalfChanged /= kRadix10;
                }
                if(IsPalindrome(numFull)) {
                    ++numsCountCurr;
                    sum += numFull;
                }
            }
        }
        left = right;
    }
    return sum;
}

bool Solution::IsPalindrome(long long const num_) {
    auto digitsCount{0};
    auto num{num_};
    while(num > 0) {
        ++digitsCount;
        mDigits.at(digitsCount - 1) = num % mRadix;
        num /= mRadix;
    }
    for(auto i1{0}, i2{digitsCount - 1}; i1 < i2; ++i1, --i2) {
        if(mDigits.at(i1) != mDigits.at(i2)) {
            return false;
        }
    }
    return true;
}
