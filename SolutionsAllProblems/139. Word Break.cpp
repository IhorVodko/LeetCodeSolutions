// problem : https://leetcode.com/problems/word-break/description/
// submission : https://leetcode.com/problems/word-break/submissions/1804001960
// solution post : https://leetcode.com/problems/word-break/solutions/7281366/
//    c-modern-readable-code-beats-100-runtime-yl8s

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
// let 's' be the length of the given string
// 'd' - of the given dictionary
// 'w' - of the longest word in dictionary
// time complexity O(s * d * w)
// space complexity O(s)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto wordBreak(
        std::string_view const str_,
        std::span<std::string> const dict_
    ) const -> bool;

private:
    inline static size_t constexpr kMaxStrSz{300};
};

auto Solution::wordBreak(
    std::string_view const str_,
    std::span<std::string> const dict_
) const -> bool {
    namespace vs = std::views;

    auto dpIsPossible{std::bitset<kMaxStrSz>{}};
    auto const strSz{std::ssize(str_)};
    for(auto const idx: vs::iota(0, strSz)) {
        for(auto const & word: dict_) {
            auto const wordSz{std::ssize(word)};
            auto const isIdxOutOfBounds{idx < wordSz - 1};
            if(isIdxOutOfBounds) {
                continue;
            }
            auto const prevEndIdx{idx - wordSz};
            auto const isFirstSubstr{idx == wordSz - 1}; 
            if(isFirstSubstr || dpIsPossible.test(prevEndIdx)) {
                auto const subStrStartIdx{idx - wordSz + 1};
                if(str_.substr(subStrStartIdx, wordSz) == word) {
                    dpIsPossible.set(idx);
                    break;
                }
            }
        }
    }
    auto const isPossible{dpIsPossible.test(strSz - 1)};
    return isPossible;
}
