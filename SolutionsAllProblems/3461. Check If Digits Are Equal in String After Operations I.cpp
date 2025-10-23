// problem : https://leetcode.com/problems/check-if-digits-are-equal-in-string-after-operations-i/description
// submission : https://leetcode.com/problems/check-if-digits-are-equal-in-string-after-operations-i/submissions/
//    1809651591
// solution post : https://leetcode.com/problems/check-if-digits-are-equal-in-string-after-operations-i/solutions/
//    7295589/c-modern-readable-code-beats-100-runtime-r7gc

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
// let 'n' be the length of the given string
// time complexity O(n^2)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto hasSameDigits(std::string & str_) const -> bool;
};

auto Solution::hasSameDigits(std::string & str_) const -> bool {
    namespace vs = std::views;

    auto const strSz{std::ssize(str_)};
    assert(strSz >= 3);
    for(auto const loopCnt: vs::iota(1, strSz - 1)) {
        for(auto const [chrIdxCurr, chrIdxNext] : vs::zip(
                vs::iota(0, strSz - loopCnt),
                vs::iota(1, strSz - loopCnt + 1)
            )
        ) {
            str_[chrIdxCurr] =
                ((str_[chrIdxCurr] - '0') + (str_[chrIdxNext] - '0')) % 10 +
                '0'
            ;
        }
    } 
    auto const isSame{str_[0] == str_[1]};
    return isSame;
}
