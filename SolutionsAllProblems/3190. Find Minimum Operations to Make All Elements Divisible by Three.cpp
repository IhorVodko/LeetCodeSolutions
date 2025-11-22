// problem : https://leetcode.com/problems/find-minimum-operations-to-make-all-elements-divisible-by-three/description/
// submission : https://leetcode.com/problems/find-minimum-operations-to-make-all-elements-divisible-by-three/
//    submissions/1837136309
// solution post : https://leetcode.com/problems/find-minimum-operations-to-make-all-elements-divisible-by-three/
//    solutions/7368112/c-modern-readable-code-beats-100-runtime-7m34

// import std;

class Solution {
public:
// let 'n' be the number of given numbers
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto minimumOperations(
        std::span<int const> const nums_
    ) const -> int;
};

auto Solution::minimumOperations(
    std::span<int const> const nums_
) const -> int {
    return std::ranges::count_if(
        nums_,
        [] (auto const num_) {return num_ % 3 != 0;}
    );
}
