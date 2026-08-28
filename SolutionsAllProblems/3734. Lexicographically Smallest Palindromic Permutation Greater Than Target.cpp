// problem : https://leetcode.com/problems/lexicographically-smallest-palindromic-permutation-greater-than-target/description
// submission : https://leetcode.com/problems/lexicographically-smallest-palindromic-permutation-greater-than-target/submissions/2122975985
// solution post : https://leetcode.com/problems/lexicographically-smallest-palindromic-permutation-greater-than-target/solutions/8487729/
//    simplanation-simple-explanation-by-cyber-jn0g

// Approach : Greedy Prefix Matching with Backtracking
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the number of
// Time :  O(n)
// Space : O(1)

// import std;

// #include <algorithm>
// #include <array>
// #include <ios>
// #include <iostream>
// #include <iterator>
// #include <ranges>
// #include <string>

// #include <cstddef>

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

constexpr auto kChrSetSz{26};
constexpr auto kChrSetFirst{'a'};
constexpr auto kParityDiv{2};
constexpr auto kMaxOddChrCnt{1};

using cntPerChrT = std::array<int, kChrSetSz>;

constexpr auto toChr{[] (auto const idx_) {
    return static_cast<char>(kChrSetFirst + idx_);
}};
constexpr auto toIdx{[] (auto const chr_) { return chr_ - kChrSetFirst; }};
constexpr auto isPositive{[] (auto const num_) { return num_ > 0; }};
constexpr auto isOdd{[] (auto const num_) { return num_ % kParityDiv != 0; }};

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    auto lexPalindromicPermutation(
        std::string_view const srcStr_,
        std::string_view const trgtStr_
    ) -> std::string;

private:
    std::string_view mSrcStr;
    std::string_view mTrgtStr;
    int mLen{};
    int mHalfLen{};
    cntPerChrT mCntPerChr;

    auto CountChrs() const -> cntPerChrT;
    auto NotPalindrome() const -> bool;
    auto FindMiddleChr() const -> char;
    auto HalveCntPerChr() -> void;
    auto CalcPrefMatchLen() const -> int;
    auto BuildOutStr(
        std::string & outStr_,
        int const divergeIdx_,
        int const replaceIdx_,
        std::string::iterator const outStrRighHalfStart_
    ) -> void;
};

auto Solution::lexPalindromicPermutation(
    std::string_view const srcStr_,
    std::string_view const trgtStr_
) -> std::string {
    mSrcStr = srcStr_;
    mTrgtStr = trgtStr_;
    mLen = static_cast<int>(trgtStr_.size());
    mHalfLen = mLen / kParityDiv;
    // 1. Calculate character frequencies to evaluate palindrome feasibility
    mCntPerChr = CountChrs();

    // 2. Validate palindrome possibility (max one odd character count)
    if(NotPalindrome()) {
        return {};
    } 

    auto outStr{std::string(mLen, {})};

    // 3. Place the single odd-frequency character at the exact center
    if(isOdd(mLen)) {
        outStr[mHalfLen] = FindMiddleChr();
    }

    // 4. Halve frequencies to construct only the lexicographically first half
    HalveCntPerChr();

    // 5. Find the maximum prefix length that perfectly matches the target
    auto prefMatchLen{CalcPrefMatchLen()};
    auto const outStrRighHalfStart{outStr.begin() + mHalfLen + mLen % kParityDiv};

    // 6. Test if a full prefix match yields a strictly greater palindrome
    if(prefMatchLen == mHalfLen) {
        auto trgtPref{mTrgtStr | vs::take(mHalfLen)};
        rs::copy(trgtPref, outStr.begin());
        rs::copy(trgtPref | vs::reverse, outStrRighHalfStart);

        if(outStr > mTrgtStr) {
            return outStr;
        }
    }

    auto const maxDivergeIdx{std::min(mHalfLen - 1, prefMatchLen)};

    // Subtract matched prefix characters from the available frequency pool
    for(auto const chrIdx:
        mTrgtStr |
        vs::take(std::max(0, maxDivergeIdx)) |
        vs::transform(toIdx)
    ) {
        --mCntPerChr[chrIdx];
    }

    // 7. Backtrack to find optimal divergence point to exceed the target
    for(auto const divergeIdx: vs::iota(0, maxDivergeIdx + 1) | vs::reverse) {
        auto const divergeChrIdx{toIdx(mTrgtStr[divergeIdx])};

        // Extract available characters strictly greater than the target's char
        auto cntPerGreaterChr{mCntPerChr | vs::drop(divergeChrIdx + 1)};
        auto smallestGreaterChrIt{rs::find_if(cntPerGreaterChr, isPositive)};

        // 8. Select the smallest available character that exceeds the target
        if(smallestGreaterChrIt != cntPerGreaterChr.end()) {
            auto const replaceIdx{divergeChrIdx + 1 + 
                static_cast<int>(
                    rs::distance(cntPerGreaterChr.begin(), smallestGreaterChrIt)
                )
            };

            // 9. Build final string with chosen prefix and remaining sorted chars
            BuildOutStr(outStr, divergeIdx, replaceIdx, outStrRighHalfStart);

            return outStr;
        }

        // Restore character frequency from the target as we backtrack leftwards
        if(isPositive(divergeIdx)) {
            ++mCntPerChr[toIdx(mTrgtStr[divergeIdx - 1])];
        }
    }

    return {};
}

auto Solution::CountChrs() const -> cntPerChrT {
    auto cntPerChr{cntPerChrT{}};
    for(auto const chrIdx: mSrcStr | vs::transform(toIdx)) {
        ++cntPerChr[chrIdx];
    }

    return cntPerChr;
}

auto Solution::NotPalindrome() const -> bool {
    return rs::count_if(mCntPerChr, isOdd) > kMaxOddChrCnt;
}

auto Solution::FindMiddleChr() const -> char {
    return toChr(std::distance(mCntPerChr.begin(), rs::find_if(mCntPerChr, isOdd)));
}

auto Solution::HalveCntPerChr() -> void {
    for(auto const chrIdx: vs::iota(0, kChrSetSz)) {
        mCntPerChr[chrIdx] /= kParityDiv;
    }
}

auto Solution::CalcPrefMatchLen() const -> int {
    auto prefMatchLen{0};

    for(auto cntPerChrCopy{mCntPerChr};
        auto const chrIdx:
            vs::iota(0, mHalfLen) |
            vs::transform([&] (auto const idx_) { return toIdx(mTrgtStr[idx_]); }) |
            vs::take_while([&] (auto const chrIdx_) {
                return isPositive(cntPerChrCopy[chrIdx_]);
            })
    ) {
        --cntPerChrCopy[chrIdx];
        ++prefMatchLen;
    }

    return prefMatchLen;
}

auto Solution::BuildOutStr(
    std::string & outStr_,
    int const divergeIdx_,
    int const replaceIdx_,
    std::string::iterator const outStrRighHalfStart_
) -> void {
    // 1. Consume selected exceeding character to remove it from available pool
    --mCntPerChr[replaceIdx_];

    // 2. Lock in matched prefix and append exceeding character for divergence
    rs::copy(mTrgtStr | vs::take(divergeIdx_), outStr_.begin());
    outStr_[divergeIdx_] = toChr(replaceIdx_);

    auto fillPos{divergeIdx_ + 1};
    // 3. Fill remaining left half sequentially with smallest available characters
    for(auto const chrIdx:
        vs::iota(0, kChrSetSz) |
        vs::filter([&] (auto const chrIdx_) {
            return isPositive(mCntPerChr[chrIdx_]);
        })
    ) {
        auto const cnt{mCntPerChr[chrIdx]};

        // Bulk append identical characters
        std::fill_n(outStr_.begin() + fillPos, cnt, toChr(chrIdx));
        fillPos += cnt;
    }

    // 4. Mirror completed left half to the right side to finalize palindrome
    rs::copy(outStr_ | vs::take(mHalfLen) | vs::reverse, outStrRighHalfStart_);
}
