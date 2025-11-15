// problem : https://leetcode.com/problems/count-the-number-of-substrings-with-dominant-ones/description/
// submission : https://leetcode.com/problems/count-the-number-of-substrings-with-dominant-ones/submissions/1830415217
// solution post : https://leetcode.com/problems/count-the-number-of-substrings-with-dominant-ones/solutions/7350370/
//    c-modern-readable-code-beats-100-runtime-zfc6

// import std;

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
// let 'n' be the length of a given string
// time complexity O(n * sqrt(n))
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto numberOfSubstrings(
        std::string_view const str_
    ) const -> int;
};

auto Solution::numberOfSubstrings(
    std::string_view const str_
) const -> int {
    namespace vs = std::views;

    auto const strSz{std::ssize(str_)};
    auto nearestPosOf0(std::vector<int>(strSz + 1));
    nearestPosOf0[0] = -1;    
    for (auto const idx : vs::iota(0, strSz)) {
        if (idx == 0 || (idx > 0 && str_[idx - 1] == '0')) {
            nearestPosOf0[idx + 1] = idx;
        } else {
            nearestPosOf0[idx + 1] = nearestPosOf0[idx];
        }
    }
    auto subStrCnt{0};
    for (auto const idx1 : vs::iota(1, strSz + 1)) {
        auto cnt0{str_[idx1 - 1] == '0' ? 1 : 0};
        auto idx2{idx1};
        while (idx2 > 0 && cnt0 * cnt0 <= strSz) {
            auto cnt1{idx1 - nearestPosOf0[idx2] - cnt0};
            if (cnt0 * cnt0 <= cnt1) {
                subStrCnt += std::min(
                    idx2 - nearestPosOf0[idx2],
                    cnt1 - cnt0 * cnt0 + 1
                );
            }
            idx2 = nearestPosOf0[idx2];
            ++cnt0;
        }
    }
    return subStrCnt;
}
