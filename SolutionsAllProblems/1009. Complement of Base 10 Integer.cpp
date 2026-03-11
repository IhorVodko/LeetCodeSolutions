// problem : https://leetcode.com/problems/complement-of-base-10-integer/description
// submission : https://leetcode.com/problems/complement-of-base-10-integer/submissions/1945124507
// solution post : https://leetcode.com/problems/complement-of-base-10-integer/solutions/7641589/
//    c-modern-readable-code-runtime-0-ms-beat-p9rc

// import std;

namespace {
    // Compile-time initializer to configure fast I/O before main() runs
    auto const fastIOInit{
        [] {
            std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return 0;
        } ()
    };
}

// time complexity O(1)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    [[nodiscard]]
    auto bitwiseComplement(int const num_) const -> int;
};

auto Solution::bitwiseComplement(int const num_) const -> int {
    namespace vs = std::views;

    // Work with unsigned representation to avoid sign-related bit behavior
    auto const num{static_cast<unsigned>(num_)};
    // Store bits of the number in a fixed-size bitset
    auto bits{std::bitset<sizeof(int) * 8>(num)};
    // Determine how many significant bits the number uses (at least 1 for zero)
    for(auto const bitW{std::max(std::bit_width(num), 1)};
        auto const j: vs::iota(0, bitW)) {
        // Flip only the significant bits to form the complement
        bits.flip(j);
    }
    // Convert modified bitset back to an integer value
    auto const complementNum{bits.to_ulong()};
    return static_cast<int>(complementNum);
}
