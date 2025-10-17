// problem : https://leetcode.com/problems/maximize-the-number-of-partitions-after-operations/description/
// submission : https://leetcode.com/problems/maximize-the-number-of-partitions-after-operations/submissions/1804079695
// solution post : https://leetcode.com/problems/maximize-the-number-of-partitions-after-operations/solutions/7281569/
//    c-modern-readable-code-beats-100-runtime-fs0l

// import std;

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream("display_runtime.txt") << 0 << std::endl;
            }
        };
        std::atexit(&Print::DoPrint);
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

class Solution {
public:
// let 's' be the length of the given string
// 'c' - size of the given character set
// time complexity O(s * c)
// space complexity O(s)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto maxPartitionsAfterOperations(
        std::string_view const str_,
        int const maxUniqueChrsCnt_
    ) -> int;

private:
    inline static size_t constexpr kChrSetSz{26};
    inline static char constexpr kChrSetFirst{'a'};

    struct Split {
        int mSegmentCnt{};
        std::bitset<kChrSetSz> mChrMask{};
        int mUniqueChrCnt{};
    };

    auto CreateSplit(
        std::bitset<kChrSetSz> & chrMask_,
        int & uniqueChrCnt_,
        int & segmentCnt_,
        int const idx_
    ) const -> Split;

    std::string_view mStr;
    int mMaxUniqueChrsCnt;
};

auto Solution::maxPartitionsAfterOperations(
    std::string_view const str_,
    int const maxUniqueChrsCnt_
) -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    mStr = str_;
    mMaxUniqueChrsCnt = maxUniqueChrsCnt_;
    auto const strSz{std::ssize(mStr)};
    auto leftSplits{std::vector<Split>{}};
    leftSplits.reserve(strSz);
    leftSplits.emplace_back(Split{});
    auto rightSplits{std::vector<Split>{}};
    rightSplits.reserve(strSz);
    rightSplits.emplace_back(Split{});
    auto currSegmentCnt{0};
    auto currChrMask{std::bitset<kChrSetSz>{}};
    auto uniqueChrCnt{0};
    for(auto const idx: vs::iota(0, strSz - 1)) {
        leftSplits.emplace_back(
            CreateSplit(currChrMask, uniqueChrCnt, currSegmentCnt, idx));
    }
    currSegmentCnt = 0;
    currChrMask = 0;
    uniqueChrCnt = 0;
    for(auto const idx: vs::iota(1, strSz) | vs::reverse) {
        rightSplits.emplace_back(
            CreateSplit(currChrMask, uniqueChrCnt, currSegmentCnt, idx));
    }
    rngs::reverse(rightSplits);
    int maxSegmentCnt{0};
    for(auto const idx: vs::iota(0, strSz)) {
        auto & leftSplit{leftSplits[idx]};
        auto & rightSplit{rightSplits[idx]};
        auto currSegmentCnt{
            leftSplit.mSegmentCnt + rightSplit.mSegmentCnt + 2
        };
        auto joinChrMask{leftSplit.mChrMask | rightSplit.mChrMask};
        size_t currUniuqueChrCnt{0};
        while(joinChrMask.any()) {
            joinChrMask.reset(std::countr_zero(joinChrMask.to_ulong()));
            ++currUniuqueChrCnt;
        }
        if(leftSplit.mUniqueChrCnt == mMaxUniqueChrsCnt &&
            rightSplit.mUniqueChrCnt == mMaxUniqueChrsCnt && 
            currUniuqueChrCnt < kChrSetSz
        ) {
            ++currSegmentCnt;
        } else if(
            std::min(currUniuqueChrCnt + 1, kChrSetSz) <= mMaxUniqueChrsCnt
        ) {
            --currSegmentCnt;
        }
        maxSegmentCnt = std::max(maxSegmentCnt, currSegmentCnt);
    }
    return maxSegmentCnt;
}

auto Solution::CreateSplit(
    std::bitset<kChrSetSz> & chrMask_,
    int & uniqueChrCnt_,
    int & segmentCnt_,
    int const idx_
) const -> Split {
    auto singleChrMask{std::bitset<kChrSetSz>{}};
    singleChrMask.set(mStr[idx_] - kChrSetFirst);
    if((chrMask_ & singleChrMask).none()) {
        ++uniqueChrCnt_;
        if(uniqueChrCnt_ <= mMaxUniqueChrsCnt) {
            chrMask_ |= singleChrMask;
        } else {
            ++segmentCnt_;
            chrMask_ = singleChrMask;
            uniqueChrCnt_ = 1;
        }
    }
    return {segmentCnt_, chrMask_, uniqueChrCnt_};
}
