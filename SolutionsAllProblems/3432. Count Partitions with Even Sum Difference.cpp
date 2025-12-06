// problem : https://leetcode.com/problems/count-partitions-with-even-sum-difference/description/
// submission : https://leetcode.com/problems/count-partitions-with-even-sum-difference/submissions/1848728908
// solution post : https://leetcode.com/problems/count-partitions-with-even-sum-difference/solutions/7396636/
//    c-modern-readable-code-beats-100-runtime-scyf

// import std;

class Solution {
public:
// let 'n' be the number of given numbers
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto countPartitions(
        std::span<int const> const nums_
    ) const -> int;
};

auto Solution::countPartitions(
    std::span<int const> const nums_
) const -> int {
    return 
            std::ranges::fold_left(nums_, 0, std::plus{}) % 2 == 0
        ?   std::ssize(nums_) - 1
        :   0
    ;
}
