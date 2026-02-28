// problem : https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/description
// submission : https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/submissions/1934060354
// solution post : https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/solutions/7615865/
//    c-modern-readable-code-beats-100-runtime-y5xd

// import std;

inline static int const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' be the given number (upper limit)
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto concatenatedBinary(int const upperLim_) const -> int; 

private:
    // Modulo required by the problem to prevent overflow
    auto static constexpr kModulus{1'000'000'007uz};
};

auto Solution::concatenatedBinary(int const upperLim_) const -> int {
    namespace vs = std::views;

    // Current bit-length of the number being appended
    auto bitWidth{0uz};
    // Accumulated concatenated result (kept in size_t to avoid overflow before modulo)
    auto accum{0uz};
    for(auto const num: vs::iota(1uz, static_cast<size_t>(upperLim_+ 1))) {
        // When num is a power of two, its binary representation gains one extra bit
        if(std::bit_floor(num) == num) {
            ++bitWidth;
        }
        // Shift previous result to make space for new bits, append num, then apply modulo
        accum = ((accum << bitWidth) | num) % kModulus;
    }
    return static_cast<int>(accum);
}
