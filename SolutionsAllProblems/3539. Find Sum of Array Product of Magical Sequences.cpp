// problem : https://leetcode.com/problems/find-sum-of-array-product-of-magical-sequences/description/
// submission : https://leetcode.com/problems/find-sum-of-array-product-of-magical-sequences/submissions/1799738133
// solution post : https://leetcode.com/problems/find-sum-of-array-product-of-magical-sequences/solutions/7270292/
//    c-modern-readable-code-optimal-time-comp-2sxw

// import std;

class Solution {
public:
// let 's' be the given length of the sequence
// 'b' - given count of the set bits required
// 'n' - count of the given nubmers
// time complexity O(s^2 * b * n)
// space complexity O(s^2 * b)
// runtime 60 ms, beats 60.00 %
    [[nodiscard]]
    auto magicalSum(
        int const magicalSeqSz_,
        int const setBitsCnt_,
        std::vector<int> const & nums_
    ) const -> int;

private:
    static inline int constexpr kModVal{1'000'000'007};
    inline static bool const kIsFastIO{
        [] () {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return true;
        } ()
    };

    [[nodiscard]]
    inline auto CalcModPow(
            long long base_,
            long long exp_
    ) const noexcept -> long long;
};

auto Solution::magicalSum(
    int const magicalSeqSz_,
    int const setBitsCnt_,
    std::vector<int> const & nums_
) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto const numsSz{std::ssize(nums_)};
    auto factorials{std::vector<long long>(magicalSeqSz_ + 1, 1)};
    auto invFactorials{std::vector<long long>(magicalSeqSz_ + 1, 1)};
    for(auto const idx: vs::iota(1, magicalSeqSz_ + 1)) {
        factorials.at(idx) = (factorials.at(idx - 1) * idx) % kModVal;
    } 
    invFactorials.at(magicalSeqSz_) =
        CalcModPow(factorials.at(magicalSeqSz_), kModVal - 2);
    for(auto const i: vs::iota(1, magicalSeqSz_ + 1) | vs::reverse) {
        invFactorials.at(i - 1) = (invFactorials.at(i) * i) % kModVal;
    }
    auto powNum{std::vector<std::vector<long long>>(
        numsSz,
        std::vector<long long>(magicalSeqSz_ + 1, 1)
    )};
    for(auto const idx1: vs::iota(0, numsSz)) {
        for(auto const idx2: vs::iota(1, magicalSeqSz_ + 1)) {
            powNum.at(idx1).at(idx2) =
                (powNum.at(idx1).at(idx2 - 1) *
                    (nums_.at(idx1) % kModVal))
                % kModVal;
        }
    }
    auto const carryIdx{magicalSeqSz_ + 1};
    auto const setBitsCnt{setBitsCnt_ + 1};
    auto const usedNumsCnt{magicalSeqSz_ + 1};
    auto CalcIdx{
        [&] (
            int const carryIdx_,
            int const setBitsCnt_,
            int const usedNumsCnt_
        ) -> int {
            auto const idx{
                (carryIdx_ * setBitsCnt + setBitsCnt_) * usedNumsCnt +
                usedNumsCnt_
            };
            return idx;
        }
    };
    auto dpSums1{std::vector<long long>(carryIdx * setBitsCnt * usedNumsCnt)};
    auto dpSums2{std::vector<long long>(carryIdx * setBitsCnt * usedNumsCnt)};
    dpSums1.at(CalcIdx(0, 0, 0)) = 1;
    for(auto const pos: vs::iota(0, numsSz)) {
        for(auto const currCarryIdx: vs::iota(0, magicalSeqSz_ + 1)) {
            for(auto const currSetBitIdx: vs::iota(0, setBitsCnt_ + 1)) {
                for(auto const usedNumsCurrCnt:
                    vs::iota(0, magicalSeqSz_ + 1)
                ) {
                    auto const currSum{dpSums1.at(
                        CalcIdx(currCarryIdx, currSetBitIdx, usedNumsCurrCnt)
                    )};
                    if(!currSum) {
                        continue;
                    }
                    auto const rem{magicalSeqSz_ - usedNumsCurrCnt};
                    for(auto const carryIdxRem: vs::iota(0, rem + 1)) {
                        auto const carryIdxTotal{carryIdxRem + currCarryIdx};
                        auto const bitVal{carryIdxTotal & 1};
                        auto const nextCarryIdx{carryIdxTotal >> 1};
                        auto const nextSetBitIdx{currSetBitIdx + bitVal};
                        if(nextSetBitIdx > setBitsCnt_) {
                            continue;
                        }
                        auto currSumCopy{currSum};
                        currSumCopy =
                            (currSumCopy * powNum.at(pos).at(carryIdxRem)) %
                            kModVal;
                        currSumCopy =
                            (currSumCopy * invFactorials.at(carryIdxRem)) %
                            kModVal;
                        auto & sum{dpSums2.at(CalcIdx(
                            nextCarryIdx,
                            nextSetBitIdx,
                            usedNumsCurrCnt + carryIdxRem
                        ))};
                        sum = (sum + currSumCopy) % kModVal;
                    }
                }
            }
        }
        dpSums1 = dpSums2;
        rngs::fill(dpSums2, 0);
    }
    auto sumTotal{0};
    for(auto const currCarryIdx: vs::iota(0, magicalSeqSz_ + 1)) {
        for(auto const currSetBitIdx: vs::iota(0, setBitsCnt_ + 1)) {
            auto sum{dpSums1.at(
                CalcIdx(currCarryIdx, currSetBitIdx, magicalSeqSz_)
            )};
            if(sum == 0) {
                continue;
            }
            auto finalOnes{
                currSetBitIdx +
                std::popcount(static_cast<unsigned>(currCarryIdx)
            )};
            if(finalOnes == setBitsCnt_) {
                sum = (sum * factorials.at(magicalSeqSz_)) % kModVal; 
                sumTotal = (sumTotal + sum) % kModVal;
            }
        }
    }
    return sumTotal;
}

auto Solution::CalcModPow(
        long long base_,
        long long exp_
) const noexcept -> long long {
    auto rem{1ll};
    while(exp_) {
        if(exp_ & 1) {
            rem = (rem * base_) % kModVal;
        }
        base_ = (base_ * base_) % kModVal;
        exp_ >>= 1;
    } 
    return rem; 
}
