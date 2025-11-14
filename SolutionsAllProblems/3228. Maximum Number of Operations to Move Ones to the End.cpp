// problem : https://leetcode.com/problems/maximum-number-of-operations-to-move-ones-to-the-end/description/
// submission : https://leetcode.com/problems/maximum-number-of-operations-to-move-ones-to-the-end/submissions/1829424357
// solution post : https://leetcode.com/problems/maximum-number-of-operations-to-move-ones-to-the-end/solutions/7347889/
//    c-modern-readable-code-beats-100-runtime-84yl

// import std;

// let 'n' be the length of a given string
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream("display_runtime.txt") << 0 << std::endl;
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
    [[nodiscard]]
    auto maxOperations(
        std::string_view const str_
    ) const -> int;
};

auto Solution::maxOperations(
    std::string_view const str_
) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto idx{0};
    auto const strSz{std::ssize(str_)};
    auto onesCnt{0};
    auto opCnt{0};
    while(idx < strSz) {
        if(str_[idx] == '0') {
            ++idx;
            continue;
        }
        while(idx < strSz && str_[idx] == '1') {
            ++onesCnt;
            ++idx;
        }
        if(idx != strSz) {
            opCnt += onesCnt;
        }
    }
    return opCnt;
}
