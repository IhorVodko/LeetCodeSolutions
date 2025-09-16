// problem : https://leetcode.com/problems/maximum-number-of-words-you-can-type/description/
// submission : https://leetcode.com/problems/maximum-number-of-words-you-can-type/submissions/1772834083
// solution post : https://leetcode.com/problems/maximum-number-of-words-you-can-type/solutions/7196591/
//    c-modern-readable-code-beats-100-runtime-eter

// import std;

class Solution {
public:
// let 'n' be a length of the given text
// 'c' - character set size
// time complexity O(n + c)
// space complexity O(c)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto canBeTypedWords(
        std::string const & text_,
        std::string const & brokenChrs_
    ) -> int;
private:
    static int constexpr kChrSetSz{27};
    static char constexpr kChrOffset{'a'};
    std::bitset<kChrSetSz> mBrokenChrs;
};

auto Solution::canBeTypedWords(
    std::string const & text_,
    std::string const & brokenChrs_
) -> int {
    namespace ranges = std::ranges;
    namespace views = std::views;
    mBrokenChrs.reset();
    for(auto const chr: brokenChrs_) {
        mBrokenChrs.set(chr - kChrOffset);
    }
    auto const IsValidWord{[&] (auto const & rng_) {
        return ranges::none_of(
            rng_,
            [&] (auto const chr_) {
                return mBrokenChrs.test(chr_ - kChrOffset);
            }
        );
    }};
    auto const correctWordCount{
        ranges::distance(
                text_
            |   views::split(' ')
            |   views::filter(
                    [&] (auto const & rng_) {
                        return IsValidWord(rng_);
                    }
                )
        )
    };
    return correctWordCount;
}
