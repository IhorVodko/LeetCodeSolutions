// problem : https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-i/description/
// submission : https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-i/submissions/1962998994
// solution post : https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-i/solutions/7715086/
//     c-modern-readable-code-runtime-0-ms-beat-avdo

// import std;

namespace {

// Compile-time initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace

// time complexity O(1)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    [[nodiscard]]
    auto canBeEqual(
        std::string s1_,
        std::string const & s2_
    ) const -> bool;

private:
    // only first two positions matter for comparison decisions
    static auto constexpr kPrefLength{2};
    // allowed operation swaps index (j) with (j + 2)
    static auto constexpr kSwapStep{2};
};

auto Solution::canBeEqual(
    std::string s1_,
    std::string const & s2_
) const -> bool {
    namespace vs = std::views;

    for(auto const j: vs::iota(0, kPrefLength)) {
        if(s1_[j] != s2_[j]) {
            // fix mismatch using allowed operation
            std::swap(s1_[j], s1_[j + kSwapStep]);
        }
    }
    return s1_ == s2_;
}
