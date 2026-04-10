// problem : https://leetcode.com/problems/minimum-distance-between-three-equal-elements-i/description/
// submission : https://leetcode.com/problems/minimum-distance-between-three-equal-elements-i/submissions/1974725927
// solution post : https://leetcode.com/problems/minimum-distance-between-three-equal-elements-i/solutions/7862163/
//    c-modern-readable-code-beats-100-runtime-nkpm

// import std;

// Approach : Fixed-Size Array Direct Addressing with 3-Pointer Sliding Window
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the length of the integer array
// 'M' - maximum possible integer value
// 'K' - maximum possible array length
// time :  O(n + M * n) 
// space : O(M * K)

namespace {

// Compile-time initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace

class Solution final {
public:
    using sizetLim = std::numeric_limits<size_t>;

    [[nodiscard]]
    auto minimumDistance(std::vector<int> const & nums_) const -> int;

private:
    static auto constexpr kNoAnswer{-1};
    static auto constexpr kMinIdxCnt{3uz};
    static auto constexpr kMaxNum{100uz};
    static auto constexpr kMaxIdx{100uz};
    // Stores the last observed index to optimize the right boundary of the sliding
    // window
    static auto constexpr kIdxOfLastIdx{100uz};
    // Tracks the total occurrences of a number to quickly filter out invalid candidates
    static auto constexpr kIdxOfIdxCnt{101uz};
    static auto constexpr kIsNotPresent{0uz};
    static auto constexpr kIsPresent{1uz};
};
auto Solution::minimumDistance(std::vector<int> const & nums_) const -> int {
    namespace vs = std::views;

    auto const numsSz{nums_.size()};

    if(numsSz < kMinIdxCnt) {
        return kNoAnswer;
    }

    // A frequency and position map where each number's array tracks presence flags,
    // last seen index, and total count
    auto numToIdxs{std::array<std::array<size_t, kMaxIdx + 2>, kMaxNum + 1>{}};

    for(auto const j: vs::iota(0uz, numsSz)) {
        auto & idxs{numToIdxs[nums_[j]]};
        idxs[kIdxOfLastIdx] = j;
        ++idxs[kIdxOfIdxCnt];
        idxs[j] = kIsPresent;
    }

    auto minDist{sizetLim::max()};
    auto leftIdx{sizetLim::max()};
    auto middleIdx{sizetLim::max()};
    auto rightIdx{sizetLim::max()};

    for(auto const & idxs: numToIdxs) {
        if(idxs[kIdxOfIdxCnt] < kMinIdxCnt) { continue; }

        auto const lastIdx{idxs[kIdxOfLastIdx]};
        auto lIdx{0uz};

        // Locate the first instance of the current number to establish the start of the
        // window
        while(idxs[lIdx] == kIsNotPresent) { ++lIdx; }

        auto midIdx{lIdx + 1};

        // Locate the second instance to complete the initial setup of the three-element window
        while(idxs[midIdx] == kIsNotPresent) { ++midIdx; }

        auto rIdx{midIdx + 1};

        // Slide a window of size 3 across the occurrences to find the minimum distance spread
        for(auto Idx{midIdx + 1}; rIdx <= lastIdx; ++rIdx) {
            if(idxs[rIdx] == kIsNotPresent) { continue; }

            if(auto const currDist{rIdx - lIdx}; currDist < minDist) {
                minDist = currDist; 
                leftIdx = lIdx;
                middleIdx = midIdx;
                rightIdx = rIdx;
            }

            lIdx = midIdx;
            midIdx = rIdx;            
        }
    }

    return minDist == sizetLim::max() ? -1 : static_cast<int>(minDist * 2);
}
