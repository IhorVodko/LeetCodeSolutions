// problem : https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-ii/description
// submission : https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-ii/submissions/
//    1661000161
// solution post : https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-ii/
//    solutions/6833318/c-modern-readable-code-beats-100-runtime-f3yf

// #include <algorithm>
// #include <array>

namespace Util {
    auto constexpr kChrMin{'0'};
    auto constexpr kChrMax{'4'};
    auto constexpr kOddEvenCountCase{0b10};
}
class Solution {
public:
// let 's' be a length of the given string
// 'c' - size of the given character set
// time complexity O(n * c^2)
// space complexity O(c)
// runtime 21 ms, beats 100.00 %
    int maxDifference(
        std::string const & str_,
        int const subStrMinSz_
    ) const;
private:
    int ComputeStatus(
        int const count1_,
        int const count2_
    ) const {
        auto const status{((count1_ & 1) << 1) | (count2_ & 1)};
        return status;
    }
};

int Solution::maxDifference(
    std::string const & str_,
    int const subStrMinSz_
) const {
    using namespace Util;
    using IntT = std::numeric_limits<int>;
    auto const strSz{str_.size()};
    auto diffMax{IntT::min()};
    for(auto chr1{kChrMin}; chr1 <= kChrMax; ++chr1) {
        for(auto chr2{kChrMin}; chr2 <= kChrMax; ++chr2) {
            if(chr1 == chr2) {
                continue;
            }
            auto diffsCurr{std::array<int, 4>{
                IntT::max(), IntT::max(), IntT::max(), IntT::max()}};
            auto countCurr1{0};
            auto countCurr2{0};
            auto countPrev1{0};
            auto countPrev2{0};
            auto idxLeft{-1};
            for(auto idxRight{0}; idxRight < strSz; ++idxRight) {
                countCurr1 += (str_.at(idxRight) == chr1);
                countCurr2 += (str_.at(idxRight) == chr2);
                while(idxRight - idxLeft >= subStrMinSz_ &&
                    countCurr2 - countPrev2 >= 2
                ) {
                    auto statusLeft{ComputeStatus(countPrev1, countPrev2)};
                    diffsCurr.at(statusLeft) =
                        std::min(diffsCurr.at(statusLeft), countPrev1 - countPrev2);
                    ++idxLeft;
                    countPrev1 += (str_.at(idxLeft) == chr1);
                    countPrev2 += (str_.at(idxLeft) == chr2);
                }
                auto statusRight{ComputeStatus(countCurr1, countCurr2)};
                if(diffsCurr.at(statusRight ^ kOddEvenCountCase) != IntT::max()) {
                    diffMax = std::max(diffMax,
                        countCurr1 - countCurr2 -
                            diffsCurr.at(statusRight ^ kOddEvenCountCase));
                }
            }
        }
    }
    return diffMax;
}
