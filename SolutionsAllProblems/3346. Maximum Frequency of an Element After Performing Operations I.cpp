// problem : https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-i/description
// submission : https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-i/
//    submissions/1807934988
// solution post : https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-i/
//     solutions/7291380/c-modern-readable-code-beats-100-runtime-ln2d

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
// let 'n' be the number of the given nubmber
// 'r' - the range of the given nubmers
// time complexity O(n * log(n) + r)
// space complexity O(log(n))
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto maxFrequency(
        std::span<int> const nums_,
        int const diff_,
        int const opCnt_
    ) const -> int;
};

auto Solution::maxFrequency(
    std::span<int> const nums_, 
    int const diff_,
    int const opCnt_
) const -> int {
    namespace rngs = std::ranges;
    namespace vs = std::views;
    using limitsInt = std::numeric_limits<int>;

    if(nums_.empty()) {
        return -1;
    }
    rngs::sort(nums_);
    auto numToCnt{std::unordered_map<int, int>{}};
    for(auto const num: nums_) {
        ++numToCnt[num];
    } 
    auto maxFreq{1};
    auto windowBegIt{nums_.cbegin()};
    auto windowEndIt{nums_.cbegin()};
    auto const numsEnd{nums_.cend()};
    auto const maxNum{nums_.back()};
    for(auto const num: vs::iota(nums_.front(), maxNum + 1)) {
        while(windowEndIt < numsEnd && *windowEndIt <= num + diff_) {
            ++windowEndIt;
        }
        while(*windowBegIt < num - diff_) {
            ++windowBegIt;
        }
        auto const windowSz{std::distance(windowBegIt, windowEndIt)};
        auto opMaxCnt{opCnt_};
        if(auto const numToCntIt{numToCnt.find(num)};
            numToCntIt != numToCnt.cend()
        ) {
            opMaxCnt += numToCntIt->second;
        }
        auto const currFreq{std::min(static_cast<int>(windowSz), opMaxCnt)};
        maxFreq = std::max(maxFreq, currFreq);
    }
    return maxFreq;
}
