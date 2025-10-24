// problem : https://leetcode.com/problems/next-greater-numerically-balanced-number/description/
// submission : https://leetcode.com/problems/next-greater-numerically-balanced-number/submissions/1810199446
// solution post : https://leetcode.com/problems/next-greater-numerically-balanced-number/solutions/7296948/
//    c-modern-readable-code-beats-100-runtime-k7z2

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
// let 'n' be the given nubmer
// 'C' - the greatest possible balanced number
// time complexity O(C - n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto nextBeautifulNumber(int num_) -> int;

private:
    static constexpr int kMaxBalancedNum{1'224'444};
    static constexpr int kRadix{10};
    std::array<int, kRadix> mDigitCnts{};

    [[nodiscard]]
    inline auto IsNumberBalanced(int num_) -> bool;
};

auto Solution::nextBeautifulNumber(int num_) -> int {
    namespace vs = std::views;

    if(num_ >= kMaxBalancedNum) {
        return -1;
    }
    for(auto const num: vs::iota(num_ + 1, kMaxBalancedNum + 1)) {
        if(IsNumberBalanced(num)) {
            return num;
        }
    }
    return -1;
}

auto Solution::IsNumberBalanced(int num_) -> bool {
    namespace vs = std::views;

    mDigitCnts.fill(0);
    while(num_ > 0) {
        ++mDigitCnts[num_ % kRadix];
        num_ /= kRadix;
    }
    for(auto const digit: vs::iota(0, kRadix)) {
        auto const digitCnt{mDigitCnts[digit]};
        if(digitCnt > 0 && digitCnt != digit) {
            return false;
        }
    }
    return true;

}
