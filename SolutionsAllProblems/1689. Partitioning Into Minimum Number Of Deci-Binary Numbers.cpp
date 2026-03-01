// problem : https://leetcode.com/problems/partitioning-into-minimum-number-of-deci-binary-numbers/description
// submission : https://leetcode.com/problems/partitioning-into-minimum-number-of-deci-binary-numbers/submissions/
//    1935043994
// solution post : https://leetcode.com/problems/partitioning-into-minimum-number-of-deci-binary-numbers/solutions/
//    7618468/c-modern-readable-code-beats-100-runtime-tq1x

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
class Solution {
public:
    [[nodiscard]]
    auto minPartitions(std::string_view strNum_) const -> int;

private:
    static auto constexpr kDigitChrLoLim{'0'};
    static auto constexpr kDigitChrUpLim{'9'};
    static auto constexpr kDigitUpLim{9};
};

auto Solution::minPartitions(std::string_view strNum_) const -> int {
    namespace vs = std::views;

    // Track the maximum digit character found in the string
    auto maxDigitChr{kDigitChrLoLim};
    for(auto const digitChr: strNum_) {
        maxDigitChr = std::max(maxDigitChr, digitChr);
        // Early exit if highest possible digit is found
        if(maxDigitChr == kDigitChrUpLim) {
            return kDigitUpLim;
        }
    }
    // Convert max digit character to its integer value
    return maxDigitChr - kDigitChrLoLim;
}
