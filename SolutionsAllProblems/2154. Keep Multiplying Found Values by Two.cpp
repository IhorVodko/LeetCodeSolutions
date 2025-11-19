// problem : https://leetcode.com/problems/keep-multiplying-found-values-by-two/description
// submission : https://leetcode.com/problems/keep-multiplying-found-values-by-two/submissions/1834359564
// solution post : https://leetcode.com/problems/keep-multiplying-found-values-by-two/solutions/7360756/
//    c-modern-readable-code-beats-100-runtime-25og

// import std;

class Solution {
public:
// let 'n' be the number of given numbers
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto findFinalValue(
        std::span<int const> const nums_,
        int original_
    ) const -> int;
};

auto Solution::findFinalValue(
    std::span<int const> const nums_,
    int original_
) const -> int {
    auto numsSet{std::unordered_set<int>{nums_.begin(), nums_.end()}};
    while(numsSet.contains(original_)) {
        original_ *= 2;
    }
    return original_;
}
