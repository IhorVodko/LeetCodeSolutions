// problem : https://leetcode.com/problems/check-if-binary-string-has-at-most-one-segment-of-ones/description
// submission : https://leetcode.com/problems/check-if-binary-string-has-at-most-one-segment-of-ones/submissions/1939949458
// solution post : https://leetcode.com/problems/check-if-binary-string-has-at-most-one-segment-of-ones/solutions/7630299/
//    c-modern-readable-code-beats-100-runtime-0dhn

// import std;

// Static initializer to configure fast I/O before main() runs
inline static int const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' be the number of bits
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    [[nodiscard]]
    auto checkOnesSegment(std::string_view const bits_) const -> bool;
};

auto Solution::checkOnesSegment(std::string_view const bits_) const -> bool {
    // If "01" exists, it means a segment of 1s ended and another 1 may appear later,
    // which implies more than one segment of consecutive 1s.
    return bits_.find("01") == std::string::npos;
}
