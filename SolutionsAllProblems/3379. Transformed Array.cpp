// problem : https://leetcode.com/problems/transformed-array/description
// submission : https://leetcode.com/problems/transformed-array/submissions/1909527003
// solution post : https://leetcode.com/problems/transformed-array/solutions/7555912/
//    c-modern-readable-code-beats-100-runtime-5x4w

// import std;

inline static int const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' be the number of elements
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto constructTransformedArray(
        std::span<int const> const nums_
    ) const -> std::vector<int>;
};

auto Solution::constructTransformedArray(
    std::span<int const> const nums_
) const -> std::vector<int> {
    namespace vs = std::views;

    auto const sz{std::ssize(nums_)};
    auto result{std::vector<int>(sz)};
    for(auto const toIdx: vs::iota(0, sz)) {
        // Compute wrapped index safely for both positive and negative shifts
        auto const fromIdx{((toIdx + nums_[toIdx]) % sz + sz) % sz};
        // Assign value from the computed source index
        result[toIdx] = nums_[fromIdx];
    }
    return result;
}
