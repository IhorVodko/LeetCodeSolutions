// problem : https://leetcode.com/problems/count-the-number-of-arrays-with-k-matching-adjacent-elements/description/
// submission : https://leetcode.com/problems/count-the-number-of-arrays-with-k-matching-adjacent-elements/submissions/
//    1667391170
// solution post : https://leetcode.com/problems/count-the-number-of-arrays-with-k-matching-adjacent-elements/solutions/
//    6854843/c-modern-readable-code-beats-100-runtime-k5lh

// #include <cstdint>

#include <ranges>

namespace Util {
    auto constexpr kMod{static_cast<std::int_fast32_t>(1e9) + 7};
    auto constexpr kArrSzMax{static_cast<std::int_fast32_t>(1e5)};
}

class Solution {
public:
    using i64fT = std::int_fast64_t;
    using i32fT = std::int_fast32_t;
// let 'n' be a required length of the sub-arrays
// 'p' - required number of pairs with equal adjacent values
// time complexity O(log(n - p))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    i32fT countGoodArrays(
        i32fT const subArrSz_,
        i32fT const ArrSz_,
        i32fT const pairsCount_
    ) const;
private:
    i64fT CalculateComb(
        i32fT const num1_,
        i32fT const num2_
    ) const;
    static constexpr std::array<i64fT, Util::kArrSzMax> initFactorials();
    static constexpr std::array<i64fT, Util::kArrSzMax>
    initFactorialsInv();
    static constexpr i64fT DoQPow(
        i64fT const num_,
        i32fT const pow_
    );
    inline static std::array<i64fT, Util::kArrSzMax>
        mFactorials{initFactorials()};
    inline static std::array<i64fT, Util::kArrSzMax>
        mFactorialsInv{initFactorialsInv()};
};

Solution::i32fT Solution::countGoodArrays(
    i32fT const subArrSz_,
    i32fT const ArrSz_,
    i32fT const pairsCount_
) const {
    using namespace  Util;
    auto goodArrCount{CalculateComb(subArrSz_ - 1, pairsCount_)};
    goodArrCount *= ArrSz_;
    goodArrCount %= kMod;
    goodArrCount *=  DoQPow(ArrSz_ - 1, subArrSz_ - pairsCount_ - 1);
    goodArrCount %= kMod;
    return goodArrCount;
}

Solution::i64fT Solution::CalculateComb(
    i32fT const num1_,
    i32fT const num2_
) const {
    using namespace Util;
    auto combCount{mFactorials.at(num1_) * mFactorialsInv.at(num2_)};
    combCount %= kMod;
    combCount *= mFactorialsInv.at(num1_ - num2_);
    combCount %= kMod;
    return combCount;
}

constexpr std::array<Solution::i64fT, Util::kArrSzMax>
Solution::initFactorials() {
    using namespace Util;
    namespace views = std::views;
    auto factorials{std::array<i64fT, Util::kArrSzMax>{}};
    factorials.at(0) = 1;
    for(auto i: views::iota(1, kArrSzMax)) {
        factorials.at(i) = (factorials.at(i - 1) * i) % kMod;
    }
    return factorials;
}

constexpr std::array<Solution::i64fT, Util::kArrSzMax>
Solution::initFactorialsInv() {
    using namespace Util;
    namespace views = std::views;
    auto factorialsInv{std::array<i64fT, Util::kArrSzMax>{}};
    factorialsInv.at(kArrSzMax - 1) =
        DoQPow(mFactorials.at(kArrSzMax - 1), kMod - 2);
    for(auto i: views::iota(1, kArrSzMax) | views::reverse) {
        factorialsInv.at(i - 1) = (factorialsInv.at(i) * i % kMod);
    }
    return factorialsInv;
}

constexpr Solution::i64fT Solution::DoQPow(
    i64fT const num_,
    i32fT const pow_
) {
    using namespace Util;
    auto num{num_};
    auto pow{pow_};
    auto product{1ll};
    while(pow) {
        if(pow % 2 == 1) {
            product = (product * num) % kMod;
        }
        num = (num * num) % kMod;
        pow /= 2;
    }
    return product;
}
