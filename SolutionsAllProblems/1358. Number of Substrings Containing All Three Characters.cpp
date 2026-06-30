// problem : https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/description
// submission : https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/submissions/2051220693
// solution post : https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/solutions/8367845/
//    modern-readable-code-optimal-time-comple-ts2b

// Approach : Track Last Seen Indices (Optimized Sliding Window)
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the string length
// Time :  O(n)
// Space : O(1)

// import std;

class Solution final {
public:
    [[nodiscard]]
    static auto numberOfSubstrings(std::string_view const str_) -> int;
};

auto Solution::numberOfSubstrings(std::string_view const str_) -> int {
    namespace vs = std::views;
    namespace rs = std::ranges;

    auto constexpr kTotChr{3};
    auto constexpr kNoIdx{-1};
    auto constexpr kCntOffset{1};
    auto constexpr kChrSetFirst{'a'};

    // Accumulator state for the folding iteration
    struct IdxsAndTot {
        std::array<int, kTotChr> mLatestIdxPerChr{kNoIdx, kNoIdx, kNoIdx};
        int mSubstrTot_{};
    };

    auto const accumSubStrCnt{[=] (auto idxsAndTot_, auto const idx_) {
        auto & [latestIdxPerChr, substrTot_]{idxsAndTot_};
        latestIdxPerChr[str_[idx_] - kChrSetFirst] = idx_;
        // Count valid substrings ending at the current index
        substrTot_  += kCntOffset + rs::min(latestIdxPerChr);
        
        return idxsAndTot_;
    }};

    return rs::fold_left(
        vs::iota(0, static_cast<int>(str_.size())),
        IdxsAndTot{},
        accumSubStrCnt
    ).mSubstrTot_;
}

namespace {

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace
