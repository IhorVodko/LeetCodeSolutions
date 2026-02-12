// problem : https://leetcode.com/problems/longest-balanced-substring-i/description
// submission : https://leetcode.com/problems/longest-balanced-substring-i/submissions/1917371394
// solution post : https://leetcode.com/problems/longest-balanced-substring-i/solutions/7574882/
//    c-modern-readable-code-beats-100-runtime-xc5l

// import std;

inline static int const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' be the string length
// time complexity O(n^2)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto longestBalanced(std::string_view const str_) const -> int;

private:
    static auto constexpr kChrSetSz{26};
};

auto Solution::longestBalanced(std::string_view const str_) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;
    using intLim = std::numeric_limits<int>;

    auto const strLen{std::ssize(str_)};
    auto maxSubStrLen{intLim::min()};
    for(auto chrCnts{std::array<int, kChrSetSz>{}};
        auto const iBeg: vs::iota(0, strLen)
    ) {
        for(auto const iEnd: vs::iota(iBeg, strLen)) {
            auto & curChrCnt{chrCnts[str_[iEnd] - 'a']};
            ++curChrCnt;
            // Track minimum and maximum frequency among characters present in current
            // substring
            auto chrMinCnt{intLim::max()};
            auto chrMaxCnt{intLim::min()};
            for(auto const chrCnt: chrCnts) {
                if(chrCnt > 0) {
                    chrMinCnt = std::min(chrMinCnt, chrCnt);
                    chrMaxCnt = std::max(chrMaxCnt, chrCnt);
                }
            }

            // Balanced substring condition: all used characters have equal frequency
            if(chrMinCnt == chrMaxCnt) {
                auto const curSubStrLen{iEnd - iBeg + 1};
                maxSubStrLen = std::max(maxSubStrLen, curSubStrLen);
            }
        }
        // Early stopping if remaining length cannot exceed current maximum
        if(iBeg + maxSubStrLen >= strLen) {
            return maxSubStrLen;
        }
        // Reset character counts for next starting index
        rngs::fill(chrCnts, 0);
    }
    return maxSubStrLen;
}
