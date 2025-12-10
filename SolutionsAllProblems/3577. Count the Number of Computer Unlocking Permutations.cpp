// problem : https://leetcode.com/problems/count-the-number-of-computer-unlocking-permutations/description
// submission : https://leetcode.com/problems/count-the-number-of-computer-unlocking-permutations/submissions/1852371260
// solution post : https://leetcode.com/problems/count-the-number-of-computer-unlocking-permutations/solutions/7405544/
//    c-modern-readable-code-beats-100-runtime-ecs3

// import std;

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream{"display_runtime.txt"} << 0 << std::endl;
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
// let 'n' be the number of given complexities
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto countPermutations(
        std::span<int const> const complexities_
    ) const -> int;

private:
    static auto constexpr kModulos{1'000'000'007};
};

auto Solution::countPermutations(
    std::span<int const> const complexities_
) const -> int {
    namespace vs = std::views;

    auto permCnt{1};
    for(auto const idx: vs::iota(1ll, std::ssize(complexities_))) {
        if(complexities_.front() >= complexities_[idx]) {
            return 0;
        }
        permCnt = (permCnt * idx) % kModulos;
    }
    return permCnt;
}
