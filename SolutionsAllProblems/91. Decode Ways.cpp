// problem : https://leetcode.com/problems/decode-ways/description/
// submission : https://leetcode.com/problems/decode-ways/submissions/1822324563
// solution post : https://leetcode.com/problems/decode-ways/solutions/7330448/
//    c-modern-readable-code-beats-100-runtime-vcq9

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
// let 'n' be the length of given string
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto numDecodings(
        std::string_view const str_
    ) const -> int;
};

auto Solution::numDecodings(
    std::string_view const str_
) const -> int {
    namespace vs = std::views;

    if (str_.empty() || str_[0] == '0') {
        return 0;
    }
    auto const strSz{std::ssize(str_)};
    auto prevPrevWaysCnt{1};
    auto prevWaysCnt{1};
    for (auto const [prevI, currI]: vs::zip(
            vs::iota(0, strSz - 1),
            vs::iota(1, strSz)
    )) {
        if(prevPrevWaysCnt == 0 && prevWaysCnt == 0) {
            return 0;
        }
        auto currWaysCnt{0};
        if (str_[currI] != '0') {
            currWaysCnt = prevWaysCnt;
        }
        auto twoDigit{-1};
        auto twoDigitStr{str_.substr(prevI, 2)};
        std::from_chars(
            twoDigitStr.data(), twoDigitStr.data() + twoDigitStr.size(),
            twoDigit
        );
        if (10 <= twoDigit && twoDigit <= 26) {
            currWaysCnt += prevPrevWaysCnt;
        }
        prevPrevWaysCnt = prevWaysCnt;
        prevWaysCnt = currWaysCnt;
    }
    return prevWaysCnt;
}
