// problem : https://leetcode.com/problems/number-of-substrings-with-only-1s/description/
// submission : https://leetcode.com/problems/number-of-substrings-with-only-1s/submissions/1832525070
// solution post : https://leetcode.com/problems/number-of-substrings-with-only-1s/solutions/7355731/
//    c-modern-readable-code-beats-100-runtime-h7ba

// import std;

class Solution {
public:
// let 'n' be the length of given string
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto numSub(std::string_view const str_) const -> int;

private:
    static int constexpr kMod{1'000'000'007};

    inline auto CalcSubStrCnt(
        int const subStrCnt_,
        long long const cntOnes_
    ) const -> int;
};


auto Solution::numSub(std::string_view const str_) const -> int {
    auto cntOnes{0ll};
    auto subStrCnt{0};
    for (auto const chr: str_) {
        if (chr == '1') {
            ++cntOnes;
        } else if (cntOnes > 0) {
            subStrCnt = CalcSubStrCnt(subStrCnt, cntOnes);
            cntOnes = 0;
        }
    }
    if (cntOnes > 0) {
        subStrCnt = CalcSubStrCnt(subStrCnt, cntOnes);
    }
    return subStrCnt;
}

auto Solution::CalcSubStrCnt(
    int subStrCnt_,
    long long const cntOnes_
) const -> int {
    auto const currSubStrCnt{
        static_cast<int>((cntOnes_ * (cntOnes_ + 1) / 2) % kMod)
    };
    subStrCnt_ += currSubStrCnt; 
    subStrCnt_ %= kMod;
    return subStrCnt_;
}
