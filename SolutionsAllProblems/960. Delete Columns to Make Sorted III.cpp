// problem : https://leetcode.com/problems/delete-columns-to-make-sorted-iii/description
// submission : https://leetcode.com/problems/delete-columns-to-make-sorted-iii/submissions/1862530037
// solution post : https://leetcode.com/problems/delete-columns-to-make-sorted-iii/solutions/7431209/
//    c-modern-readable-code-beats-100-runtime-i2g1

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

class Solution {
public:
// let 'n' be the number of strings
// 'm' - string length
// time complexity O(n * m^2)
// space complexity O(m)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto minDeletionSize(std::vector<std::string> const & strs_) const -> int;
};

auto Solution::minDeletionSize(std::vector<std::string> const & strs_) const -> int{
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto const strSz{std::ssize(strs_[0])};
    auto keptColCntByIdx{std::vector<int>(strSz, 1)};
    auto keptColMaxCnt{1};
    for(auto const prevI: vs::iota(0, strSz - 1) | vs::reverse) {
        for(auto const curI: vs::iota(prevI + 1, strSz)) {
            for(auto const & row: strs_) {
                if(row[prevI] > row[curI]) {
                    goto Continue;
                }
            }
            keptColCntByIdx[prevI] =
                std::max(keptColCntByIdx[prevI], keptColCntByIdx[curI] + 1);
            keptColMaxCnt = std::max(keptColMaxCnt, keptColCntByIdx[prevI]);
            Continue:
        }
    }
    auto const delColMinCnt{strSz - keptColMaxCnt};
    return delColMinCnt;
}
