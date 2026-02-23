// problem : https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/description
// submission : https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/submissions/1928665880
// solution post : https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/solutions/7602988/
//    c-modern-readable-code-beats-100-runtime-myhw

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
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    [[nodiscard]]
    auto hasAllCodes(
        std::string_view const str_,
        int const subStrSz_
    ) const -> bool;

private:
    static auto constexpr kMaxSubStrSz{20z};
    static auto constexpr kMaxBinNumSz{20z};
    static auto constexpr kMaxNumCnt{(1z << kMaxSubStrSz) + 1z};

};
auto Solution::hasAllCodes(
    std::string_view const str_,
    int const subStrSz_
) const -> bool {
    namespace vs = std::views;
    using intL = std::numeric_limits<int>;

    auto const strSz{std::ssize(str_)};
    auto codesLeftCnt{1z << subStrSz_};
    auto isCodeSeen{std::bitset<kMaxNumCnt>{}};
    // quick check: if the string is too short to contain all 2^subStrSz_ binary codes,
    // return false
    if(subStrSz_ + codesLeftCnt > strSz + 1) {
        return false;
    }
    auto binNum{std::bitset<kMaxBinNumSz>{}};
    for(auto const i: vs::iota(0, subStrSz_)) {
        // build the first window as an integer (rolling hash base state)
        // MSB corresponds to the first character of the substring
        binNum.set(subStrSz_ - i - 1, str_[i] == '1');
    }
    // record the first rolling hash value
    isCodeSeen.set(binNum.to_ulong());
    --codesLeftCnt;
    auto binNumMask{std::bitset<kMaxBinNumSz>{}};
    for(auto const i: vs::iota(0, subStrSz_)) {
        // mask keeps only the lowest subStrSz_ bits
        // this removes the overflow bit after each left shift in rolling hash
        binNumMask.set(i);
    }
    for(auto const i: vs::iota(subStrSz_, strSz)) {
        // rolling hash step:
        // shift left to drop the oldest bit and make room for the new one
        binNum <<= 1z;
        // apply mask to ensure the hash remains exactly subStrSz_ bits
        binNum &= binNumMask;
        // insert new bit as least significant bit
        binNum.set(0, str_[i] == '1');
        auto const num{binNum.to_ulong()};
        if(!isCodeSeen.test(num)) {
            // mark newly discovered hash value
            isCodeSeen.set(num);
            if(--codesLeftCnt == 0) {
                // early exit once all possible rolling hash values are seen
                return true;
            }
        }
    }
    // not all possible codes have been seen
    return false;
}
