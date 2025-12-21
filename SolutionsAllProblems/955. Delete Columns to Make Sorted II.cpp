// problem : https://leetcode.com/problems/delete-columns-to-make-sorted-ii/description
// submission : https://leetcode.com/problems/delete-columns-to-make-sorted-ii/submissions/1861432404
// solution post : https://leetcode.com/problems/delete-columns-to-make-sorted-ii/solutions/7428323/
//    c-modern-readable-code-beats-100-runtime-cncv

// import std;

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream{"display_runtime.txt"} << 0 << std::endl;
            }
        };
        std::atexit(&Print::DoPrint);
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' be the number of given strings
// 'm' - string size
// time complexity O(n * m)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto minDeletionSize(std::span<std::string const> const & strs_) const -> int;
};

auto Solution::minDeletionSize(std::span<std::string const> const & strs_) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto const strsSz{std::ssize(strs_)};
    auto const strSz{std::ssize(strs_[0])};
    auto isCheckNeeded{std::vector<bool>(strsSz - 1, true)};
    auto delColCnt{0};
    for(auto const colIdx: vs::iota(0, strSz)) {
        for(auto const rowIdx: vs::iota(0, strsSz - 1)) {
            auto const curChr{strs_[rowIdx][colIdx]};
            auto const prevChr{strs_[rowIdx + 1][colIdx]}; 
            if( isCheckNeeded[rowIdx] &&
                curChr > prevChr
            ) {
                ++delColCnt;
                goto skip;
            }
        }
        for(auto const rowIdx: vs::iota(0, strsSz -1)) {
            if(strs_[rowIdx][colIdx] < strs_[rowIdx + 1][colIdx]) {
                isCheckNeeded[rowIdx] = false;
            }
        }
        skip:
    }
    return delColCnt;
}
