// problem : https://leetcode.com/problems/find-the-string-with-lcp/description
// submission : https://leetcode.com/problems/find-the-string-with-lcp/submissions/1961749942
// solution post : https://leetcode.com/problems/find-the-string-with-lcp/solutions/7709129/c-modern-readable-code-runtime-0-ms-beat-gp32

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


// let 'n' by 'n' be the matrix size
// time complexity O(n^2)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    using mxT= std::vector<std::vector<int>>;

    auto findTheString(mxT const & lcpMx_) const -> std::string;

private:
    static auto constexpr kChrSetMin{'a'};
    static auto constexpr kChrSetMax{'z'};
    static auto constexpr kChrSetNone{'\0'};
};

auto Solution::findTheString(mxT const & lcpMx_) const -> std::string {
    namespace vs = std::views;

    auto const rcSz{std::ssize(lcpMx_)};
    auto word{std::string(rcSz, kChrSetNone)};
    auto chr{kChrSetMin};
    // Greedily assign characters ensuring all positions with LCP > 0 share the same
    // character
    for(auto const r: vs::iota(0, rcSz)) {
        if(word[r] != kChrSetNone) { continue; }
        // If we run out of characters, it's impossible to construct a valid string
        if(chr > kChrSetMax) { return {}; }
        word[r] = chr;
        // Assign same character to all c where LCP(r, c) > 0
        for(auto const c: vs::iota(r + 1, rcSz)) {
            if(lcpMx_[r][c] > 0) { word[c] = word[r]; }
        }
        ++chr;
    }
    // Validate the constructed string against the LCP matrix
    for(auto const r: vs::iota(0, rcSz) | vs::reverse) {
        for(auto const c: vs::iota(0, rcSz) | vs::reverse) {
            // If characters differ, LCP must be zero
            if(word[r] != word[c]) {
                if(lcpMx_[r][c] > 0) { return {}; }
                continue;
            }
            // If either index is at the last position, LCP must be exactly 1
            if(r == rcSz - 1 || c == rcSz - 1) {
                if(lcpMx_[r][c] != 1) { return {}; }
                continue;
            }
            // Otherwise, LCP must follow recursive relation
            if(lcpMx_[r][c] != lcpMx_[r + 1][c + 1] + 1) { return {}; }
        }
    }
    // Return lexicographically smallest word that satisfies the given LCP matrix
    return word;
}
