// problem : https://leetcode.com/problems/find-the-k-th-character-in-string-game-ii/description
// submission : https://leetcode.com/problems/find-the-k-th-character-in-string-game-ii/submissions/1686304551 
// solution post : https://leetcode.com/problems/find-the-k-th-character-in-string-game-ii/solutions/6919968/
//    c-modern-readable-code-beats-100-runtime-jywr

// #include <bit>
// #include <bitset>
// #include <ranges>

namespace Util {
    inline auto constexpr kChrSetSz{27};
    inline auto constexpr kChrSetFirst{'a'};
    inline auto constexpr kIntLongLongSz{64};
}

class Solution {
public:
// let 'n' be a given index of the target character 
// time complexity O(log2(n))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    char kthCharacter(
        long long const idxOfTargetChr_,
        std::vector<int> const & operations_
    ) const;
};

char Solution::kthCharacter(
    long long const idxOfTargetChr_,
    std::vector<int> const & operations_
) const {
    namespace views = std::views;
    using namespace Util;
    auto chrTargetOffset{0};
    auto const idxPrev{static_cast<unsigned long long>(idxOfTargetChr_) - 1};
    auto const idxPrevBin{std::bitset<kIntLongLongSz>{idxPrev}};
    auto const idxPrevBinSz{std::bit_width(idxPrev)};
    for(auto const idx: views::iota(0, idxPrevBinSz + 1) | views::reverse) {
        if(idxPrevBin.test(idx)) {
            chrTargetOffset += operations_.at(idx);
        }
    }
    auto const chrTarget{kChrSetFirst + (chrTargetOffset % (kChrSetSz - 1))};
    return chrTarget;
}
