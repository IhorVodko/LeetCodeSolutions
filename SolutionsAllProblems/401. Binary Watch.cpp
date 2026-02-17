// problem : https://leetcode.com/problems/binary-watch/description
// submission : https://leetcode.com/problems/binary-watch/submissions/1922433826
// solution post : https://leetcode.com/problems/binary-watch/solutions/7587074/
//    c-modern-readable-code-beats-100-runtime-m7ve

// import std;

// let 'n' be the number of turned on LEDs
// time complexity O(Combinations(10, n))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto readBinaryWatch(int const turnedOnCnt_) const -> std::vector<std::string>;
};

auto Solution::readBinaryWatch(
    int const turnedOnCnt_
) const -> std::vector<std::string> {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    static auto constexpr kLedsTotCnt{10};
    static auto constexpr kHourLedsCnt{4};
    static auto constexpr kMaxHour{11};
    static auto constexpr kMaxMin{59};
    static auto constexpr kTimeBufSz{5};
    static auto constexpr kOn{true};

    auto leds{std::array<bool, kLedsTotCnt>{}};
    rngs::fill(leds.end() - turnedOnCnt_, leds.end(), kOn);
    auto times{std::vector<std::string>{}};
    do {
        auto hours{0};
        // Compute hour value from the first 4 LEDs (most significant bit first)
        for(auto const i: vs::iota(0, kHourLedsCnt) | vs::reverse) {
            hours += static_cast<int>(std::exp2(kHourLedsCnt - 1 - i)) * leds[i];
        }
        if(hours > kMaxHour) {
            continue;
        }
        auto const isHSingleD{hours <= 9 ? true : false};
        auto mins{0};
        // Compute minute value from the remaining 6 LEDs
        for(auto const i: vs::iota(kHourLedsCnt, kLedsTotCnt) | vs::reverse) {
            mins += static_cast<int>(std::exp2(kLedsTotCnt - 1 - i)) * leds[i]; 
        }
        if(mins > kMaxMin) {
            continue;
        }
        auto const isMSinbleD{mins <= 9 ? true : false};
        auto tBuf{std::array<char, kTimeBufSz>{}};
        auto const tBufBegPtr{tBuf.data()};
        auto const tBufEndPtr{tBufBegPtr + kTimeBufSz};
        // Write hours into the buffer
        auto const hRes{std::to_chars(tBufBegPtr, tBufEndPtr, hours)};
        *hRes.ptr = ':';
        auto const mBufBegPtr{hRes.ptr + 1};
        auto const mBufSz{kTimeBufSz - (mBufBegPtr - tBufBegPtr)};
        // Write minutes immediately after ':'
        auto const mRes{std::to_chars(mBufBegPtr, mBufBegPtr + mBufSz, mins)};
        if(isHSingleD) {
            // Ensure minutes are zero-padded when hour is single digit
            if(mRes.ptr == tBufEndPtr - 2) {
                tBuf[3] = tBuf[2];
                tBuf[2] = '0';
            }             
            times.emplace_back(tBufBegPtr, tBufEndPtr - 1);
        } else {
            // Ensure minutes are zero-padded when hour has two digits
            if(mRes.ptr == tBufEndPtr - 1) {
                tBuf[4] = tBuf[3];
                tBuf[3] = '0';
            }
            times.emplace_back(tBufBegPtr, tBufEndPtr);
        }
    } while(rngs::next_permutation(leds).found);
    return times;
}
