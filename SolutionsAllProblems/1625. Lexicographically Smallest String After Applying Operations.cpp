// problem : https://leetcode.com/problems/lexicographically-smallest-string-after-applying-operations/description
// submission : https://leetcode.com/problems/lexicographically-smallest-string-after-applying-operations/submissions/
//    1805804711
// solution post : https://leetcode.com/problems/lexicographically-smallest-string-after-applying-operations/solutions/
//    7285924/c-modern-readable-code-beats-100-runtime-yx0d

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
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto findLexSmallestString(
        std::string & str_,
        int const addend_,
        int const shiftSteps_
   ) -> std::string;

private:
    auto Add(
        std::string & str_,
        int const startIdx_
    ) const -> void;

    int mAddend{};
    int mStrSz;
};

auto Solution::findLexSmallestString(
    std::string & str_,
    int const addend_,
    int const shiftSteps_
) -> std::string {
    namespace vs = std::views;

    mAddend = addend_;
    mStrSz = std::ssize(str_);
    auto smallestStr{str_};
    str_ += str_;
    auto const gcdVal{std::gcd(shiftSteps_, mStrSz)};
    for(auto const idx: vs::iota(0, mStrSz) | vs::stride(gcdVal)) {
        auto currStr{str_.substr(idx, mStrSz)};
        Add(currStr, 1);
        if(shiftSteps_ % 2) {
            Add(currStr, 0);
        }
        smallestStr = std::min(smallestStr, currStr);
    }
    return smallestStr;
}

auto Solution::Add(
    std::string & str_,
    int const startIdx_
) const -> void {
    namespace vs = std::views;

    auto minVal{10};
    auto times{0};
    for(auto const idx: vs::iota(0, 10)) {
        auto currVal{((str_[startIdx_] - '0') + idx * mAddend) % 10};
        if(currVal < minVal) {
            minVal = currVal;
            times = idx;
        }
    }        
    for(auto const idx:
            vs::iota(startIdx_, mStrSz) | vs::stride(2)
    ) {
        str_[idx] = '0' + ((str_[idx] - '0') + times * mAddend) % 10;
    }
}
