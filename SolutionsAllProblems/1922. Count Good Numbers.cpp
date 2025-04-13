// problem : https://leetcode.com/problems/count-good-numbers/description/
// submission : https://leetcode.com/problems/count-good-numbers/submissions/1605813806
// solution post : https://leetcode.com/problems/count-good-numbers/solutions/6647378/
//     c-modern-readable-code-beats-100-runtime-dvvm

// let 'n' be a digits count given
// time complexity O(log2(n))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
namespace Uitility {
    auto constexpr kMod{static_cast<int>(1e9 + 7)};
    auto constexpr kPrimeeDigitsCount{4};
    auto constexpr kEvenDigitsCount{5};
}

class Solution {
public:
    int countGoodNumbers(long long const digitsCount_) const;
private:
    long long DoFastExponentiation(
        long long const multiplicand_,
        long long const multiplier_
    ) const;
};

int Solution::countGoodNumbers(long long const digitsCount_) const {
    using namespace Uitility;
    auto const goodNumsCount{
        (DoFastExponentiation(kPrimeeDigitsCount, digitsCount_ / 2) *
        DoFastExponentiation(kEvenDigitsCount, (digitsCount_ + 1) / 2)) % kMod};
    return goodNumsCount;
} 

long long Solution::DoFastExponentiation(
    long long const multiplicand_,
    long long const multiplier_
) const {
    using namespace Uitility;
    auto product{1LL};
    auto multiplicand{multiplicand_};
    for(auto multiplier{multiplier_}; multiplier > 0; multiplier /= 2) {
        if (multiplier % 2 == 1) {
            product = (product * multiplicand) % kMod;
        }
        multiplicand = (multiplicand * multiplicand) % kMod;
    }
    return product;
}
