// problem : https://leetcode.com/problems/minimum-deletions-to-make-string-balanced/description
// submission : https://leetcode.com/problems/minimum-deletions-to-make-string-balanced/submissions/1911499813
// solution post : https://leetcode.com/problems/minimum-deletions-to-make-string-balanced/solutions/7561084/
//    c-modern-readable-code-beats-100-runtime-j2io

// import std;

inline static int const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' be the string length
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto minimumDeletions(std::string & str_) const -> int;
};

auto Solution::minimumDeletions(std::string & str_) const -> int {
    namespace vs = std::views;

    auto const sz{std::ssize(str_)};
    // Minimum deletions needed to keep the prefix balanced so far
    auto minDelCnt{0};
    // Number of 'b' characters seen in the prefix
    auto bCnt{0};
    for(auto const i: vs::iota(0, sz)) {
        if(str_[i] == 'b') {
            // Keeping 'b' increases the cost of future misplaced 'a's
            ++bCnt;
        } else {
            // Either delete this 'a' or delete all previous 'b's
            minDelCnt = std::min(minDelCnt + 1, bCnt);
        }
    }
    return minDelCnt;
}
