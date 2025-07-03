// problem : https://leetcode.com/problems/k-th-symbol-in-grammar/description
// submission : https://leetcode.com/problems/k-th-symbol-in-grammar/submissions/1685179232
// solution post : https://leetcode.com/problems/k-th-symbol-in-grammar/solutions/6915917/
//    c-modern-readable-code-beats-100-runtime-puto

// #include <bit>

class Solution {
public:
// let 'c' be a given column value
// time complexity O(log2(c))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    int kthGrammar(
        int const rowCount_,
        int const colCount_
    ) const;
};

int Solution::kthGrammar(
    int const rowCount_,
    int const colCount_
) const {
    auto const bitsSetCount{std::popcount(
        static_cast<unsigned>(colCount_ - 1))};
    auto const targetSymbol{(bitsSetCount % 2) == 0 ? 0 : 1};
    return targetSymbol;
}
