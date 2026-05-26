// problem : https://leetcode.com/problems/count-the-number-of-special-characters-i/description
// submission : https://leetcode.com/problems/count-the-number-of-special-characters-i/submissions/2013569272
// solution post : https://leetcode.com/problems/count-the-number-of-special-characters-i/solutions/8294866/
//    c-modern-readable-code-beats-100-runtime-j0dd

// Approach : Bitmask Intersection
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the string length
// complexity :  O(n)
// complexity : O(1), a character set size is a small constant, 26.

// import std;

class Solution final {
public:
    [[nodiscard]]
    static auto numberOfSpecialChars(std::string_view const word_) -> int;

private:
    // Maps alphabet domain to bitset indices
    [[nodiscard]]
    inline static auto ToIdx(char const chr_) -> size_t;

    static auto constexpr kChrSetSz{26uz};
    static auto constexpr kFirstLowChr{'a'};
    static auto constexpr kFirstUpChr{'A'};
};

auto Solution::numberOfSpecialChars(std::string_view const word_) -> int {
    namespace vs = std::views;

    // Single character cannot form a lower-upper pair
    if(word_.size() == 1) {
        return 0;
    }

    // Lower half stores lowercase, upper half stores uppercase
    auto chrMask{std::bitset<kChrSetSz * 2>{}};
    for(auto const chr: word_) {
        chrMask.set(ToIdx(chr));
    }

    // Intersect uppercase presence with lowercase presence
    chrMask &= (chrMask >> kChrSetSz);

    // Tally valid pairs found
    return static_cast<int>(chrMask.count());
}

auto Solution::ToIdx(char const chr_) -> size_t {
    return std::islower(chr_) ? chr_ - kFirstLowChr : chr_ - kFirstUpChr + kChrSetSz;
}

namespace {

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace
