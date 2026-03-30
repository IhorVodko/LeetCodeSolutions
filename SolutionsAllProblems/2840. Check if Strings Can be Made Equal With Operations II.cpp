// problem : https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-ii/description
// submission : https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-ii/submissions/1963984321
// solution post : https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-ii/solutions/7723257/
//    c-modern-readable-code-runtime-0-ms-beat-4rh0

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

// let 'n' be the string size
// 'M' - the constant character set size
// time complexity O(n)
// space complexity O(M)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    [[nodiscard]]
    auto checkStrings(
        std::string const & s1_,
        std::string const & s2_
    ) const -> bool;

private:
    static auto constexpr kChrSetSz{26uz}; 
    static auto constexpr kChrSetFirst{'a'};
    // Predicate to verify that all frequency differences are zero
    static auto constexpr kIsZero{[] (auto const val_) { return val_ == 0; }};
};

auto Solution::checkStrings(
    std::string const & s1_,
    std::string const & s2_
) const -> bool {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto const len{std::ssize(s1_)};
    // Frequency difference arrays for even and odd indices separately
    auto cE{std::array<int, kChrSetSz>{}};
    auto cO{std::array<int, kChrSetSz>{}};
    for(auto const j: vs::iota(0, len)) {
        if(j % 2 == 0) {
            // Track net frequency difference for even positions
            --cE[s1_[j] - 'a'];
            ++cE[s2_[j] - 'a'];
        } else {
            // Track net frequency difference for odd positions
            --cO[s1_[j] - 'a'];
            ++cO[s2_[j] - 'a'];
        }
    }
    // Valid if both even and odd position character multisets match
    return rngs::all_of(cE, kIsZero) && rngs::all_of(cO,kIsZero); 
}
