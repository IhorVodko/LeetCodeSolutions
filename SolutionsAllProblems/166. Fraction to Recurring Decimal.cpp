// problem : https://leetcode.com/problems/fraction-to-recurring-decimal/description
// submission : https://leetcode.com/problems/fraction-to-recurring-decimal/submissions/1781618408
// solution post : https://leetcode.com/problems/fraction-to-recurring-decimal/solutions/7221145/
//    c-modern-readable-code-beats-100-runtime-0b0k

// import std;

class Solution {
public:
// let 'n' be a given upper limit of the result value
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto fractionToDecimal(
        int const numerator_,
        int const denominator_
    ) const -> std::string;
};

auto Solution::fractionToDecimal(
    int const numerator_,
    int const denominator_
) const -> std::string {
    assert(denominator_ != 0);
    if(numerator_ == 0) {
        return "0";
    }
    auto fractionStr{std::string{}};
    if(numerator_ < 0 ^ denominator_ < 0) {
        fractionStr += '-';
    }
    auto dividend{std::labs(numerator_)};
    auto divisor{std::labs(denominator_)};
    auto [quotient, remainder]{std::div(dividend, divisor)};
    fractionStr += std::to_string(quotient);
    if(remainder == 0) {
        return fractionStr;
    }
    fractionStr += '.';
    std::unordered_map<long long, int> remainderToIdx;
    while(remainder != 0) {
        if( auto const remainderAndIdxIt{remainderToIdx.find(remainder)};
            remainderAndIdxIt != remainderToIdx.end()
        ) {
            fractionStr.insert(remainderAndIdxIt->second, "(");
            fractionStr += ")";
            break;
        }
        remainderToIdx[remainder] = fractionStr.size();
        remainder *= 10;
        fractionStr += std::to_string(remainder / divisor);
        remainder %= divisor;
    }
    return fractionStr;
}
