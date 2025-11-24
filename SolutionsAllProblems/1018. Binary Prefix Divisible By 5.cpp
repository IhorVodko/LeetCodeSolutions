// problem : https://leetcode.com/problems/binary-prefix-divisible-by-5/description 
// submission : https://leetcode.com/problems/binary-prefix-divisible-by-5/submissions/1838693692
// solution post : https://leetcode.com/problems/binary-prefix-divisible-by-5/solutions/7371976/
//    c-modern-readable-code-beats-100-runtime-wrjh

// import std;

class Solution {
public:
// let 'n' be the number of given numbers
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto prefixesDivBy5(
        std::span<int const> const nums_
    ) const -> std::vector<bool>;
};

auto Solution::prefixesDivBy5(
    std::span<int const> const nums_
) const -> std::vector<bool> {
    namespace vs = std::views;

    auto const numsSz{std::ssize(nums_)};
    auto answer{std::vector<bool>{}};
    answer.reserve(numsSz);
    auto rem{0};
    for(auto const idx: vs::iota(0, numsSz)) {
        rem = (rem * 2 + nums_[idx]) % 5;
        answer.emplace_back(rem == 0);
    }
    return answer;
}
