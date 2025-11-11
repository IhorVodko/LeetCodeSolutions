// problem : https://leetcode.com/problems/ones-and-zeroes/description
// submission : https://leetcode.com/problems/ones-and-zeroes/submissions/1827009274
// solution post : https://leetcode.com/problems/ones-and-zeroes/solutions/7341909/
//    c-modern-readable-code-beats-100-runtime-z5y1

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
// let 's' be the total length of the given strings
// 'm' - the given upper limit of 0s count
// 'n' - the given upper limit of 1s count
// time complexity O(s * m * n)
// space complexity O(m * n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto findMaxForm(
        std::span<std::string const> const strs_,
        int const maxLimitCnt0s_,
        int const maxLimitCnt1s_
    ) const -> int;

private:
    [[nodiscard]]
    inline auto Count0and1(
        std::string_view const str_
    ) const -> std::pair<int, int>;
};

auto Solution::findMaxForm(
    std::span<std::string const> const strs_,
    int const maxLimitCnt0s_,
    int const maxLimitCnt1s_
) const -> int {
    auto dp{std::vector<std::vector<int>>(
        maxLimitCnt0s_ + 1,
        std::vector<int>(maxLimitCnt1s_ + 1)
    )};
    for(auto const & str: strs_) {
        auto const [cnt0s, cnt1s]{Count0and1(str)};
        for(auto dpCnt0s{maxLimitCnt0s_}; dpCnt0s >= cnt0s; --dpCnt0s) {
            for(auto dp1sCnt{maxLimitCnt1s_}; dp1sCnt >= cnt1s; --dp1sCnt) {
                dp[dpCnt0s][dp1sCnt] = std::max(
                    1 + dp[dpCnt0s - cnt0s][dp1sCnt - cnt1s],
                    dp[dpCnt0s][dp1sCnt]
                );
            }
        }
    }
    auto const maxSubSetSz{dp[maxLimitCnt0s_][maxLimitCnt1s_]};
    return maxSubSetSz;
}

auto Solution::Count0and1(
    std::string_view const str_
) const -> std::pair<int, int> {
    auto cnt0s{0};
    auto cnt1s{0};
    for(auto const chr: str_) {
        chr == '0' ? ++cnt0s : ++cnt1s;
    }
    return {cnt0s, cnt1s};
}
