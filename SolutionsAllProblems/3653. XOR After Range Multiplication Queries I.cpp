// problem : https://leetcode.com/problems/xor-after-range-multiplication-queries-i/description
// submission : https://leetcode.com/problems/xor-after-range-multiplication-queries-i/submissions/1972630218
// solution post : https://leetcode.com/problems/xor-after-range-multiplication-queries-i/solutions/7829759/
//    c-modern-readable-code-beats-9282-runtim-1cpk

// Approach : Sequential Query Simulation

// Complexity :
// let 'n' be the number of
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %

// import std;

namespace {

// Compile-time initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    auto xorAfterQueries(
        std::vector<int> & nums_,
        std::vector<std::vector<int>> const & queries_
    ) -> int;

private:
    static auto constexpr kMod{1'000'000'007};
};

auto Solution::xorAfterQueries(
    std::vector<int> & nums_,
    std::vector<std::vector<int>> const & queries_
) -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    // Apply stride-based transformations for all queries sequentially
    for(auto const & query: queries_) {
        auto const r{query[1]};
        auto const step{query[2]};
        auto const mult{static_cast<long long>(query[3])};

        // Modify elements in-place with modulo arithmetic to prevent integer overflow
        for(auto l{query[0]}; l <= r; l += step) {
            nums_[l] = (nums_[l] * mult) % kMod;
        }
    }

    // Compute the final XOR sum using a functional reduction over the array view
    auto const xorVal{
        rngs::fold_left(nums_ | vs::drop(1), nums_.front(), std::bit_xor{})};

    return xorVal;
}
